
#ifndef SED_GENERATOR_HPP
#define SED_GENERATOR_HPP
#include <map>
#include <stack>
#include <string>
namespace SED::AST
{
enum class Operator;
enum class NodeClass;
enum class ValueType;
} // namespace SED::AST

namespace SED::Generator
{

class MermaidGenerator
{
    static size_t counter;

  public:
    static size_t count();
    static size_t getCounter();
    static void refreshCounter();
    static void mermaidHeader();
    static void mermaidFooter();
    virtual void toMermaid() = 0;
    static void putEdge();
    static void putEdge(const std::string &message);
    static void putEdge(size_t from, size_t to);
    static void putEdge(size_t from, size_t to, const std::string &message);
    static void putLabel(const std::string &label);
};

class IRGenerator
{
    static size_t registerCounter;
    static size_t labelCounter;

  public:
    virtual void toIR() = 0;
    static size_t getRegister();
    static void nextRegister();
    static size_t getLabel();
    static void nextLabel();
    static std::string registerWrapper(size_t register_id);
    static std::string labelWrapper(size_t label_id);
};
} // namespace SED::Generator

#endif // SED_GENERATOR_HPP
