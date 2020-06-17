#ifndef COMPILER_PRETTYPRINT_H
#define COMPILER_PRETTYPRINT_H

#include <cstdio>

namespace calclang {

    namespace PrettyPrint {

        enum class Color {
            black = 30, red, green, yellow, blue, magenta, cyan, white,
        };

        auto set(std::FILE* stream,
                 Color color,
                 bool bold = false,
                 bool italic = false,
                 bool underline = false) -> void;

        auto reset(std::FILE* stream) -> void;

        auto print(std::FILE* stream,
                   const char* string,
                   Color color,
                   bool bold = false,
                   bool italic = false,
                   bool underline = false) -> void;
    }

}

#endif