
#ifndef SED_CONTEXT_HPP
#define SED_CONTEXT_HPP
#include "ast.hpp"
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
namespace SED
{
namespace AST
{
class Constant;
class FunctionCall;
} // namespace AST
namespace Context
{
struct AnalyzerContext
{
    AnalyzerContext();
    std::vector<std::map<std::string, AST::Constant *>> variables;
    std::vector<std::map<std::string, std::vector<Enumeration::ValueType>>> functions;
    std::stack<AST::Node *> nodeStack;
    AST::FunctionDeclaration *currentFunction = nullptr;
    void add(std::string name, AST::Constant *value);
    void add(std::string name, std::vector<Enumeration::ValueType> parameters);
    AST::Constant *get(AST::Variable *variable);
    std::vector<Enumeration::ValueType> get(AST::FunctionCall *function);
    std::vector<Enumeration::ValueType> get(AST::FunctionDeclaration *function);
    bool exists(AST::Variable *variable);
    bool exists(AST::FunctionCall *function);
    bool exists(AST::FunctionDeclaration *function);
    void enter();
    void exit();
    bool isGloabl();
};
} // namespace Context

} // namespace SED
inline SED::Context::AnalyzerContext analyzerContext;

#endif // SED_CONTEXT_HPP