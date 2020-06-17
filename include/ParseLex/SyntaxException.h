#ifndef COMPILER_SYNTAXEXCEPTION_H
#define COMPILER_SYNTAXEXCEPTION_H

#include <exception>
#include "Location.h"

namespace calclang {

    class SyntaxException : public std::exception {
    public:
        SyntaxException(Location location,
                        std::string cause) :
                _location(location),
                _cause(cause) {}

        auto what() const noexcept -> const char* override {
            return _cause.c_str();
        }

        auto location() const -> const Location& {
            return _location;
        }

    private:
        const Location _location;
        const std::string _cause;
    };

}

#endif
