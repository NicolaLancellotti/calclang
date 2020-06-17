#include "PrettyPrint.h"

namespace calclang::PrettyPrint {

    auto set(FILE* stream,
             Color color,
             bool bold,
             bool italic,
             bool underline) -> void {
        std::fprintf(stream, "\x1b[");

        if (bold) {
            std::fprintf(stream, ";1");
        }
        if (italic) {
            std::fprintf(stream, ";3");
        }
        if (underline) {
            std::fprintf(stream, ";4");
        }
        std::fprintf(stream, ";%dm", color);
    }

    auto reset(FILE* stream) -> void {
        std::fprintf(stream, "\x1b[0;39m");
    }

    auto print(FILE* stream,
               const char* string,
               Color color,
               bool bold,
               bool italic,
               bool underline) -> void {
        set(stream, color, bold, italic, underline);
        std::fprintf(stream, "%s", string);
        reset(stream);
    }

}