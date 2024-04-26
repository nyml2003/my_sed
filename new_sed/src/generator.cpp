//
// Created by venty on 2024/3/24.
//
#include "generator.hpp"
#include <iostream>

namespace SED::Generator
{

std::map<Enumeration::Operator, std::string> mermaidOperatorMap = {
    {Enumeration::Operator::ADD, "\"+\""}, {Enumeration::Operator::SUB, "\"-\""},
    {Enumeration::Operator::MUL, "\"*\""}, {Enumeration::Operator::DIV, "\"/\""},
    {Enumeration::Operator::MOD, "\"%\""}, {Enumeration::Operator::AND, "\"&&\""},
    {Enumeration::Operator::OR, "\"||\""}, {Enumeration::Operator::EQ, "\"==\""},
    {Enumeration::Operator::NE, "\"!=\""}, {Enumeration::Operator::LT, "\"<\""},
    {Enumeration::Operator::LE, "\"<=\""}, {Enumeration::Operator::GT, "\">\""},
    {Enumeration::Operator::GE, "\">=\""}, {Enumeration::Operator::POS, "\"+\""},
    {Enumeration::Operator::NEG, "\"-\""}, {Enumeration::Operator::NOT, "\"!\""}};

std::string mermaidOperatorWrapper(Enumeration::Operator op)
{
    return mermaidOperatorMap[op];
}

std::map<Enumeration::NodeClass, std::string> mermaidNodeClassMap = {
    {Enumeration::NodeClass::CONSTANT, "constant"},
    {Enumeration::NodeClass::UNARY, "unary"},
    {Enumeration::NodeClass::BINARY, "binary"},
    {Enumeration::NodeClass::VARIABLE, "variable"},
    {Enumeration::NodeClass::FUNCTION_CALL, "function_call"},
    {Enumeration::NodeClass::RETURN_STATEMENT, "return"},
    {Enumeration::NodeClass::WHILE_STATEMENT, "while"},
    {Enumeration::NodeClass::IF_STATEMENT, "if"},
    {Enumeration::NodeClass::CONTINUE_STATEMENT, "continue"},
    {Enumeration::NodeClass::EXPRESSION_STATEMENT, "expression"},
    {Enumeration::NodeClass::BREAK_STATEMENT, "break"},
    {Enumeration::NodeClass::ASSIGNMENT, "assignment"},
    {Enumeration::NodeClass::VARIABLE_DECLARATION, "variable_declaration"},
    {Enumeration::NodeClass::FUNCTION_DECLARATION, "function_declaration"},
    {Enumeration::NodeClass::FUNCTION_DEFINITION, "function_definition"},
    {Enumeration::NodeClass::COMPILATION_UNIT, "compilation_unit"},
    {Enumeration::NodeClass::BLOCK, "block"}};

std::string mermaidNodeClassWrapper(Enumeration::NodeClass nodeClass)
{
    return mermaidNodeClassMap[nodeClass];
}

std::map<Enumeration::ValueType, std::string> mermaidValueTypeMap = {
    {Enumeration::ValueType::INT_32, "int"},   {Enumeration::ValueType::FLOAT_32, "float"},
    {Enumeration::ValueType::BOOLEAN, "bool"}, {Enumeration::ValueType::POINTER, "pointer"},
    {Enumeration::ValueType::CHAR, "char"},    {Enumeration::ValueType::VOID, "void"}};

std::string mermaidValueTypeWrapper(Enumeration::ValueType valueType)
{
    return mermaidValueTypeMap[valueType];
}

size_t MermaidGenerator::counter = 0;

size_t MermaidGenerator::nextCounter()
{
    return ++counter;
}

size_t MermaidGenerator::getCounter()
{
    return counter;
}

void MermaidGenerator::refreshCounter()
{
    counter = 0;
}

void MermaidGenerator::mermaidHeader()
{
    std::cout << "```mermaid" << std::endl;
    std::cout << "graph TD" << std::endl;
}

void MermaidGenerator::mermaidFooter()
{
    std::cout << "```" << std::endl;
}

void MermaidGenerator::putEdge()
{
    std::cout << counter << " --> " << counter + 1 << std::endl;
}

void MermaidGenerator::putEdge(const std::string &message)
{
    std::cout << counter << " -- " << message << " --> " << counter + 1 << std::endl;
}

void MermaidGenerator::putEdge(size_t from, size_t to)
{
    std::cout << from << " --> " << to << std::endl;
}

void MermaidGenerator::putEdge(size_t from, size_t to, const std::string &message)
{
    std::cout << from << " -- " << message << " --> " << to << std::endl;
}

void MermaidGenerator::putLabel(const std::string &label)
{
    std::cout << counter << "[" << label << "]" << std::endl;
}

void MermaidGenerator::putLabel(Enumeration::NodeClass nodeClass)
{
    std::cout << counter << "[" << mermaidNodeClassWrapper(nodeClass) << "]" << std::endl;
}

void MermaidGenerator::putLabel(Enumeration::Operator op)
{
    std::cout << counter << "[" << mermaidOperatorWrapper(op) << "]" << std::endl;
}

void MermaidGenerator::putLabel(Enumeration::ValueType valueType)
{
    std::cout << counter << "[" << mermaidValueTypeWrapper(valueType) << "]" << std::endl;
}

std::map<Enumeration::Operator, std::string> irOperatorMap = {
    {Enumeration::Operator::ADD, "add"}, {Enumeration::Operator::SUB, "sub"}, {Enumeration::Operator::MUL, "mul"},
    {Enumeration::Operator::DIV, "div"}, {Enumeration::Operator::MOD, "mod"}, {Enumeration::Operator::AND, "and"},
    {Enumeration::Operator::OR, "or"},   {Enumeration::Operator::EQ, "eq"},   {Enumeration::Operator::NE, "ne"},
    {Enumeration::Operator::LT, "lt"},   {Enumeration::Operator::LE, "le"},   {Enumeration::Operator::GT, "gt"},
    {Enumeration::Operator::GE, "ge"},   {Enumeration::Operator::POS, "pos"}, {Enumeration::Operator::NEG, "neg"},
    {Enumeration::Operator::NOT, "not"}};

std::string irOperatorWrapper(Enumeration::Operator op)
{
    return irOperatorMap[op];
}

size_t IRGenerator::registerCounter = 0;

size_t IRGenerator::labelCounter = 0;

size_t IRGenerator::getRegister()
{
    return registerCounter;
}

void IRGenerator::nextRegister()
{
    registerCounter++;
}

std::string IRGenerator::registerWrapper(size_t register_id)
{
    return "%" + std::to_string(register_id);
}

size_t IRGenerator::getLabel()
{
    return labelCounter;
}

void IRGenerator::nextLabel()
{
    labelCounter++;
}

std::string IRGenerator::labelWrapper(size_t label_id)
{
    return "L" + std::to_string(label_id);
}
} // namespace SED::Generator