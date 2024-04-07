#ifndef SED_AST_HPP
#define SED_AST_HPP

#include <string>
#include <vector>
#include <array>
#include "generator.hpp"
#include "analyzer.hpp"
#include "location.hh"
#include "errorDump.hpp"

namespace SED::AST
{
    class Value;
    class RightValue;
    class Variable;
    enum class ValueType;

    enum class NodeClass
    {
        COMPILATION_UNIT,
        VARIABLE_DECLARATION,
        ASSIGNMENT,
        FUNCTION,
        BLOCK,
        RETURN_STATEMENT,
        INT_32,
        FLOAT_32,
        BOOLEAN,
        POINTER,
        UNARY,
        BINARY,
        VARIABLE,
        VOID,
        FUNCTION_CALL,
        IF_STATEMENT,
        WHILE_STATEMENT,
        BREAK_STATEMENT,
        CONTINUE_STATEMENT,
        ARGUMENT,
    };

    class Node : public Generator::MermaidGenerator, public Analyzable, public ErrorDump
    {
        NodeClass nodeClass;
        
    public:
        yy::position begin;
        yy::position end;
        Node(NodeClass _nodeClass);
        virtual void toMermaid() = 0;
        NodeClass getNodeClass() const;
        Node *setNodeClass(NodeClass _nodeClass);
        virtual bool isBlock();
        void dump(const std::string &message) override;
    };

    class CompilationUnit : public Node
    {
        std::vector<Node *> children{};

    public:
        explicit CompilationUnit();
        CompilationUnit *setChildren(std::vector<Node *> _children);
        std::vector<Node *> &getChildren();
        void toMermaid() override;
        void analyze() override;
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

        void analyze() override;
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

        void analyze() override;
    };

    class Block : public Node
    {
        std::vector<Node *> children;

    public:
        explicit Block();

        Block *setChildren(std::vector<Node *> _children);

        std::vector<Node *> &getChildren();
        void toMermaid() override;
        void analyze() override;

        bool isBlock() override;

        static Block *blockify(Node *node);
    };

    class Argument : public Node
    {
        ValueType type;
        Variable *variable;

    public:
        explicit Argument();

        Argument *setType(ValueType _type);

        Argument *setVariable(Variable *_variable);

        void toMermaid() override;

        void analyze() override;

        ValueType getType() const;

        Variable *getVariable() const;
    };

    class Function : public Node
    {
        std::string name;
        ValueType returnType;
        std::vector<Argument *> parameters;
        Block *block;

    public:
        explicit Function();

        Function *setName(std::string _name);

        Function *setReturnType(ValueType _returnType);

        Function *setBlock(Block *_block);

        Function *setParameters(std::vector<Argument *> _parameters);

        void toMermaid() override;
        void analyze() override;

        const std::string &getName() const;

        ValueType getReturnType() const;

        Block *getBlock() const;

        const std::vector<Argument *> &getParameters() const;
    };

    class ReturnStatement : public Node
    {
        RightValue *value;

    public:
        explicit ReturnStatement();

        ReturnStatement *setValue(RightValue *_value);

        void toMermaid() override;
        RightValue *getValue() const;
        void analyze() override;
    };

    class IfStatement : public Node
    {
        RightValue *condition;
        Block *thenBlock;
        Block *elseBlock;

    public:
        explicit IfStatement();

        IfStatement *setCondition(RightValue *_condition);

        IfStatement *setThenBlock(Block *_thenBlock);

        IfStatement *setElseBlock(Block *_elseBlock);

        void toMermaid() override;

        void analyze() override;

        RightValue *getCondition() const;

        Block *getThenBlock() const;
    };

    class WhileStatement : public Node
    {
        RightValue *condition;
        Block *block;

    public:
        explicit WhileStatement();

        WhileStatement *setCondition(RightValue *_condition);

        WhileStatement *setBlock(Block *_block);

        void toMermaid() override;

        void analyze() override;

        RightValue *getCondition() const;

        Block *getBlock() const;
    };

    class BreakStatement : public Node
    {
    public:
        explicit BreakStatement();
        void toMermaid() override;
        void analyze() override;
    };

    class ContinueStatement : public Node
    {
    public:
        explicit ContinueStatement();
        void toMermaid() override;
        void analyze() override;
    };

};

#endif // SED_AST_HPP
