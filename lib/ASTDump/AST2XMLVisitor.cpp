#include "AST2XMLVisitor.h"
using namespace tinyxml2;
using namespace calclang;


auto AST2XMLVisitor::visit(ModuleAST& node) -> void {
    auto element = new_element(node, "ModuleAST");
    root = element; node.expression()->accept(*this);
}

auto AST2XMLVisitor::new_element(const NodeAST& node, const char* name) -> XMLElement* {
    XMLElement* element = doc.NewElement(name);
    element->SetAttribute("loc", location_to_string(node.location()).c_str());
    root->InsertEndChild(element);
    return element;
}

auto AST2XMLVisitor::visit(NumberAST& node) -> void {
    auto element = new_element(node, "NumberAST");
    element->SetText(node.value());
}

auto AST2XMLVisitor::visit(BinaryOperationAST& node) -> void {
    auto element = new_element(node, "BinaryOpAST");
    element->SetAttribute("op", node.op_to_string());

    root = element; node.left_expression()->accept(*this);
    root = element; node.right_expression()->accept(*this);
}

auto AST2XMLVisitor::visit(BlockAST& node) -> void {
    auto element = new_element(node, "BodyAST");

    for (auto& expressions : node.expressions()) {
        root = element; expressions->accept(*this);
    }
}

auto AST2XMLVisitor::visit(AssignAST& node) -> void {
    auto element = new_element(node, "AssignAST");

    root = element; node.variable()->accept(*this);
    root = element; node.expression()->accept(*this);
}

auto AST2XMLVisitor::visit(VariableAST& node) -> void {
    auto element = new_element(node, "VariableAST");
    element->SetAttribute("id", node.id().c_str());
}