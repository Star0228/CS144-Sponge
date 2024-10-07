#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {
    this->max = capacity;
}

size_t ByteStream::write(const string &data) {
    size_t written = 0;
    size_t temp = min(data.size(), this->remaining_capacity());
    while(temp--){
        this->queue.push(data[written++]);
    }
    this->sum_write += written;
    return written;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t temp = min(len, this->queue.size());
    auto temp_queue = this->queue;
    string s = "";
    while (temp--) {
        s.append(1, temp_queue.front());
        temp_queue.pop();
    }
    return s;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t temp = min(len, this->queue.size());
    this->sum_read += temp;
    while(temp--){
        this->queue.pop();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    auto s = peek_output(len);
    pop_output(len);
    return s;
}

void ByteStream::end_input() {
    this->input_end = true;
}

bool ByteStream::input_ended() const {
    return this->input_end;
}

size_t ByteStream::buffer_size() const { return this->queue.size(); }

bool ByteStream::buffer_empty() const { return this->queue.size()==0; }

bool ByteStream::eof() const { return this->input_end && buffer_empty(); }

size_t ByteStream::bytes_written() const { return this->sum_write; }

size_t ByteStream::bytes_read() const { return this->sum_read; }

size_t ByteStream::remaining_capacity() const { return this->max - this->queue.size(); }
