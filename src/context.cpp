//
// Created by venty on 2024/3/24.
//
#include "context.hpp"

namespace SED::Context {
    void AnalyzerContext::add(AST::Variable *variable, AST::DirectRightValue *value) {
        std::string name = variable->getName();
        if (variables.back().find(name) != variables.back().end()) {
            throw std::runtime_error("Variable already exists");
        }
        variables.back()[name] = value;
    }

    void AnalyzerContext::add(AST::Function *function) {
        std::string name = function->getName();
        if (functions.find(name) != functions.end()) {
            throw std::runtime_error("Function already exists");
        }
        functions[name] = function->getReturnType();
    }

    AST::DirectRightValue * AnalyzerContext::get(AST::Variable *variable){
        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++) {
            if (it->find(name) != it->end()) {
                return it->at(name);
            }
        }
        throw std::runtime_error("Variable not found");
    }

    AST::ValueType AnalyzerContext::get(AST::FunctionCall *functionCall) {
        std::string name = functionCall->getName();
        if (functions.find(name) != functions.end()) {
            return functions[name];
        }
        throw std::runtime_error("Function not found");
    }

    void AnalyzerContext::set(AST::Variable *variable, AST::DirectRightValue *value)
    {
        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++) {
            if (it->find(name) != it->end()) {
                it->at(name) = value;
                return;
            }
        }
        throw std::runtime_error("Variable not found");
    }

    /**
    * @brief 进入一个新的作用域
    */
    void AnalyzerContext::enter() {
        variables.push_back(std::map<std::string, AST::DirectRightValue *>());
    }

    /**
    * @brief 离开一个作用域
    */
    void AnalyzerContext::leave() {
        variables.pop_back();
    }

    /**
    * @brief 判断当前是否在全局作用域,如果在全局作用域则返回true，否则返回false
    * @details 如果只有一个作用域则返回true，否则返回false
    */
    bool AnalyzerContext::isGlobal() {
        return variables.size() == 1;
    }
}