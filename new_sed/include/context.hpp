
#ifndef SED_CONTEXT_HPP
#define SED_CONTEXT_HPP
#include "ast.hpp"
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
namespace SED
{
namespace AST
{
class Constant;
}
namespace Context
{
struct AnalyzerContext
{
    AnalyzerContext();
    std::vector<std::map<std::string, AST::Constant *>> variables;
    std::vector<std::map<std::string, Enumeration::ValueType>> functions;
    void add(AST::Variable *variable, AST::Constant *value);
    void add(std::string name, Enumeration::ValueType type);
    AST::Constant *get(AST::Variable *variable);
    Enumeration::ValueType get(std::string name);
    bool exists(AST::Variable *variable);
    bool exists(std::string name);
    void set(AST::Variable *variable, AST::Constant *value);
    void enter();
    void exit();
    bool isGloabl();
};
} // namespace Context
} // namespace SED
inline SED::Context::AnalyzerContext analyzerContext;
#endif // SED_CONTEXT_HPP