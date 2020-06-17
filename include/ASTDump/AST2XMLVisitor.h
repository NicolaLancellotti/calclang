#ifndef COMPILER_AST2XMLVISITOR_H
#define COMPILER_AST2XMLVISITOR_H

#include "Visitor.h"
#include "tinyxml2.h"
#include "AST.h"
#include "OutputStream.h"

namespace calclang {

    class AST2XMLVisitor : public Visitor {
    public:
        AST2XMLVisitor(OutputStream file_box):
                doc{},
                root{&(this->doc)},
                _file_box{std::move(file_box)} {}

        auto operator()(std::unique_ptr<RootAST>& node) {
            node->accept(*this);
            tinyxml2::XMLPrinter steamer{_file_box.file()};
            doc.Print(&steamer);
        }

        auto visit(NumberAST&) -> void override;

        auto visit(BinaryOperationAST&) -> void override;

        auto visit(BlockAST&) -> void override;

        auto visit(AssignAST&) -> void override;

        auto visit(VariableAST&) -> void override;

    private:
        auto new_element(const NodeAST& node,
                         const char* name) -> tinyxml2::XMLElement*;

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLNode* root;
        OutputStream _file_box;
    };

}

#endif