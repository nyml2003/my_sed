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
#include "errorDump.hpp"

namespace SED::AST {

    /*---------------------Node---------------------*/

    Node::Node(NodeClass _nodeClass) : nodeClass(_nodeClass) {
    }

    void Node::dump(const std::string &message, Error::ErrorType errorType) {
        
        // 根据errorType的不同，输出不同的颜色，在控制台中显示 std::cerr
        switch (errorType) {
            case Error::ErrorType::ERROR:
                std::cerr << "\033[31mError: \033[0m" << message << std::endl;
                exit(1);
                break;
            case Error::ErrorType::WARNING:
                std::cerr << "\033[33mWarning: \033[0m" << message << ",the statement will be ignored" << std::endl;
                break;
            case Error::ErrorType::INFO:
                std::cout << "\033[34mINFO: \033[0m" << message << std::endl;
                break;
            default:
                std::cerr << "Unknown Error" << std::endl;
                break;
        }
    }

    void Node::dump(const std::vector<std::string> &messages, Error::ErrorType errorType) {
        for (const auto &message : messages) {
            dump(message, errorType);
        }
        exit(1);
    }

    NodeClass Node::getNodeClass() const {
        return nodeClass;
    }

    Node *Node::setNodeClass(NodeClass _nodeClass) {
        nodeClass = _nodeClass;
        return this;
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

    void VariableDeclaration::interpret(){
            if (value->getValueType() != type) {
                dump("the type of variable " + variable->getName() + " is " + Generator::ValueTypeToMermaid::toMermaid(type), Error::ErrorType::INFO);
                dump("the type of value is " + Generator::ValueTypeToMermaid::toMermaid(value->getValueType()), Error::ErrorType::INFO);
                dump("type mismatch", Error::ErrorType::WARNING);
                return;
            }
            auto valueDirect = value->directify();
            try{
                analyzerContext.add(variable, valueDirect);
            }catch(std::runtime_error &e){
                dump(e.what(), Error::ErrorType::WARNING);
            }
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
        count();
        putEdge(id, getCounter(), "值");
        value->toMermaid();
    }

    void Assignment::interpret() {
        if (analyzerContext.exists(variable) == false) {
            dump("the identifier " + variable->getName() + " is not declared", Error::ErrorType::WARNING);
            return;
        }
        if (analyzerContext.get(variable)->getValueType() != value->getValueType()) {
            dump("the type of variable " + variable->getName() + " is " + Generator::ValueTypeToMermaid::toMermaid(analyzerContext.get(variable)->getValueType()), Error::ErrorType::INFO);
            dump("the type of value is " + Generator::ValueTypeToMermaid::toMermaid(value->getValueType()), Error::ErrorType::INFO);
            dump("type mismatch", Error::ErrorType::WARNING);
            return;
        }
        auto valueDirect = value->directify();
        analyzerContext.set(variable, valueDirect);
    }

    Variable *Assignment::getVariable() const {
        return variable;
    }

    RightValue *Assignment::getValue() const {
        return value;
    }

    /*---------------------BreakStatement---------------------*/

    BreakStatement::BreakStatement() : Node(NodeClass::BREAK_STATEMENT) {}

    void BreakStatement::toMermaid() {
        putLabel(NodeClass::BREAK_STATEMENT);
    }

    void BreakStatement::interpret() {
        exit(0);
    }
}
