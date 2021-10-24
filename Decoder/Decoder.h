#pragma once

#include "../BitWriter/BitWriter.h"
#include "../BitReader/BitReader.h"
#include "../HuffmanTrie/HuffmanTrie.h"

namespace Huffman {
class Decoder {
public:
    Decoder(const std::string& archive_name);

    void Decode();

    ~Decoder();

private:
    std::ifstream archive_file;
    const size_t FILENAME_END = 256;
    const size_t ONE_MORE_FILE = 257;
    const size_t ARCHIVE_END = 258;
};
};  // namespace Huffman
