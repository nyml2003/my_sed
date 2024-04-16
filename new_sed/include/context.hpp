#ifndef SED_CONTEXT_HPP
#define SED_CONTEXT_HPP
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "value.hpp"

namespace SED {
    namespace AST {
        class DirectRightValue;
    }
    namespace Context {
        struct AnalyzerContext {
            AnalyzerContext();
            std::vector<std::map<std::string, AST::DirectRightValue *> > variables;
            std::vector<std::map<std::string, AST::ValueType>> functions;
            void add(AST::Variable *variable, AST::DirectRightValue *value) ;
            void add(std::string name, AST::ValueType type);
            AST::DirectRightValue *get(AST::Variable *variable);
            AST::ValueType get(std::string name);
            bool exists(AST::Variable *variable);
            bool exists(std::string name);
            void set(AST::Variable *variable, AST::DirectRightValue *value);
        };
    }
}
inline SED::Context::AnalyzerContext analyzerContext;
#endif //SED_CONTEXT_HPP