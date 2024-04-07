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
            std::vector<std::map<std::string, AST::DirectRightValue *> > variables;
            std::map<std::string, AST::ValueType> functions;
            void add(AST::Variable *variable, AST::DirectRightValue *value) ;
            void add(AST::Function *function);
            AST::DirectRightValue *get(AST::Variable *variable);
            AST::ValueType get(AST::FunctionCall *functionCall);
            void set(AST::Variable *variable, AST::DirectRightValue *value);
            void enter() ;
            void leave() ;
            bool isGlobal() ;
        };
    }
}
inline SED::Context::AnalyzerContext analyzerContext;
#endif //SED_CONTEXT_HPP