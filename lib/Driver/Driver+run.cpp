#include "Driver.h"
#include "Parser.h"
#include "AST2XMLVisitor.h"
#include "SemanticAnalysisVisitor.h"
#include "EvaluatorVisitor.h"
#include "Action.h"
#include "Defer.h"
#include "RuntimeException.h"
#include "InputStream.h"
#include "OutputStream.h"

using namespace calclang;

auto Driver::run(int argc, const char*  argv[]) -> int {
    Defer print_finish{[]() { Action::print(Action::Finished);}};
    if (!parse_args(argc, argv)) {
        return EXIT_FAILURE;
    }
    return run_internal() ? EXIT_SUCCESS : EXIT_FAILURE;
}

auto Driver::run_internal() -> bool
try {
    auto make_lexer = [&]() -> Lexer {
        return Lexer{_interactive ? InputStream{} : InputStream{_input_file},
                     _lex_verbose};
    };

    // _________________________________________________________________________
    // Lexical analysis

    if (_interactive) {
        Action::interactive(Action::InsertCode);
    }

    switch (_dump_tokens) {
        case Dump::Disabled:
            if (_phase == Phase::LexicalAnalysis) {
                Action::print(Action::LexicalAnalysis);
                make_lexer().lex_all();
            }
            break;
        case Dump::ToStandardError:
            Action::print(Action::DumpingTokens);
            make_lexer().dump_tokens(OutputStream{OutputStream::Error});
            break;
        case Dump::ToFile:
            Action::print(Action::DumpingTokens);
            make_lexer().dump_tokens(OutputStream{_dump_tokens_file, "w"});
            break;
    }

    // _________________________________________________________________________
    // Syntactic analysis

    if (_phase < Phase::SyntacticAnalysis) return true;
    if (!_interactive) Action::print(Action::SyntacticAnalysis);

    auto parser = Parser{make_lexer(), _parse_verbose};
    auto root_node = parser();

    switch (_dump_ast) {
        case Dump::Disabled:
            break;
        case Dump::ToStandardError: {
            Action::print(Action::DumpingAST);
            auto visitor = AST2XMLVisitor{OutputStream{OutputStream::Error}};
            visitor(root_node);
            break;
        }
        case Dump::ToFile: {
            Action::print(Action::DumpingAST);
            auto visitor = AST2XMLVisitor{OutputStream{_dump_ast_file, "w"}};
            visitor(root_node);
            break;
        }
    }

    // _________________________________________________________________________
    // Semantic analysis

    if (_phase < Phase::SemanticAnalysis) return true;
    if (!_interactive) Action::print(Action::SemanticAnalysis);

    auto semantic_analyser = SemanticAnalysisVisitor{true};
    if (!semantic_analyser(root_node)) {
        return false;
    }

    // _________________________________________________________________________
    // Evaluation

    if (_phase < Phase::Evaluation) return true;
    if (!_interactive) Action::print(Action::Evaluating);

    auto evaluator = EvaluatorVisitor{};
    auto result = evaluator(root_node);
    std::cerr << "Result: " << result << std::endl;

    // _________________________________________________________________________

    return true;

} catch (SyntaxException& exception) {
    Error::analysis(exception.location(), exception.what());
    return false;
} catch (RuntimeException& exception) {
    Error::runtime(exception.location(), exception.what());
    return false;
}