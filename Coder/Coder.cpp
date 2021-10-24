#include "Coder.h"
#include "../ExtraIOFunctions/ExtraOutput.h"
#include "../Modifiers/Modifiers.h"
#include <unordered_map>
#include <stdexcept>

Huffman::Coder::Coder(std::ofstream& archive_file) : bit_writer_(BitWriter(archive_file)) {

}

Huffman::Coder::Coder(BitWriter& bit_writer) : bit_writer_(bit_writer) {

}

void
Huffman::Coder::AddFile(const std::string& filename, bool is_last_file) {
    std::ifstream current_file(filename, std::ios::binary);
    if (current_file.fail()) {
        throw std::overflow_error(filename);
    }
    char current_char;
    std::unordered_map<Letter, size_t> symbols_count;
    current_file.get(current_char);
    while (!current_file.eof()) {
        if (current_file.fail()) {
            throw std::overflow_error(filename);
        }
        symbols_count[Letter(current_char)]++;
        current_file.get(current_char);
    }
    current_file.close();
    for (const auto& c: filename) {
        symbols_count[Letter(c)]++;
    }
    symbols_count[Letter(FILENAME_END)]++;
    symbols_count[Letter(ONE_MORE_FILE)]++;
    symbols_count[Letter(ARCHIVE_END)]++;

    Huffman::HuffmanTrie trie(symbols_count);
    auto codes_lengths = trie.GetCodesLengths();

    auto canonical_codes = Modifiers::GetCanonicalCodes(codes_lengths);
    Write(bit_writer_, Letter(canonical_codes.size()));  // 1
    for (size_t j = 0; j < canonical_codes.size(); ++j) {             // 2.1
        Write(bit_writer_, canonical_codes[j].first);
    }
    for (const auto& code_length: Huffman::Modifiers::GetCountLengths(codes_lengths)) {  // 2.2
        Write(bit_writer_, Letter(code_length));
    }
    std::unordered_map<Letter, HuffmanCode> code_by_symbol = Huffman::Modifiers::GetMapCodesBySymbols(canonical_codes);
    for (const auto& filename_symbol: filename) {  // 3
        bit_writer_.Write(code_by_symbol[Letter(filename_symbol)]);
    }
    bit_writer_.Write(code_by_symbol[Letter(FILENAME_END)]);  // 4
    current_file.open(filename, std::ios::binary);
    if (current_file.fail()) {
        throw std::overflow_error(filename);
    }
    current_file.get(current_char);
    while (!current_file.eof()) {  // 5
        if (current_file.fail()) {
            throw std::overflow_error(filename);
        }
        bit_writer_.Write(code_by_symbol[current_char]);
        current_file.get(current_char);
    }
    current_file.close();
    if (!is_last_file) {
        bit_writer_.Write(code_by_symbol[Letter(ONE_MORE_FILE)]);  // 6
    } else {
        bit_writer_.Write(code_by_symbol[Letter(ARCHIVE_END)]);
    }
}

void Huffman::Coder::WriteTail() {
    bit_writer_.WriteTail();
}
