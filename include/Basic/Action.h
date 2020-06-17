#ifndef COMPILER_ACTION_H
#define COMPILER_ACTION_H

namespace calclang {

    namespace Action {
        extern const char* LexicalAnalysis;
        extern const char* DumpingTokens;
        extern const char* SyntacticAnalysis;
        extern const char* DumpingAST;
        extern const char* SemanticAnalysis;
        extern const char* Evaluating;
        extern const char* Finished;
        extern const char* InsertCode;

        auto print(const char* string) -> void;
        auto interactive(const char* string) -> void;
    }

}

#endif
