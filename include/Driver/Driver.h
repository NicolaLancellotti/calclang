#ifndef COMPILER_DRIVER_H
#define COMPILER_DRIVER_H

#include <filesystem>

namespace calclang {

    class Driver {
    public:

        auto run(int argc, const char* argv[]) -> int;

    private:
        enum class Phase {
            None,
            LexicalAnalysis,
            SyntacticAnalysis,
            SemanticAnalysis,
            Evaluation
        };

        enum class Dump {
            Disabled, ToStandardError, ToFile,
        };

        auto parse_args(int argc, const char* argv[]) -> bool;

        auto run_internal() -> bool;

        Phase _phase{Phase::None};

        auto set_phase(Phase phase) -> void {
            if (phase > this->_phase) {
                this->_phase = phase;
            }
        }

        std::filesystem::path _input_file;
        bool _interactive = false;

        bool _lex_verbose = false;
        Dump _dump_tokens{Dump::Disabled};
        std::string _dump_tokens_file{};

        bool _parse_verbose = false;
        Dump _dump_ast{Dump::Disabled};
        std::string _dump_ast_file{};
    };

}

#endif
