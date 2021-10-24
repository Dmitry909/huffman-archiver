#pragma once

#include "../constants.h"

class BitWriter {
public:
    BitWriter(std::ostream& output);

    void Write(bool value);

    void Write(const std::vector<bool>& code);

    void Write(const char& chr);

    void WriteTail();

private:
    std::ostream& output_;
    size_t buffer_size_ = 0;
    char buffer_ = 0;
    const size_t BITS_IN_CHAR = 8;
};
