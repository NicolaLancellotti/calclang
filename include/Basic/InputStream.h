#ifndef COMPILER_INPUTSTREAM_H
#define COMPILER_INPUTSTREAM_H

#include <sstream>

class InputStream {
public:

    InputStream(const InputStream&) = delete;
    InputStream& operator=(const InputStream&) = delete;
    InputStream(InputStream&&) = default;
    InputStream& operator=(InputStream&&) = default;

    // Standard input
    InputStream() {}

    InputStream(const std::filesystem::path& path):
            _stream{std::make_unique<std::ifstream>(path, std::ifstream::in)},
            _file_name{path.filename()} {};

    InputStream(const std::string& source): _stream{std::make_unique<std::stringstream>(source)} {}

    auto stream() -> std::istream* {
        return _stream.get() != nullptr ? _stream.get() : &std::cin;
    }

    auto name() -> const std::string* {
        return _stream != nullptr ? &_file_name : nullptr;
    }

private:
    std::unique_ptr<std::istream> _stream = nullptr;
    std::string _file_name{};
};


#endif
