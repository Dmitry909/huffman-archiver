#include "BitReader.h"
#include <stdexcept>

BitReader::BitReader(std::istream& input): input_(input) {

}

bool BitReader::Read() {
    if (buffer_size_ == 0) {
        if (input_.eof()) {
            throw std::range_error("access problem with istream in BitReader");
        }
        input_.get(buffer_);
        buffer_size_ = 8;
    }
    --buffer_size_;
    bool to_return = static_cast<bool>(buffer_ >> buffer_size_);
    buffer_ &= (1 << buffer_size_) - 1;
    return to_return;
}
