
#include "Driver.h"
#include "Error.h"

using namespace calclang;

namespace Arg {
    const char* LexicalAnalysis = "-l";
    const char* LexicalAnalysisVerbose = "-lv";

    const char* DumpTokensToFile= "-dtokens=";
    const char* DumpTokensToStandardError= "-dtokens";

    const char* SyntacticAnalysis = "-p";
    const char* SyntacticAnalysisVerbose = "-pv";

    const char* DumpASTToFile= "-dast=";
    const char* DumpASTToStandardError= "-dast";

    const char* SemanticAnalysis = "-s";
    const char* Evaluation = "-e";

    auto is(const char* arg1, const char* arg2) -> bool {
        if (arg2 == DumpTokensToFile || arg2 == DumpASTToFile) {
            return strncmp(arg1, arg2, strlen(arg2)) == 0;
        }
        return strcmp(arg1, arg2) == 0;
    }
}

auto Driver::parse_args(int argc, const char* argv[]) -> bool {
    using namespace Arg;

    for (int i = 1;i < argc; ++i) {
        auto arg = argv[i];

        if (arg[0] != '-') {
            _input_file = std::filesystem::path{arg};
            if (!std::filesystem::exists(_input_file)) {
                Error::analysis(std::nullopt, Error::FileNotExist, _input_file.c_str());
                return false;
            }
        } else if (is(arg, LexicalAnalysis)) {
            set_phase(Phase::LexicalAnalysis);
        } else if (is(arg, LexicalAnalysisVerbose)) {
            _lex_verbose = true;
            set_phase(Phase::LexicalAnalysis);
        } else if (is(arg, DumpTokensToFile)) {
            _dump_tokens_file = std::string{&arg[9]};
            _dump_tokens = Dump::ToFile;
            set_phase(Phase::LexicalAnalysis);
        } else if (is(arg, DumpTokensToStandardError)) {
            _dump_tokens = Dump::ToStandardError;
            set_phase(Phase::LexicalAnalysis);
        } else if (is(arg, SyntacticAnalysis)) {
            set_phase(Phase::SyntacticAnalysis);
        } else if (is(arg, SyntacticAnalysisVerbose)) {
            _parse_verbose = true;
            set_phase(Phase::SyntacticAnalysis);
        } else if (is(arg, DumpASTToFile)) {
            _dump_ast_file = std::string{&arg[6]};
            _dump_ast = Dump::ToFile;
            set_phase(Phase::SyntacticAnalysis);
        } else if (is(arg, DumpASTToStandardError)) {
            _dump_ast = Dump::ToStandardError;
            set_phase(Phase::SyntacticAnalysis);
        } else if (is(arg, SemanticAnalysis)) {
            set_phase(Phase::SemanticAnalysis);
        } else if (is(arg, Evaluation)) {
            set_phase(Phase::Evaluation);
        } else {
            Error::analysis(std::nullopt, Error::UnrecognizedCommand, arg);
            return false;
        }
    }

    if (_input_file.empty()) {
//        Error::analysis(std::nullopt, Error::NoInputFile);
//        return false;
        this->_interactive = true;
    }

    if (this->_interactive && _dump_tokens != Dump::Disabled && _phase > Phase::LexicalAnalysis) {
        Error::analysis(std::nullopt, Error::DumpTokensMutuallyExclusive);
        return false;
    }

    if (_phase == Phase::None) {
        set_phase(Phase::Evaluation);
    }

    return true;
}