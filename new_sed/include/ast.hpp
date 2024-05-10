
#ifndef SED_AST_HPP
#define SED_AST_HPP
#include "analyzer.hpp"
#include "enumeration.hpp"
#include "error.hpp"
#include "generator.hpp"
#include "ir.hpp"
#include "location.hh"
#include <array>
#include <string>
#include <vector>
namespace SED::AST
{
class Value;
class Variable;

class Node : public Generator::MermaidGenerator, public Generator::IRGenerator, public Analyzer::Analyzable
{
  private:
    Enumeration::NodeClass nodeClass;

  public:
    yy::position begin;
    yy::position end;
    Node(Enumeration::NodeClass _nodeClass);
    Enumeration::NodeClass getNodeClass() const;
    virtual void toMermaid() = 0;
    virtual void toIR() = 0;
    virtual void analyze() = 0;
};
/**
 * @brief 变量声明
 * (const) int a = 1;
 * TODO: 1. 支持const
 * TODO: 2. 语义分析不完整, 需要继续考虑
 */
class VariableDeclaration : public Node
{
  private:
    Enumeration::ValueType type;
    Variable *variable;
    Value *value;
    bool canReassign;

  public:
    explicit VariableDeclaration();

    /*set, get*/

    VariableDeclaration *setVariable(Variable *_variable);

    VariableDeclaration *setValue(Value *_value);

    VariableDeclaration *setType(Enumeration::ValueType _type);

    VariableDeclaration *setCanReassign(bool _canReassign);

    Variable *getVariable() const;

    Value *getValue() const;

    Enumeration::ValueType getType() const;

    bool getCanReassign() const;

    /* 对于generator接口的实现 */

    void toMermaid() override;

    void toIR() override;

    /* 对于analyzer接口的实现 */

    void analyze() override;
};

class Assignment : public Node
{
  private:
    Variable *variable;
    Value *value;

  public:
    explicit Assignment();
    /*set, get*/

    Assignment *setVariable(Variable *_variable);

    Assignment *setValue(Value *_value);

    Variable *getVariable() const;

    Value *getValue() const;

    /* 对于generator接口的实现 */

    void toMermaid() override;

    void toIR() override;

    /* 对于analyzer接口的实现 */

    void analyze() override;
};

class BreakStatement : public Node
{
  public:
    explicit BreakStatement();
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class FunctionDeclaration : public Node
{
  private:
    std::vector<Enumeration::ValueType> parameters;
    Enumeration::ValueType returnType;
    std::string name;

  public:
    explicit FunctionDeclaration();
    /*set, get*/
    FunctionDeclaration *setReturnType(Enumeration::ValueType _returnType);
    FunctionDeclaration *setName(const std::string &_name);
    FunctionDeclaration *setParameters(const std::vector<Enumeration::ValueType> &_parameters);
    Enumeration::ValueType getReturnType() const;
    std::string getName() const;
    std::vector<Enumeration::ValueType> getParameters() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class ExpressionStatement : public Node
{
  private:
    Value *value;

  public:
    explicit ExpressionStatement();
    /*set, get*/
    ExpressionStatement *setValue(Value *_value);
    Value *getValue() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class CompilationUnit : public Node
{
  private:
    std::vector<Node *> nodes;

  public:
    explicit CompilationUnit();
    /*set, get*/
    CompilationUnit *setNodes(const std::vector<Node *> &_nodes);
    std::vector<Node *> getNodes() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class Block : public Node
{
  private:
    std::vector<Node *> nodes;

  public:
    explicit Block();
    size_t beginLine = 0;
    /*set, get*/
    Block *setNodes(const std::vector<Node *> &_nodes);
    std::vector<Node *> getNodes() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class ReturnStatement : public Node
{
  private:
    Value *value;

  public:
    explicit ReturnStatement();
    /*set, get*/
    ReturnStatement *setValue(Value *_value);
    Value *getValue() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class FunctionDefinition : public Node
{
  private:
    FunctionDeclaration *declaration;
    std::vector<VariableDeclaration *> parameters;
    Block *block;
    ReturnStatement *returnStatement;

  public:
    explicit FunctionDefinition();
    /*set, get*/
    FunctionDefinition *setDeclaration(FunctionDeclaration *_declaration);
    FunctionDefinition *setBlock(Block *_block);
    FunctionDefinition *setParameters(const std::vector<VariableDeclaration *> &_parameters);
    FunctionDeclaration *getDeclaration() const;
    Block *getBlock() const;
    std::vector<VariableDeclaration *> getParameters() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class WhileStatement : public Node
{
  private:
    Value *condition;
    Block *body;

  public:
    explicit WhileStatement();
    /*set, get*/
    WhileStatement *setCondition(Value *_condition);
    WhileStatement *setBody(Block *_body);
    Value *getCondition() const;
    Block *getBody() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class IfStatement : public Node
{
  private:
    Value *condition;
    Block *thenBody;
    Block *elseBody;

  public:
    explicit IfStatement();
    /*set, get*/
    IfStatement *setCondition(Value *_condition);
    IfStatement *setThenBody(Block *_thenBody);
    IfStatement *setElseBody(Block *_elseBody);
    Value *getCondition() const;
    Block *getThenBody() const;
    Block *getElseBody() const;
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};

class ContinueStatement : public Node
{
  public:
    explicit ContinueStatement();
    /* 对于generator接口的实现 */
    void toMermaid() override;
    void toIR() override;
    /* 对于analyzer接口的实现 */
    void analyze() override;
};
}; // namespace SED::AST

#endif // SED_AST_HPP
