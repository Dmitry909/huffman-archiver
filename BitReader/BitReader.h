#pragma once

#include "../constants.h"
#include <fstream>

class BitReader {
public:
    BitReader(std::istream& input);

    bool Read();

private:
    std::istream& input_;
    size_t buffer_size_ = 0;
    char buffer_ = 0;
};