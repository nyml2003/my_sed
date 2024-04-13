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
        {NodeClass::EXPRESSION_STATEMENT, "ExpressionStatement"}};

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

    void VariableDeclaration::interpret()
    {
        try
        {
            ValueType valueType = value->getValueType();

            if (valueType != type)
            {
                Error::TypeMismatchError(type, valueType).error();
                return;
            }
            auto valueDirect = value->directify();
            analyzerContext.add(variable, valueDirect);
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
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

    void Assignment::interpret()
    {
        if (analyzerContext.exists(variable) == false)
        {
            Error::UndefinedVariableError(variable->getName()).error();
            return;
        }
        if (analyzerContext.get(variable)->getValueType() != value->getValueType())
        {
            Error::TypeMismatchError(analyzerContext.get(variable)->getValueType(), value->getValueType()).error();
            return;
        }
        try
        {
            auto valueDirect = value->directify();
            analyzerContext.set(variable, valueDirect);
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
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

    void BreakStatement::interpret()
    {
        exit(0);
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

    void FunctionDeclaration::interpret()
    {
        try{
            if (analyzerContext.exists(name))
            {
                Error::FunctionRedeclarationError(name).error();
                return;
            }
            analyzerContext.add(name, returnType);
        }catch(std::runtime_error &e){
            std::cerr << e.what() << std::endl;
        }
        
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

    void ExpressionStatement::interpret()
    {
        try{
            auto valueDirect = value->directify();
            value = valueDirect;
            value->interpret();
        }catch(std::runtime_error &e){
            std::cerr << e.what() << std::endl;
        }
    }

}
