//
// Created by venty on 2024/3/24.
//

#include "ast.hpp"
#include "context.hpp"
#include "driver.hpp"
#include "error.hpp"
#include "generator.hpp"
#include "value.hpp"
#include <fstream>
#include <iostream>

namespace SED::AST
{

/*
 * 以下是Node的实现
 */

Node::Node(NodeClass _nodeClass) : nodeClass(_nodeClass)
{
}

std::map<Node::NodeClass, std::string> Node::NodeClassEnumMap = {
    {NodeClass::INT_32, "32位有符号整数"},
    {NodeClass::FLOAT_32, "32位浮点数"},
    {NodeClass::BOOLEAN, "布尔值"},
    {NodeClass::POINTER, "指针"},
    {NodeClass::CHAR, "字符"},
    {NodeClass::VOID, "void"},
    {NodeClass::UNARY, "一元运算"},
    {NodeClass::BINARY, "二元运算"},
    {NodeClass::VARIABLE, "变量"},
    {NodeClass::ASSIGNMENT, "赋值语句"},
    {NodeClass::VARIABLE_DECLARATION, "变量声明"},
    {NodeClass::BREAK_STATEMENT, "break语句"},
    {NodeClass::FUNCTION_CALL, "函数调用"},
    {NodeClass::FUNCTION_DECLARATION, "函数声明"},
    {NodeClass::COMPILATION_UNIT, "编译单元"},
    {NodeClass::EXPRESSION_STATEMENT, "表达式语句"},
    {NodeClass::RETURN_STATEMENT, "return语句"},
    {NodeClass::FUNCTION_DEFINITION, "函数定义"},
    {NodeClass::BLOCK, "块"},
    {NodeClass::IF_STATEMENT, "if语句"},
    {NodeClass::WHILE_STATEMENT, "while语句"},
    {NodeClass::CONTINUE_STATEMENT, "continue语句"},
};

std::string Node::NodeClassEnumMapToString(NodeClass nodeClass)
{
    return NodeClassEnumMap[nodeClass];
}

Node::NodeClass Node::getNodeClass() const
{
    return nodeClass;
}

/*---------------------VARIABLE_DECLARATION---------------------*/

VariableDeclaration::VariableDeclaration() : Node(Node::NodeClass::VARIABLE_DECLARATION)
{
}

void VariableDeclaration::toMermaid()
{
    size_t id = getCounter();
    putLabel(Node::NodeClassEnumMapToString(Node::NodeClass::VARIABLE_DECLARATION));
    count();
    putEdge(id, getCounter(), "类型");
    putLabel(ValueTypeEnumMapToString(type));
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

void VariableDeclaration::toIR()
{
    irs.push_back((new IR::Var())->setName(variable->getName()));
    value->toIR();
    irs.push_back((new IR::Assign())->setLeftValue(variable->getName())->setRightValue(getRegister()));
}

VariableDeclaration *VariableDeclaration::setVariable(Variable *_variable)
{
    variable = _variable;
    return this;
}

VariableDeclaration *VariableDeclaration::setValue(Value *_value)
{
    value = _value;
    return this;
}

VariableDeclaration *VariableDeclaration::setType(ValueType _type)
{
    type = _type;
    return this;
}

VariableDeclaration *VariableDeclaration::setCanReassign(bool _canReassign)
{
    canReassign = _canReassign;
    return this;
}

Variable *VariableDeclaration::getVariable() const
{
    return variable;
}

Value *VariableDeclaration::getValue() const
{
    return value;
}

ValueType VariableDeclaration::getType() const
{
    return type;
}

bool VariableDeclaration::getCanReassign() const
{
    return canReassign;
}

void VariableDeclaration::analyze()
{
    if (analyzerContext.exists(variable) == true)
    {
        Error::VariableRedeclarationError(variable->getName()).error();
        return;
    }
    if (value != nullptr)
    {
        if (value->getValueType() != type)
        {
            Error::TypeMismatchError(type, value->getValueType()).error();
            return;
        }
        if (value->isDirect())
        {
            value = value->directify();
        }
        analyzerContext.add(variable, value->directify());
    }
    return;
}

/*---------------------Assignment---------------------*/

Assignment::Assignment() : Node(NodeClass::ASSIGNMENT)
{
}

Assignment *Assignment::setVariable(Variable *_variable)
{
    variable = _variable;
    return this;
}

Assignment *Assignment::setValue(Value *_value)
{
    value = _value;
    return this;
}

void Assignment::toMermaid()
{
    size_t id = getCounter();
    putLabel(Node::NodeClassEnumMapToString(Node::NodeClass::ASSIGNMENT));
    count();
    putEdge(id, getCounter(), "变量");
    variable->toMermaid();
    count();
    putEdge(id, getCounter(), "值");
    value->toMermaid();
}

void Assignment::toIR()
{

    value->toIR();
    irs.push_back((new IR::Assign())->setLeftValue(variable->getName())->setRightValue(getRegister()));
}

Variable *Assignment::getVariable() const
{
    return variable;
}

Value *Assignment::getValue() const
{
    return value;
}

void Assignment::analyze()
{
    if (analyzerContext.exists(variable) == false)
    {
        Error::UndeclaredVariableError(variable->getName()).error();
        return;
    }
    if (analyzerContext.get(variable)->getValueType() != value->getValueType())
    {
        Error::TypeMismatchError(analyzerContext.get(variable)->getValueType(), value->getValueType()).error();
        return;
    }
    if (value->isDirect())
    {
        value = value->directify();
        analyzerContext.set(variable, value->directify());
    }
}

/*---------------------BreakStatement---------------------*/

BreakStatement::BreakStatement() : Node(NodeClass::BREAK_STATEMENT)
{
}

void BreakStatement::toMermaid()
{
    putLabel(NodeClassEnumMapToString(NodeClass::BREAK_STATEMENT));
}

void BreakStatement::toIR()
{
    ;
}

void BreakStatement::analyze()
{
    ;
}

/*---------------------FunctionDeclaration---------------------*/

FunctionDeclaration::FunctionDeclaration() : Node(NodeClass::FUNCTION_DECLARATION)
{
}

void FunctionDeclaration::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::FUNCTION_DECLARATION));
    count();
    putEdge(id, getCounter(), "函数名");
    putLabel(name);
    count();
    putEdge(id, getCounter(), "返回值");
    putLabel(ValueTypeEnumMapToString(returnType));
}

void FunctionDeclaration::toIR()
{
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

void FunctionDeclaration::analyze()
{
    if (analyzerContext.exists(name))
    {
        Error::FunctionRedeclarationError(name).error();
    }
    analyzerContext.add(name, returnType);
}

/*---------------------ExpressionStatement---------------------*/

ExpressionStatement::ExpressionStatement() : Node(NodeClass::EXPRESSION_STATEMENT)
{
}

ExpressionStatement *ExpressionStatement::setValue(Value *_value)
{
    value = _value;
    return this;
}

Value *ExpressionStatement::getValue() const
{
    return value;
}

void ExpressionStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::EXPRESSION_STATEMENT));
    count();
    putEdge(id, getCounter(), "值");
    value->toMermaid();
}

void ExpressionStatement::toIR()
{
    value->toIR();
}

void ExpressionStatement::analyze()
{
    if (value->isDirect())
    {
        value = value->directify();
    }
}

/*---------------------COMPILAION_UNIT---------------------*/

CompilationUnit::CompilationUnit() : Node(NodeClass::COMPILATION_UNIT)
{
}

void CompilationUnit::toMermaid()
{
    mermaidHeader();
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::COMPILATION_UNIT));
    for (auto &node : nodes)
    {
        count();
        putEdge(id, getCounter(), NodeClassEnumMap[node->getNodeClass()]);
        node->toMermaid();
    }
    mermaidFooter();
}

CompilationUnit *CompilationUnit::setNodes(const std::vector<Node *> &_nodes)
{
    nodes = std::move(_nodes);
    return this;
}

std::vector<Node *> CompilationUnit::getNodes() const
{
    return nodes;
}

void CompilationUnit::toIR()
{
    for (auto &node : nodes)
    {
        node->toIR();
    }
    for (auto &ir : irs)
    {
        ir->output();
    }
}

void CompilationUnit::analyze()
{
    for (auto &node : nodes)
    {
        node->analyze();
    }
}

/*---------------------Block---------------------*/

Block::Block() : Node(NodeClass::BLOCK)
{
}

void Block::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::BLOCK));
    for (auto &node : nodes)
    {
        count();
        putEdge(id, getCounter(), NodeClassEnumMap[node->getNodeClass()]);
        node->toMermaid();
    }
}

void Block::analyze()
{
    analyzerContext.enter();
    for (auto &node : nodes)
    {
        node->analyze();
    }
    analyzerContext.exit();
}

void Block::toIR()
{
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

FunctionDefinition::FunctionDefinition() : Node(NodeClass::FUNCTION_DEFINITION)
{
}

void FunctionDefinition::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::FUNCTION_DEFINITION));
    count();
    putEdge(id, getCounter(), "函数声明");
    declaration->toMermaid();
    count();
    putEdge(id, getCounter(), "函数体");
    block->toMermaid();
}

void FunctionDefinition::analyze()
{
    if (analyzerContext.exists(declaration->getName()))
    {
        Error::FunctionRedeclarationError(declaration->getName()).error();
    }
    analyzerContext.add(declaration->getName(), declaration->getReturnType());
    block->analyze();
}

void FunctionDefinition::toIR()
{
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

ReturnStatement::ReturnStatement() : Node(NodeClass::RETURN_STATEMENT)
{
}

ReturnStatement *ReturnStatement::setValue(Value *_value)
{
    value = _value;
    return this;
}

Value *ReturnStatement::getValue() const
{
    return value;
}

void ReturnStatement::analyze()
{
    if (value == nullptr)
    {
        return;
    }
    if (value->isDirect())
    {
        value = value->directify();
    }
}

void ReturnStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::RETURN_STATEMENT));
    if (value == nullptr)
    {
        return;
    }
    count();
    putEdge(id, getCounter(), "值");
    value->toMermaid();
}

void ReturnStatement::toIR()
{
    if (value == nullptr)
    {
        irs.push_back((new IR::Return()));
        return;
    }
    else
    {
        value->toIR();
        irs.push_back((new IR::Return())->setVar(registerWrapper(getRegister())));
    }
}

/*WHILE*/

WhileStatement::WhileStatement() : Node(NodeClass::WHILE_STATEMENT)
{
}

WhileStatement *WhileStatement::setCondition(Value *_condition)
{
    condition = _condition;
    return this;
}

WhileStatement *WhileStatement::setBody(Node *_body)
{
    body = _body;
    return this;
}

void WhileStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::WHILE_STATEMENT));
    count();
    putEdge(id, getCounter(), "条件");
    condition->toMermaid();
    count();
    putEdge(id, getCounter(), "循环体");
    body->toMermaid();
}

void WhileStatement::toIR()
{
    nextLabel();
    size_t startLabel = getLabel();
    nextLabel();
    size_t endLabel = getLabel();
    irs.push_back((new IR::Label())->setName(labelWrapper(startLabel)));
    condition->toIR();
    irs.push_back((new IR::Ifz())->setRegisterSource(getRegister())->setLabel(endLabel));
    body->toIR();
    irs.push_back((new IR::Goto())->setLabel(labelWrapper(startLabel)));
    irs.push_back((new IR::Label())->setName(labelWrapper(endLabel)));
}

void WhileStatement::analyze()
{
    if (condition->getValueType() != ValueType::BOOLEAN)
    {
        Error::ConditionNotBoolError(condition->getValueType()).error();
        return;
    }
    body->analyze();
}

/*If*/

IfStatement::IfStatement() : Node(NodeClass::IF_STATEMENT)
{
}

IfStatement *IfStatement::setCondition(Value *_condition)
{
    condition = _condition;
    return this;
}

IfStatement *IfStatement::setThenBody(Node *_thenBody)
{
    thenBody = _thenBody;
    return this;
}

IfStatement *IfStatement::setElseBody(Node *_elseBody)
{
    elseBody = _elseBody;
    return this;
}

Value *IfStatement::getCondition() const
{
    return condition;
}

Node *IfStatement::getThenBody() const
{
    return thenBody;
}

Node *IfStatement::getElseBody() const
{
    return elseBody;
}

void IfStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(NodeClassEnumMapToString(NodeClass::IF_STATEMENT));
    count();
    putEdge(id, getCounter(), "条件");
    condition->toMermaid();
    count();
    putEdge(id, getCounter(), "then");
    thenBody->toMermaid();
    if (elseBody != nullptr)
    {
        count();
        putEdge(id, getCounter(), "else");
        elseBody->toMermaid();
    }
}

void IfStatement::toIR()
{
    condition->toIR();
    nextLabel();
    size_t ifz_label = getLabel();
    irs.push_back((new IR::Ifz())->setRegisterSource(getRegister())->setLabel(ifz_label));
    thenBody->toIR();
    if (elseBody != nullptr)
    {
        nextLabel();
        irs.push_back((new IR::Goto())->setLabel(labelWrapper(getLabel())));
        irs.push_back((new IR::Label())->setName(labelWrapper(ifz_label)));
        elseBody->toIR();
        irs.push_back((new IR::Label())->setName(labelWrapper(getLabel())));
    }
    else
    {
        irs.push_back((new IR::Label())->setName(labelWrapper(ifz_label)));
    }
}

void IfStatement::analyze()
{
    if (condition->getValueType() != ValueType::BOOLEAN)
    {
        Error::ConditionNotBoolError(condition->getValueType()).error();
        return;
    }
    thenBody->analyze();
    if (elseBody != nullptr)
    {
        elseBody->analyze();
    }
}

/*Continue*/

ContinueStatement::ContinueStatement() : Node(NodeClass::CONTINUE_STATEMENT)
{
}

void ContinueStatement::toMermaid()
{
    putLabel(NodeClassEnumMapToString(NodeClass::CONTINUE_STATEMENT));
}

void ContinueStatement::toIR()
{
    ;
}

void ContinueStatement::analyze()
{
    ;
}

} // namespace SED::AST
