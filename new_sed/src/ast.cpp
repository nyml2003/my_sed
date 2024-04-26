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

Node::Node(Enumeration::NodeClass _nodeClass) : nodeClass(_nodeClass)
{
}

Enumeration::NodeClass Node::getNodeClass() const
{
    return nodeClass;
}

/*---------------------VARIABLE_DECLARATION---------------------*/

VariableDeclaration::VariableDeclaration() : Node(Enumeration::NodeClass::VARIABLE_DECLARATION)
{
}

/*set, get*/

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

VariableDeclaration *VariableDeclaration::setType(Enumeration::ValueType _type)
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

Enumeration::ValueType VariableDeclaration::getType() const
{
    return type;
}

bool VariableDeclaration::getCanReassign() const
{
    return canReassign;
}

/* 对于generator接口的实现 */

void VariableDeclaration::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "type");
    putLabel(type);
    nextCounter();
    putEdge(id, getCounter(), "variable");
    variable->toMermaid();
    if (value == nullptr)
    {
        return;
    }
    nextCounter();
    putEdge(id, getCounter(), "value");
    value->toMermaid();
}

void VariableDeclaration::toIR()
{
    irs.push_back((new IR::Var())->setName(variable->getName()));
    value->toIR();
    irs.push_back((new IR::Assign())->setLeftValue(variable->getName())->setRightValue(getRegister()));
}
// 文法: type variable = value
void VariableDeclaration::analyze()
{
    // 如果变量已经存在,则报错
    if (analyzerContext.exists(variable) == true)
    {
        Error::VariableRedeclarationError(variable->getName()).error();
        return;
    }
    // value一定有值
    if (value != nullptr)
    {
        // 比较value的类型和type是否一致
        if (value->getValueType() != type)
        {
            Error::TypeMismatchError(type, value->getValueType()).error();
            return;
        }
        // 剔除value的常量成分
        if (value->isConstant())
        {
            value = value->constantify();
        }
        // 在context中添加变量,但是不存储value的值
        analyzerContext.add(variable, Constant::createValue(type));
    }
    else
    {
        throw std::runtime_error("VariableDeclaration::analyze() value is nullptr");
    }
    return;
}

/*---------------------Assignment---------------------*/

Assignment::Assignment() : Node(Enumeration::NodeClass::ASSIGNMENT)
{
}
/*set, get*/

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

Variable *Assignment::getVariable() const
{
    return variable;
}

Value *Assignment::getValue() const
{
    return value;
}

void Assignment::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "variable");
    variable->toMermaid();
    nextCounter();
    putEdge(id, getCounter(), "value");
    value->toMermaid();
}

void Assignment::toIR()
{

    value->toIR();
    irs.push_back((new IR::Assign())->setLeftValue(variable->getName())->setRightValue(getRegister()));
}

void Assignment::analyze()
{
    // 如果变量不存在,则报错
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
    if (value->isConstant())
    {
        value = value->constantify();
    }
    // 如果变量的类型和value的类型不一致,则报错
}

/*---------------------BreakStatement---------------------*/

BreakStatement::BreakStatement() : Node(Enumeration::NodeClass::BREAK_STATEMENT)
{
}

void BreakStatement::toMermaid()
{
    putLabel(getNodeClass());
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

FunctionDeclaration::FunctionDeclaration() : Node(Enumeration::NodeClass::FUNCTION_DECLARATION)
{
}
/*set, get*/
FunctionDeclaration *FunctionDeclaration::setName(const std::string &_name)
{
    name = _name;
    return this;
}

FunctionDeclaration *FunctionDeclaration::setReturnType(Enumeration::ValueType _returnType)
{
    returnType = _returnType;
    return this;
}

std::string FunctionDeclaration::getName() const
{
    return name;
}

Enumeration::ValueType FunctionDeclaration::getReturnType() const
{
    return returnType;
}

void FunctionDeclaration::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "name");
    putLabel(name);
    nextCounter();
    putEdge(id, getCounter(), "returnType");
    putLabel(returnType);
}

void FunctionDeclaration::toIR()
{
    irs.push_back((new IR::Label())->setName(name));
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

ExpressionStatement::ExpressionStatement() : Node(Enumeration::NodeClass::EXPRESSION_STATEMENT)
{
}

/*set, get*/

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
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "value");
    value->toMermaid();
}

void ExpressionStatement::toIR()
{
    value->toIR();
}

void ExpressionStatement::analyze()
{
    if (value->isConstant())
    {
        value = value->constantify();
    }
}

/*---------------------COMPILAION_UNIT---------------------*/

CompilationUnit::CompilationUnit() : Node(Enumeration::NodeClass::COMPILATION_UNIT)
{
}

/*set, get*/
CompilationUnit *CompilationUnit::setNodes(const std::vector<Node *> &_nodes)
{
    nodes = std::move(_nodes);
    return this;
}

std::vector<Node *> CompilationUnit::getNodes() const
{
    return nodes;
}

void CompilationUnit::toMermaid()
{
    mermaidHeader();
    size_t id = getCounter();
    putLabel(getNodeClass());
    for (auto &node : nodes)
    {
        nextCounter();
        putEdge(id, getCounter());
        node->toMermaid();
    }
    mermaidFooter();
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

Block::Block() : Node(Enumeration::NodeClass::BLOCK)
{
}

/*set, get*/
Block *Block::setNodes(const std::vector<Node *> &_nodes)
{
    nodes = std::move(_nodes);
    return this;
}

std::vector<Node *> Block::getNodes() const
{
    return nodes;
}

void Block::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    for (auto &node : nodes)
    {
        nextCounter();
        putEdge(id, getCounter());
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

/*---------------------FunctionDefinition---------------------*/

FunctionDefinition::FunctionDefinition() : Node(Enumeration::NodeClass::FUNCTION_DEFINITION)
{
}

void FunctionDefinition::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "declaration");
    declaration->toMermaid();
    nextCounter();
    putEdge(id, getCounter(), "block");
    block->toMermaid();
}

void FunctionDefinition::analyze()
{
    declaration->analyze();
    block->analyze();
}

void FunctionDefinition::toIR()
{
    declaration->toIR();
    irs.push_back((new IR::Start()));
    block->toIR();
    irs.push_back((new IR::End()));
}

/*set, get*/

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

Block *FunctionDefinition::getBlock() const
{
    return block;
}

/*---------------------ReturnStatement---------------------*/

ReturnStatement::ReturnStatement() : Node(Enumeration::NodeClass::RETURN_STATEMENT)
{
}

/*set, get*/

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
    if (value->isConstant())
    {
        value = value->constantify();
    }
}

void ReturnStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    if (value == nullptr)
    {
        return;
    }
    nextCounter();
    putEdge(id, getCounter(), "value");
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

WhileStatement::WhileStatement() : Node(Enumeration::NodeClass::WHILE_STATEMENT)
{
}

WhileStatement *WhileStatement::setCondition(Value *_condition)
{
    condition = _condition;
    return this;
}

WhileStatement *WhileStatement::setBody(Block *_body)
{
    body = _body;
    return this;
}

Value *WhileStatement::getCondition() const
{
    return condition;
}

Block *WhileStatement::getBody() const
{
    return body;
}

void WhileStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "condition");
    condition->toMermaid();
    nextCounter();
    putEdge(id, getCounter(), "body");
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
    if (condition->getValueType() != Enumeration::ValueType::BOOLEAN)
    {
        Error::ConditionNotBoolError(condition->getValueType()).error();
        return;
    }
    body->analyze();
}

/*If*/

IfStatement::IfStatement() : Node(Enumeration::NodeClass::IF_STATEMENT)
{
}
/*set, get*/

IfStatement *IfStatement::setCondition(Value *_condition)
{
    condition = _condition;
    return this;
}

IfStatement *IfStatement::setThenBody(Block *_thenBody)
{
    thenBody = _thenBody;
    return this;
}

IfStatement *IfStatement::setElseBody(Block *_elseBody)
{
    elseBody = _elseBody;
    return this;
}

Value *IfStatement::getCondition() const
{
    return condition;
}

Block *IfStatement::getThenBody() const
{
    return thenBody;
}

Block *IfStatement::getElseBody() const
{
    return elseBody;
}

void IfStatement::toMermaid()
{
    size_t id = getCounter();
    putLabel(getNodeClass());
    nextCounter();
    putEdge(id, getCounter(), "condition");
    condition->toMermaid();
    nextCounter();
    putEdge(id, getCounter(), "then");
    thenBody->toMermaid();
    if (elseBody != nullptr)
    {
        nextCounter();
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
    if (condition->getValueType() != Enumeration::ValueType::BOOLEAN)
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

ContinueStatement::ContinueStatement() : Node(Enumeration::NodeClass::CONTINUE_STATEMENT)
{
}

void ContinueStatement::toMermaid()
{
    putLabel(getNodeClass());
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
