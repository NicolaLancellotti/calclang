#include "Error.h"
#include "PrettyPrint.h"

using namespace calclang;

const char* Error::AnalysisError = "error: ";
const char* Error::RuntimeError = "runtime error: ";
const char* Error::UnrecognizedCommand = "unrecognized command: %s";
const char* Error::FileNotExist = "file %s not exist";
const char* Error::NoInputFile = "no input file";
const char* Error::UndefinedVariable = "cannot find value `%s` in this scope";
const char* Error::AssignToRval = "cannot assign to value";
const char* Error::DivisionByZero = "division by zero";
const char* Error::DumpTokensMutuallyExclusive = "dump tokens flag is mutually exclusive with other flags in interactive mode";

static auto print_error(std::optional<Location> location_opt, const char* error_type, const char* format, va_list args) -> void {
    FILE* stream = stderr;
    if (location_opt.has_value()) {
        auto location = location_opt.value();
        PrettyPrint::set(stream, PrettyPrint::Color::blue);
        std::fprintf(stream, "%s: ", location_to_string(location).c_str());
    }

    PrettyPrint::set(stream, PrettyPrint::Color::red);
    std::fprintf(stream, "%s", error_type);
    PrettyPrint::set(stream, PrettyPrint::Color::blue);
    std::vfprintf(stream, format, args);
    PrettyPrint::reset(stream);
    std::cerr << std::endl;
}

auto Error::analysis(std::optional<Location> location, const char* error, ...) -> void {
    va_list args;
    va_start(args, error);
    print_error(location, Error::AnalysisError, error, args);
}

auto Error::runtime(std::optional<Location> location, const char* error, ...) -> void {
    va_list args;
    va_start(args, error);
    print_error(location, Error::RuntimeError, error, args);
}