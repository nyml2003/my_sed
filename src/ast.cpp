//
// Created by venty on 2024/3/24.
//

#include <iostream>
#include "ast.hpp"
#include "generator.hpp"
#include "value.hpp"
#include "context.hpp"


namespace SED::AST {

    /*---------------------Node---------------------*/

    Node::Node(NodeClass _nodeClass) : nodeClass(_nodeClass) {}

    NodeClass Node::getNodeClass() const {
        return nodeClass;
    }

    Node *Node::setNodeClass(NodeClass _nodeClass) {
        nodeClass = _nodeClass;
        return this;
    }

    bool Node::isBlock() {
        return false;
    }

    /*---------------------COMPILATION_UNIT---------------------*/

    CompilationUnit::CompilationUnit() : Node(NodeClass::COMPILATION_UNIT) {}

    CompilationUnit *CompilationUnit::setChildren(std::vector<Node *> _children) {
        children = std::move(_children);
        return this;
    }

    std::vector<Node *> &CompilationUnit::getChildren() {
        return children;
    }

    void CompilationUnit::toMermaid() {
        mermaidHeader();
        size_t id = getCounter();
        putLabel(NodeClass::COMPILATION_UNIT);
        for (size_t i = 0; i < children.size(); i++) {
            count();
            putEdge(id, getCounter(), "顶级语句" + std::to_string(i));
            children[i]->toMermaid();
        }
        mermaidFooter();
    }

    void CompilationUnit::analyze() {
        analyzerContext.enter();
        for (auto &child : children) {
            child->analyze();
        }
        analyzerContext.leave();
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
        if (value == nullptr) {
            return;
        }
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    VariableDeclaration *VariableDeclaration::setVariable(Variable *_variable) {
        variable = _variable;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setValue(RightValue *_value)
    {
        value = _value;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setType(ValueType _type) {
        type = _type;
        return this;
    }

    VariableDeclaration *VariableDeclaration::setIsConst(bool _isConst) {
        isConst = _isConst;
        return this;
    }

    Variable *VariableDeclaration::getVariable() const {
        return variable;
    }

    RightValue* VariableDeclaration::getValue() const {
        return value;
    }

    ValueType VariableDeclaration::getType() const {
        return type;
    }

    bool VariableDeclaration::getIsConst() const {
        return isConst;
    }

    void VariableDeclaration::analyze() {
        bool isDirect = value->isDirect();
        if (isConst && !isDirect) {
            throw std::runtime_error("常量必须是直接值");
        }
        if (isDirect) {
            value = value->directify();
            analyzerContext.add(variable, value->directify());
        }
    }

    /*---------------------Assignment---------------------*/


    Assignment::Assignment() : Node(NodeClass::ASSIGNMENT){}

    Assignment *Assignment::setVariable(Variable *_variable) {
        variable = _variable;
        return this;
    }

    Assignment *Assignment::setValue(RightValue *_value) {
        value = _value;
        return this;
    }

    void Assignment::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::ASSIGNMENT);
        count();
        putEdge(id, getCounter(), "变量");
        variable->toMermaid();
        if (value == nullptr) {
            return;
        }
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    Variable *Assignment::getVariable() const {
        return variable;
    }

    RightValue *Assignment::getValue() const {
        return value;
    }

    void Assignment::analyze() {
        if (value->isDirect()) {
            value = value->directify();
            analyzerContext.set(variable, value->directify());
        }else{
            analyzerContext.set(variable, nullptr);
        }
    }

    /*---------------------Block---------------------*/


    Block::Block() : Node(NodeClass::BLOCK) {}

    bool Block::isBlock() {
        return true;
    }

    Block *Block::setChildren(std::vector<Node *> _children) {
        children = std::move(_children);
        return this;
    }

    void Block::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::BLOCK);
        for (size_t i = 0; i < children.size(); i++) {
            count();
            putEdge(id, getCounter(), "语句" + std::to_string(i));
            children[i]->toMermaid();
        }
    }

    std::vector<Node *> &Block::getChildren() {
        return children;
    }

    void Block::analyze() {
        analyzerContext.enter();
        for (auto &child : children) {
            child->analyze();
        }
        analyzerContext.leave();
    }

    Block* Block::blockify(Node *node) {
        if (node->isBlock()) {
            return dynamic_cast<Block *>(node);
        }
        return (new Block())->setChildren({node});
    }

    /*---------------------Function---------------------*/

    Function::Function() : Node(NodeClass::FUNCTION) {}

    Function *Function::setName(std::string _name) {
        name = std::move(_name);
        return this;
    }

    Function *Function::setBlock(Block *_block) {
        block = _block;
        return this;
    }

    Function *Function::setReturnType(ValueType _returnType) {
        returnType = _returnType;
        return this;
    }

    Function *Function::setParameters(std::vector<Argument *> _parameters) {
        parameters = std::move(_parameters);
        return this;
    }

    void Function::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::FUNCTION);
        count();
        putEdge(id, getCounter(), "函数名");
        putLabel(name);
        count();
        putEdge(id, getCounter(), "返回值类型");
        putLabel(returnType);
        for (size_t i = 0; i < parameters.size(); i++) {
            count();
            putEdge(id, getCounter(), "参数" + std::to_string(i));
            parameters[i]->toMermaid();
        }
        count();
        putEdge(id, getCounter(), "函数体");
        block->toMermaid();
    }

    const std::string &Function::getName() const {
        return name;
    }

    ValueType Function::getReturnType() const {
        return returnType;
    }

    Block* Function::getBlock() const {
        return block;
    }

    const std::vector<Argument *> &Function::getParameters() const {
        return parameters;
    }

    void Function::analyze() {
        analyzerContext.add(this);
        analyzerContext.enter();
        for (auto &parameter : parameters) {
            analyzerContext.add(parameter->getVariable(), nullptr);
        }
        for (auto &child : block->getChildren()) {
            child->analyze();
        }
        analyzerContext.leave();
    }

    /*---------------------ReturnStatement---------------------*/

    ReturnStatement::ReturnStatement() : Node(NodeClass::RETURN_STATEMENT) {}

    ReturnStatement *ReturnStatement::setValue(RightValue *_value) {
        value = _value;
        return this;
    }

    void ReturnStatement::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::RETURN_STATEMENT);
        count();
        putEdge(id, getCounter(), "返回值");
        value->toMermaid();
    }

    RightValue *ReturnStatement::getValue() const {
        return value;
    }

    void ReturnStatement::analyze() {
        if (value->isDirect()) value = value->directify();
    }

    /*---------------------IfStatement---------------------*/

    IfStatement::IfStatement() : Node(NodeClass::IF_STATEMENT) {}

    IfStatement *IfStatement::setCondition(RightValue *_condition) {
        condition = _condition;
        return this;
    }

    IfStatement *IfStatement::setThenBlock(Block *_thenBlock) {
        thenBlock = _thenBlock;
        return this;
    }

    IfStatement *IfStatement::setElseBlock(Block *_elseBlock) {
        elseBlock = _elseBlock;
        return this;
    }

    void IfStatement::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::IF_STATEMENT);
        count();
        putEdge(id, getCounter(), "条件");
        condition->toMermaid();
        count();
        putEdge(id, getCounter(), "then");
        thenBlock->toMermaid();
        if (elseBlock == nullptr) {
            return;
        }
        count();
        putEdge(id, getCounter(), "else");
        elseBlock->toMermaid();
    }

    RightValue *IfStatement::getCondition() const {
        return condition;
    }

    Block *IfStatement::getThenBlock() const {
        return thenBlock;
    }

    void IfStatement::analyze() {
        thenBlock->analyze();
        if (elseBlock != nullptr) {
            elseBlock->analyze();
        }
    }

    /*---------------------WhileStatement---------------------*/

    WhileStatement::WhileStatement() : Node(NodeClass::WHILE_STATEMENT) {}

    WhileStatement *WhileStatement::setCondition(RightValue *_condition) {
        condition = _condition;
        return this;
    }

    WhileStatement *WhileStatement::setBlock(Block *_block) {
        block = _block;
        return this;
    }

    void WhileStatement::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::WHILE_STATEMENT);
        count();
        putEdge(id, getCounter(), "条件");
        condition->toMermaid();
        count();
        putEdge(id, getCounter(), "循环体");
        block->toMermaid();
    }

    RightValue *WhileStatement::getCondition() const {
        return condition;
    }

    Block *WhileStatement::getBlock() const {
        return block;
    }

    void WhileStatement::analyze() {
        block->analyze();
    }

    /*---------------------BreakStatement---------------------*/

    BreakStatement::BreakStatement() : Node(NodeClass::BREAK_STATEMENT) {}

    void BreakStatement::toMermaid() {
        putLabel(NodeClass::BREAK_STATEMENT);
    }

    void BreakStatement::analyze() {}

    /*---------------------ContinueStatement---------------------*/

    ContinueStatement::ContinueStatement() : Node(NodeClass::CONTINUE_STATEMENT) {}

    void ContinueStatement::toMermaid() {
        putLabel(NodeClass::CONTINUE_STATEMENT);
    }

    void ContinueStatement::analyze() {}

    /*---------------------Argument---------------------*/

    Argument::Argument() : Node(NodeClass::ARGUMENT) {}

    Argument *Argument::setVariable(Variable *_variable) {
        variable = _variable;
        return this;
    }

    Argument *Argument::setType(ValueType _type) {
        type = _type;
        return this;
    }

    void Argument::toMermaid() {
        size_t id = getCounter();
        putLabel(NodeClass::ARGUMENT);
        count();
        putEdge(id, getCounter(), "类型");
        putLabel(type);
        count();
        putEdge(id, getCounter(), "变量");
        variable->toMermaid();
    }

    Variable *Argument::getVariable() const {
        return variable;
    }

    ValueType Argument::getType() const {
        return type;
    }

    /**
     * @brief 语义分析中不存在Argument
    **/
    void Argument::analyze() {
        ;
    }
}
