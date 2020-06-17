#ifndef COMPILER_OUTPUTSTREAM_H
#define COMPILER_OUTPUTSTREAM_H

#include <cstdio>

class OutputStream {
public:
    enum Standard {
        Output, Error
    };

    OutputStream(const OutputStream&) = delete;
    OutputStream& operator=(const OutputStream&) = delete;

    OutputStream(OutputStream&& out_stream) {
        std::swap(_file, out_stream._file);
    };

    OutputStream& operator=(OutputStream&& out_stream) {
        std::swap(_file, out_stream._file); return *this;
    }

    OutputStream(Standard standard) {
        _file = standard == Error ? stderr : stdout;
    }

    OutputStream(const std::string& file_name,
                 const char* mode):
            _file{fopen(file_name.c_str(), mode)}   {}

    ~OutputStream() {
        if (_file != stdin && _file != stdout && _file != stderr) {
            std::fclose(_file);
        }
    }

    auto file() -> std::FILE* {
        return _file;
    }

private:
    std::FILE* _file = nullptr;
};

#endif
