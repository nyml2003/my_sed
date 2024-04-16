//
// Created by venty on 2024/3/24.
//

#include <iostream>
#include "ast.hpp"
#include "generator.hpp"
#include "value.hpp"
#include "context.hpp"
#include <fstream>
#include "driver.hpp"
#include "error.hpp"

namespace SED::AST
{

    /*---------------------Node---------------------*/

    Node::Node(NodeClass _nodeClass) : nodeClass(_nodeClass)
    {
    }

    std::map<NodeClass, std::string> NodeClassEnumMap = {
        {NodeClass::VARIABLE_DECLARATION, "VariableDeclaration"},
        {NodeClass::ASSIGNMENT, "Assignment"},
        {NodeClass::INT_32, "Int32"},
        {NodeClass::FLOAT_32, "Float32"},
        {NodeClass::BOOLEAN, "Boolean"},
        {NodeClass::POINTER, "Pointer"},
        {NodeClass::UNARY, "Unary"},
        {NodeClass::BINARY, "Binary"},
        {NodeClass::VARIABLE, "Variable"},
        {NodeClass::VOID, "Void"},
        {NodeClass::BREAK_STATEMENT, "BreakStatement"},
        {NodeClass::FUNCTION_CALL, "FunctionCall"},
        {NodeClass::FUNCTION_DECLARATION, "FunctionDeclaration"},
        {NodeClass::EXPRESSION_STATEMENT, "ExpressionStatement"},
        {NodeClass::RETURN_STATEMENT, "ReturnStatement"},
        {NodeClass::FUNCTION_DEFINITION, "FunctionDefinition"},
        {NodeClass::COMPILATION_UNIT, "CompilationUnit"},
        {NodeClass::BLOCK, "Block"},

        };

    std::string NodeClassEnumMapToString(NodeClass nodeClass){
        return NodeClassEnumMap[nodeClass];
    }

    NodeClass Node::getNodeClass() const
    {
        return nodeClass;
    }

    /*---------------------VARIABLE_DECLARATION---------------------*/

    VariableDeclaration::VariableDeclaration() : Node(NodeClass::VARIABLE_DECLARATION) {}

    void VariableDeclaration::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::VARIABLE_DECLARATION);
        count();
        putEdge(id, getCounter(), "类型");
        putLabel(type);
        count();
        putEdge(id, getCounter(), "变量");
        variable->toMermaid();
        if (value == nullptr)
        {
            return;
        }
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    void VariableDeclaration::toIR(){
        irs.push_back((new IR::Var())->setName(variable->getName()));
    }

    VariableDeclaration *VariableDeclaration::setVariable(Variable *_variable)
    {
        variable = _variable;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setValue(RightValue *_value)
    {
        value = _value;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setType(ValueType _type)
    {
        type = _type;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setIsConst(bool _isConst)
    {
        isConst = _isConst;
        return this;
    }

    Variable *VariableDeclaration::getVariable() const
    {
        return variable;
    }

    RightValue *VariableDeclaration::getValue() const
    {
        return value;
    }

    ValueType VariableDeclaration::getType() const
    {
        return type;
    }

    bool VariableDeclaration::getIsConst() const
    {
        return isConst;
    }

    /*---------------------Assignment---------------------*/

    Assignment::Assignment() : Node(NodeClass::ASSIGNMENT) {}

    Assignment *Assignment::setVariable(Variable *_variable)
    {
        variable = _variable;
        return this;
    }

    Assignment *Assignment::setValue(RightValue *_value)
    {
        value = _value;
        return this;
    }

    void Assignment::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::ASSIGNMENT);
        count();
        putEdge(id, getCounter(), "变量");
        variable->toMermaid();
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    void Assignment::toIR(){
        irs.push_back((new IR::Assign())->setLeftVar(variable->getName())->setRightVar(getRegister()));
        value->toIR();
    }

    Variable *Assignment::getVariable() const
    {
        return variable;
    }

    RightValue *Assignment::getValue() const
    {
        return value;
    }

    /*---------------------BreakStatement---------------------*/

    BreakStatement::BreakStatement() : Node(NodeClass::BREAK_STATEMENT) {}

    void BreakStatement::toMermaid()
    {
        putLabel(NodeClass::BREAK_STATEMENT);
    }

    void BreakStatement::toIR(){
        ;
    }

    /*---------------------FunctionDeclaration---------------------*/

    FunctionDeclaration::FunctionDeclaration() : Node(NodeClass::FUNCTION_DECLARATION) {}

    void FunctionDeclaration::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::FUNCTION_DECLARATION);
        count();
        putEdge(id, getCounter(), "函数名");
        putLabel(name);
        count();
        putEdge(id, getCounter(), "返回值");
        putLabel(returnType);
    }

    void FunctionDeclaration::toIR(){
        ;
    }

    FunctionDeclaration *FunctionDeclaration::setName(const std::string &_name)
    {
        name = _name;
        return this;
    }

    FunctionDeclaration *FunctionDeclaration::setReturnType(ValueType _returnType)
    {
        returnType = _returnType;
        return this;
    }

    std::string FunctionDeclaration::getName() const
    {
        return name;
    }

    ValueType FunctionDeclaration::getReturnType() const
    {
        return returnType;
    }

    /*---------------------ExpressionStatement---------------------*/

    ExpressionStatement::ExpressionStatement() : Node(NodeClass::EXPRESSION_STATEMENT) {}

    ExpressionStatement *ExpressionStatement::setValue(RightValue *_value)
    {
        value = _value;
        return this;
    }

    RightValue *ExpressionStatement::getValue() const
    {
        return value;
    }

    void ExpressionStatement::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::EXPRESSION_STATEMENT);
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    /*---------------------COMPILAION_UNIT---------------------*/

    CompilationUnit::CompilationUnit() : Node(NodeClass::COMPILATION_UNIT) {}

    void CompilationUnit::toMermaid()
    {
        mermaidHeader();
        size_t id = getCounter();
        putLabel(NodeClass::COMPILATION_UNIT);
        for (auto &node : nodes)
        {
            count();
            putEdge(id, getCounter(), NodeClassEnumMap[node->getNodeClass()]);
            node->toMermaid();
        }
        mermaidFooter();
    }

    CompilationUnit * CompilationUnit::setNodes(const std::vector<Node *> &_nodes)
    {
        nodes = std::move(_nodes);
        return this;
    }

    std::vector<Node *> CompilationUnit::getNodes() const
    {
        return nodes;
    }

    /*---------------------Block---------------------*/

    Block::Block() : Node(NodeClass::BLOCK) {}

    void Block::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::BLOCK);
        for (auto &node : nodes)
        {
            count();
            putEdge(id, getCounter(), NodeClassEnumMap[node->getNodeClass()]);
            node->toMermaid();
        }
    }

    void Block::toIR(){
        for (auto &node : nodes)
        {
            node->toIR();
        }
    }

    Block *Block::setNodes(const std::vector<Node *> &_nodes)
    {
        nodes = std::move(_nodes);
        return this;
    }

    std::vector<Node *> Block::getNodes() const
    {
        return nodes;
    }

    /*---------------------FunctionDefinition---------------------*/

    FunctionDefinition::FunctionDefinition() : Node(NodeClass::FUNCTION_DEFINITION) {}

    void FunctionDefinition::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::FUNCTION_DEFINITION);
        count();
        putEdge(id, getCounter(), "函数声明");
        declaration->toMermaid();
        count();
        putEdge(id, getCounter(), "函数体");
        block->toMermaid();
    }

    void FunctionDefinition::toIR(){
        irs.push_back((new IR::Label())->setName(declaration->getName()));
        irs.push_back((new IR::Start()));
        block->toIR();
        irs.push_back((new IR::End()));
    }

    FunctionDefinition *FunctionDefinition::setDeclaration(FunctionDeclaration *_declaration)
    {
        declaration = _declaration;
        return this;
    }

    FunctionDefinition *FunctionDefinition::setBlock(Block *_block)
    {
        block = _block;
        return this;
    }

    FunctionDeclaration *FunctionDefinition::getDeclaration() const
    {
        return declaration;
    }

    /*---------------------ReturnStatement---------------------*/

    ReturnStatement::ReturnStatement() : Node(NodeClass::RETURN_STATEMENT) {}

    ReturnStatement *ReturnStatement::setValue(RightValue *_value)
    {
        value = _value;
        return this;
    }

    RightValue *ReturnStatement::getValue() const
    {
        return value;
    }

    void ReturnStatement::toMermaid()
    {
        size_t id = getCounter();
        putLabel(NodeClass::RETURN_STATEMENT);
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    void ReturnStatement::toIR(){
        irs.push_back((new IR::Return())->setVar(getRegister()));
    }
}
