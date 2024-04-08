#ifndef SED_GENERATOR_HPP
#define SED_GENERATOR_HPP

#include <string>
#include <map>

namespace SED::AST{
    enum class Operator;
    enum class NodeClass;
    enum class ValueType;
}

namespace SED::Generator {
    class OperatorToMermaid {
        static std::map<AST::Operator, std::string> operatorNames;
    public:
        static std::string toMermaid(AST::Operator op);
    };
    class NodeClassToMermaid {
        static std::map<AST::NodeClass, std::string> NodeClassNames;
    public:
        static std::string toMermaid(AST::NodeClass NodeClass);
    };
    class ValueTypeToMermaid {
        static std::map<AST::ValueType, std::string> ValueTypeNames;
    public:
        static std::string toMermaid(AST::ValueType type);
    };

    class MermaidGenerator {
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
        static void putLabel(AST::NodeClass NodeClass);
        static void putLabel(AST::Operator op);
        static void putLabel(AST::ValueType type);
        static void putLabel(const std::string_view &label);
    };
}

#endif //SED_GENERATOR_HPP
