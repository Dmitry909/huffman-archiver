#pragma once

#include "../BitReader/BitReader.h"

namespace Huffman {
Letter ReadLetter(BitReader& bit_reader) {
    Letter result;
    for (size_t i = 0; i < LETTER_SIZE; ++i) {
        result[LETTER_SIZE - i - 1] = bit_reader.Read();
    }
    return result;
}
}  // namespace Huffman
