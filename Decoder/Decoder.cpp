#include "Decoder.h"
#include "../ExtraIOFunctions/ExtraInput.h"
#include <stdexcept>

Huffman::Decoder::Decoder(const std::string& archive_name) {
    archive_file.open(archive_name);
    if (archive_file.fail()) {
        throw std::overflow_error(archive_name);
    }
}

void Huffman::Decoder::Decode() {
    BitReader bit_reader(archive_file);
    while (true) {
        size_t symbols_count = ReadLetter(bit_reader).to_ullong();  // 1
        std::vector<Letter> sorted_letters(symbols_count);
        for (size_t i = 0; i < symbols_count; ++i) {  // 2.1
            sorted_letters[i] = ReadLetter(bit_reader);
        }
        std::vector<size_t> count_letters_by_code_length;
        size_t count_read_letters = 0;
        while (count_read_letters < sorted_letters.size()) {  // 2.2
            count_letters_by_code_length.push_back(ReadLetter(bit_reader).to_ullong());
            count_read_letters += count_letters_by_code_length.back();
        }
        Huffman::HuffmanTrie trie(sorted_letters, count_letters_by_code_length);
        std::string output_filename;
        Letter last_letter = trie.ReadLetter(bit_reader);
        while (last_letter != Letter(FILENAME_END)) {  // 3-4
            output_filename += static_cast<char>(last_letter.to_ullong());
            last_letter = trie.ReadLetter(bit_reader);
        }
        std::ofstream output_file(output_filename, std::ios::binary);
        if (output_file.fail()) {
            throw std::overflow_error(output_filename);
        }
        last_letter = trie.ReadLetter(bit_reader);
        auto bit_writer = BitWriter(output_file);
        while (last_letter != Letter(ONE_MORE_FILE) && last_letter != Letter(ARCHIVE_END)) {  // 5-6
            bit_writer.Write(static_cast<char>(last_letter.to_ullong()));
            output_filename += static_cast<char>(last_letter.to_ullong());
            last_letter = trie.ReadLetter(bit_reader);
        }
        output_file.close();
        if (last_letter == Letter(ARCHIVE_END)) {
            break;
        }
    }
}

Huffman::Decoder::~Decoder() {
    archive_file.close();
}