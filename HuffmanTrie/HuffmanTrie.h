#pragma once

#include "../BitReader/BitReader.h"
#include <unordered_map>

namespace Huffman {
class HuffmanTrie {
public:
    HuffmanTrie(Letter letter);

    HuffmanTrie(std::unordered_map<Letter, size_t>& symbols_count);

    HuffmanTrie(std::vector<Letter>& sorted_letters, std::vector<size_t> count_letters_by_code_length);

    void Add(const HuffmanCode& code, const Letter& letter);

    std::vector<std::pair<size_t, Letter>> GetCodesLengths() const;

    Letter ReadLetter(BitReader& reader);

    ~HuffmanTrie();

private:
    Letter letter;
    HuffmanTrie* left = nullptr;
    HuffmanTrie* right = nullptr;

    bool IsTerminal() const;

    void RecursiveSearch(std::vector<std::pair<size_t, Letter>>& to_add, const HuffmanTrie* node, size_t depth) const;
};
}  // namespace Huffman
