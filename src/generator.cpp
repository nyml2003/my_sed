//
// Created by venty on 2024/3/24.
//
#include <iostream>
#include "generator.hpp"
#include "value.hpp"

namespace SED::Generator {

    std::map<AST::Operator, std::string> OperatorToMermaid::operatorNames = {
            {AST::Operator::UNKNOWN, "\"unknown\""},
            {AST::Operator::ADD, "\"+\""},
            {AST::Operator::SUB, "\"-\""},
            {AST::Operator::MUL, "\"*\""},
            {AST::Operator::DIV, "\"/\""},
            {AST::Operator::MOD, "\"%\""},
            {AST::Operator::AND, "\"&&\""},
            {AST::Operator::OR, "\"||\""},
            {AST::Operator::EQ, "\"==\""},
            {AST::Operator::NE, "\"!=\""},
            {AST::Operator::LT, "\"<\""},
            {AST::Operator::LE, "\"<=\""},
            {AST::Operator::GT, "\">\""},
            {AST::Operator::GE, "\">=\""},
            {AST::Operator::POS, "\"+\""},
            {AST::Operator::NEG, "\"-\""},
            {AST::Operator::NOT, "\"!\""},
    };

    std::map<AST::NodeClass, std::string> NodeClassToMermaid::NodeClassNames = {
            {AST::NodeClass::INT_32, "int"},
            {AST::NodeClass::FLOAT_32, "float"},
            {AST::NodeClass::BOOLEAN, "bool"},
            {AST::NodeClass::POINTER, "pointer"},
            {AST::NodeClass::UNARY, "unary"},
            {AST::NodeClass::BINARY, "binary"},
            {AST::NodeClass::VARIABLE, "variable"},
            {AST::NodeClass::ASSIGNMENT, "assignment"},
            {AST::NodeClass::FUNCTION, "function"},
            {AST::NodeClass::BLOCK, "block"},
            {AST::NodeClass::RETURN_STATEMENT, "return"},
            {AST::NodeClass::VARIABLE_DECLARATION, "VARIABLE_DECLARATION"},
            {AST::NodeClass::COMPILATION_UNIT, "compilationUnit"},
            {AST::NodeClass::FUNCTION_CALL, "functionCall"},
            {AST::NodeClass::IF_STATEMENT, "if"},
            {AST::NodeClass::WHILE_STATEMENT, "while"},
            {AST::NodeClass::BREAK_STATEMENT, "break"},
            {AST::NodeClass::CONTINUE_STATEMENT, "continue"},
            {AST::NodeClass::VOID, "void"},
            {AST::NodeClass::ARGUMENT, "argument"},
    };

    std::map<AST::ValueType, std::string> ValueTypeToMermaid::ValueTypeNames = {
            {AST::ValueType::INT_32, "int"},
            {AST::ValueType::FLOAT_32, "float"},
            {AST::ValueType::BOOLEAN, "bool"},
            {AST::ValueType::POINTER, "pointer"},
            {AST::ValueType::VOID, "void"},
    };


    std::string OperatorToMermaid::toMermaid(AST::Operator op) {
        return operatorNames[op];
    }

    std::string NodeClassToMermaid::toMermaid(AST::NodeClass NodeClass) {
        return NodeClassNames[NodeClass];
    }

    std::string ValueTypeToMermaid::toMermaid(AST::ValueType type) {
        return ValueTypeNames[type];
    }

    size_t MermaidGenerator::counter = 0;

    size_t MermaidGenerator::count() {
        return ++counter;
    }

    size_t MermaidGenerator::getCounter() {
        return counter;
    }

    void MermaidGenerator::refreshCounter() {
        counter = 0;
    }

    void MermaidGenerator::mermaidHeader() {
        std::cout << "```mermaid" << std::endl;
        std::cout << "graph TD" << std::endl;
    }

    void MermaidGenerator::mermaidFooter() {
        std::cout << "```" << std::endl;
    }

    void MermaidGenerator::putEdge() {
        std::cout << counter << " --> " << counter + 1 << std::endl;
    }

    void MermaidGenerator::putEdge(const std::string &message) {
        std::cout << counter << " -- " << message << " --> " << counter + 1 << std::endl;
    }

    void MermaidGenerator::putEdge(size_t from, size_t to) {
        std::cout << from << " --> " << to << std::endl;
    }

    void MermaidGenerator::putEdge(size_t from, size_t to, const std::string &message) {
        std::cout << from << " -- " << message << " --> " << to << std::endl;
    }

    void MermaidGenerator::putLabel(AST::NodeClass NodeClass) {
        std::cout << counter << "[" << NodeClassToMermaid::toMermaid(NodeClass) << "]" << std::endl;
    }

    void MermaidGenerator::putLabel(AST::Operator op) {
        std::cout << counter << "[" << OperatorToMermaid::toMermaid(op) << "]" << std::endl;
    }

    void MermaidGenerator::putLabel(const std::string_view &label) {
        std::cout << counter << "[" << label << "]" << std::endl;
    }

    void MermaidGenerator::putLabel(AST::ValueType type) {
        std::cout << counter << "[" << ValueTypeToMermaid::toMermaid(type) << "]" << std::endl;
    }
}