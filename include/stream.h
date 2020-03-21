#ifndef STREAM_H_
#define STREAM_H_

#include <string>
using std::string;
#include <cstdlib>
#include <cstring>

constexpr size_t kBufferSize = 16000;

class Stream
{
    size_t pos_;
    char *buffer_;
    FILE *file_;
    size_t read_len_;
    string mod;
    bool eof_;

public:
    Stream() : pos_(0), buffer_(new char[kBufferSize]), read_len_(0), eof_(false) {}
    Stream(const string &filename, string m = "r") : pos_(0), buffer_(new char[kBufferSize]), read_len_(0), eof_(false), mod(m)
    {
        file_ = fopen(filename.c_str(), m.c_str());
    }
    void open(const string &filename, string m = "r")
    {
        mod = m;
        file_ = fopen(filename.c_str(), m.c_str());
    }
    Stream &operator>>(char &c)
    {
        if (pos_ == read_len_)
        {
            read_len_ = fread(buffer_, 1, kBufferSize, file_);
            eof_ = read_len_ == 0;
            pos_ = 0;
        }
        if (pos_ < read_len_)
        {
            c = buffer_[pos_++];
        }
        return *this;
    }
    Stream &operator>>(string &str)
    {
        str.clear();
        char ch;
        while (*this >> ch && ch != '\n')
        {
            str += ch;
        }
        return *this;
    }
    Stream &operator<<(const string &str)
    {
        if (str.size() + pos_ >= kBufferSize)
        {
            size_t temp = kBufferSize - pos_;
            strncpy(buffer_ + pos_, str.c_str(), temp);
            fwrite(buffer_, 1, kBufferSize, file_);
            pos_ = str.size() - temp;
            strncpy(buffer_, str.c_str() + temp, pos_);
        }
        else
        {
            strncpy(buffer_ + pos_, str.c_str(), str.size());
            pos_ += str.size();
        }
        return *this;
    }
    ~Stream()
    {
        if (mod == "w")
            fwrite(buffer_, 1, pos_, file_);
        delete[] buffer_;
        fclose(file_);
    }
    operator bool() const
    {
        return !eof_;
    }
};

#endif