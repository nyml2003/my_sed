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
            void add(AST::Variable *variable, AST::DirectRightValue *value) ;
            AST::DirectRightValue *get(AST::Variable *variable);
            bool exists(AST::Variable *variable);
            void set(AST::Variable *variable, AST::DirectRightValue *value);
            void list();
        };
    }
}
inline SED::Context::AnalyzerContext analyzerContext;
#endif //SED_CONTEXT_HPP