#pragma once

#include "../BitWriter/BitWriter.h"
#include "../HuffmanTrie/HuffmanTrie.h"
#include <fstream>

namespace Huffman {
    class Coder {
    public:
        Coder(std::ofstream& archive_file);

        Coder(BitWriter& bit_writer);

        void AddFile(const std::string& filename, bool is_last_file);

        void WriteTail();

    private:
        BitWriter bit_writer_;
        const size_t FILENAME_END = 256;
        const size_t ONE_MORE_FILE = 257;
        const size_t ARCHIVE_END = 258;
    };
}  // namespace Huffman
