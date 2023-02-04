#include "byte_stream.hh"

#include <cassert>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

// template <typename... Targs>
// void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : buffer_(),head_(0), tail_(0), size_(0), capacity_(capacity), input_end_(false), written_count_(0), read_count_(0) {
    buffer_.reserve(capacity);
}

/**
 * writer as many as the buffer can fit
 * @return the number of bytes written in
 */
size_t ByteStream::write(const string &data) {
    size_t written_byte_num = 0;
    auto it = data.begin();
    while (size_ < capacity_ && it != data.end()) {
        buffer_[tail_ % capacity_] = *it;
        written_byte_num++;
        it++;
        size_++;
        tail_ = (tail_ + 1) % capacity_;
    }
    written_count_ += written_byte_num;
    return written_byte_num;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string ret{};
    for (size_t i = 0; i < len && i < size_; i++) {
        ret.push_back(buffer_[(head_ + i) % capacity_]);
    }
    return ret;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    for (size_t i = 0; i < len && size_ > 0; i++) {
        head_ = (head_ + 1) % capacity_;
        size_--;
        read_count_++;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string ret = peek_output(len);
    pop_output(len);
    return ret;
}

void ByteStream::end_input() { input_end_ = true; }

bool ByteStream::input_ended() const { return input_end_; }

size_t ByteStream::buffer_size() const { return size_; }

bool ByteStream::buffer_empty() const { return !size_; }

// return true if output has reached the end
// 写end 且 读完了
bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

// total bytes that has been written
size_t ByteStream::bytes_written() const { return written_count_; }

size_t ByteStream::bytes_read() const { return read_count_; }

size_t ByteStream::remaining_capacity() const { return capacity_ - size_; }
