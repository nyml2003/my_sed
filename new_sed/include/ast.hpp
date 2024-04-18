#ifndef SED_AST_HPP
#define SED_AST_HPP

#include <string>
#include <vector>
#include <array>
#include "generator.hpp"
#include "location.hh"
#include "error.hpp"
#include "ir.hpp"
#include "analyzer.hpp"

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
        FUNCTION_DEFINITION,
        EXPRESSION_STATEMENT,
        COMPILATION_UNIT,
        BLOCK,
        RETURN_STATEMENT,
        WHILE_STATEMENT,
        IF_STATEMENT,
        CONTINUE_STATEMENT,
    };
    extern std::map<NodeClass, std::string> NodeClassEnumMap;
    extern std::string NodeClassEnumMapToString(NodeClass nodeClass);

    class Node : public Generator::MermaidGenerator, public Generator::IRGenerator, public Analyzer::Analyzable
    {   
        NodeClass nodeClass;
    public:
        yy::position begin;
        yy::position end;
        Node(NodeClass _nodeClass);
        virtual void toMermaid() = 0;
        virtual void toIR() = 0;
        virtual void analyze() = 0;
        NodeClass getNodeClass() const;
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

        void toIR() override;

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

        void toIR() override;

        Variable *getVariable() const;

        RightValue *getValue() const;

        void analyze() override;
    };

    class BreakStatement : public Node
    {
    public:
        explicit BreakStatement();
        void toMermaid() override;

        void toIR() override;
        void analyze() override;
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
        void toIR() override;
        void analyze() override;
    };

    class ExpressionStatement : public Node
    {
        RightValue *value;
    public:
        explicit ExpressionStatement();
        ExpressionStatement *setValue(RightValue *_value);
        RightValue *getValue() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class CompilationUnit : public Node
    {
        std::vector<Node *> nodes;
    public:
        explicit CompilationUnit();
        CompilationUnit *setNodes(const std::vector<Node *> &_nodes);
        std::vector<Node *> getNodes() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class Block : public Node
    {
        std::vector<Node *> nodes;
    public:
        explicit Block();
        Block *setNodes(const std::vector<Node *> &_nodes);
        std::vector<Node *> getNodes() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class FunctionDefinition : public Node
    {
        FunctionDeclaration *declaration;
        Block *block;
    public:
        explicit FunctionDefinition();
        FunctionDefinition *setDeclaration(FunctionDeclaration *_declaration);
        FunctionDefinition *setBlock(Block *_block);
        FunctionDeclaration *getDeclaration() const;
        Block *getBlock() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class ReturnStatement : public Node
    {
        RightValue *value;
    public:
        explicit ReturnStatement();
        ReturnStatement *setValue(RightValue *_value);
        RightValue *getValue() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class WhileStatement : public Node
    {
        RightValue *condition;
        Node *body;

    public:

        explicit WhileStatement();
        WhileStatement *setCondition(RightValue *_condition);
        WhileStatement *setBody(Node *_body);
        RightValue *getCondition() const;
        Node *getBody() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class IfStatement : public Node
    {
        RightValue *condition;
        Node* thenBody;
        Node *elseBody;

    public:
        explicit IfStatement();
        IfStatement *setCondition(RightValue *_condition);
        IfStatement *setThenBody(Node *_thenBody);
        IfStatement *setElseBody(Node *_elseBody);
        RightValue *getCondition() const;
        Node *getThenBody() const;
        Node *getElseBody() const;
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };

    class ContinueStatement : public Node
    {
    public:
        explicit ContinueStatement();
        void toMermaid() override;
        void toIR() override;
        void analyze() override;
    };
};

#endif // SED_AST_HPP
