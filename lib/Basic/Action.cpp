#include "Action.h"
#include "PrettyPrint.h"

using namespace calclang;

const char* Action::LexicalAnalysis = "Lexical analysis...";
const char* Action::DumpingTokens = "Dumping tokens...";
const char* Action::SyntacticAnalysis = "Lexical & syntactic analysis...";
const char* Action::DumpingAST = "Dumping AST...";
const char* Action::SemanticAnalysis = "Semantic analysis...";
const char* Action::Evaluating = "Evaluating...";
const char* Action::Finished = "Finished";
const char* Action::InsertCode = "Welcome to calclang, insert the code:";

auto Action::print(const char* string) -> void {
    PrettyPrint::print(stderr, string, PrettyPrint::Color::green);
    std::fprintf(stderr, "\n");
}

auto Action::interactive(const char* string) -> void {
    PrettyPrint::print(stderr, string, PrettyPrint::Color::white);
    std::fprintf(stderr, "\n");
}