#ifndef SED_AST_HPP
#define SED_AST_HPP

#include <string>
#include <vector>
#include <array>
#include "generator.hpp"
#include "location.hh"
#include "errorDump.hpp"
#include "interpreter.hpp"

namespace SED::AST
{
    class Value;
    class RightValue;
    class Variable;
    enum class ValueType;

    enum class NodeClass
    {
        VARIABLE_DECLARATION,
        ASSIGNMENT,
        INT_32,
        FLOAT_32,
        BOOLEAN,
        POINTER,
        UNARY,
        BINARY,
        VARIABLE,
        VOID,
        BREAK_STATEMENT,
        FUNCTION_CALL,
        FUNCTION_DECLARATION,
    };

    class Node : public Generator::MermaidGenerator, public Error::ErrorDump, public Interpreter
    {
        NodeClass nodeClass;
        
    public:
        yy::position begin;
        yy::position end;
        Node(NodeClass _nodeClass);
        virtual void toMermaid() = 0;
        NodeClass getNodeClass() const;
        Node *setNodeClass(NodeClass _nodeClass);
        void dump(const std::string &message, Error::ErrorType errorType = Error::ErrorType::ERROR) override;
        void interpret() override = 0;
    };

    class VariableDeclaration : public Node
    {
        ValueType type;
        Variable *variable;
        RightValue *value;
        bool isConst;

    public:
        explicit VariableDeclaration();

        VariableDeclaration *setVariable(Variable *_variable);

        VariableDeclaration *setValue(RightValue *_value);

        VariableDeclaration *setType(ValueType _type);

        VariableDeclaration *setIsConst(bool _isConst);

        Variable *getVariable() const;

        RightValue *getValue() const;

        ValueType getType() const;

        bool getIsConst() const;

        void toMermaid() override;

        void interpret() override;

    };

    class Assignment : public Node
    {
        Variable *variable;
        RightValue *value;

    public:
        explicit Assignment();

        Assignment *setVariable(Variable *_variable);

        Assignment *setValue(RightValue *_value);

        void toMermaid() override;

        Variable *getVariable() const;

        RightValue *getValue() const;

        void interpret() override;
    };

    class BreakStatement : public Node
    {
    public:
        explicit BreakStatement();
        void toMermaid() override;
        void interpret() override;
    };

    class FunctionDeclaration : public Node
    {
        ValueType returnType;
        std::string name;
        
    public:
        explicit FunctionDeclaration();
        FunctionDeclaration *setReturnType(ValueType _returnType);
        FunctionDeclaration *setName(const std::string &_name);
        ValueType getReturnType() const;
        std::string getName() const;
        void toMermaid() override;
        void interpret() override;
    };


};

#endif // SED_AST_HPP
