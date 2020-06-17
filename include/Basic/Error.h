#ifndef COMPILER_ERROR_H
#define COMPILER_ERROR_H

#include "Location.h"
#include <optional>

namespace calclang {

    namespace Error {
        // Type
        extern const char* AnalysisError;
        extern const char* RuntimeError;
        // Parse driver arguments
        extern const char* UnrecognizedCommand;
        extern const char* FileNotExist;
        extern const char* NoInputFile;
        // Semantic analysis
        extern const char* UndefinedVariable;
        extern const char* AssignToRval;
        // Runtime
        extern const char* DivisionByZero;
        // Interactive
        extern const char* DumpTokensMutuallyExclusive;

        auto analysis(std::optional<Location> location, const char* error,
                      ...) -> void;

        auto runtime(std::optional<Location> location, const char* error,
                     ...) -> void;
    }

}

#endif