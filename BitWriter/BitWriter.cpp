#include "BitWriter.h"
#include <fstream>

BitWriter::BitWriter(std::ostream& output): output_(output) {

}

void BitWriter::Write(bool value) {
    buffer_ = (buffer_ << 1) + static_cast<char>(value);
    ++buffer_size_;
    if (buffer_size_ == 8) {
        output_.put(buffer_);
        if (output_.fail()) {
            throw std::range_error("access problem with ostream in BitWriter");
        }
        buffer_size_ = 0;
        buffer_ = 0;
    }
}

void BitWriter::Write(const std::vector<bool>& code) {
    for (const auto& bit : code) {
        Write(bit);
    }
}

void BitWriter::Write(const char& chr) {
    for (size_t i = 0; i < BITS_IN_CHAR; ++i) {
        Write(static_cast<bool>(chr & (1 << (BITS_IN_CHAR - i - 1))));
    }
}

void BitWriter::WriteTail() {
    while (buffer_size_ > 0) {
        Write(false);
    }
}
