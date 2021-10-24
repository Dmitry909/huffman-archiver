#pragma once

#include "../BitWriter/BitWriter.h"

namespace Huffman {
void Write(BitWriter& bit_writer, const Letter& code) {
    for (size_t i = 0; i < LETTER_SIZE; ++i) {
        bit_writer.Write(code[LETTER_SIZE - i - 1]);
    }
}
}  // namespace Huffman
