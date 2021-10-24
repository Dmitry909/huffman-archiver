#pragma once

#include <vector>
#include <bitset>

namespace Huffman {
    const size_t LETTER_SIZE = 9;
}

using HuffmanCode = std::vector<bool>;
using Letter = std::bitset<Huffman::LETTER_SIZE>;

enum QUERY_TYPE {
    HELP,
    COMPRESS,
    DECOMPRESS,
};