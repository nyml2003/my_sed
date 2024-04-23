//
// Created by venty on 2024/3/24.
//
#include "context.hpp"
#include "error.hpp"
#include "value.hpp"
#include <iostream>

namespace SED::Context
{

AnalyzerContext::AnalyzerContext()
{
    variables.push_back(std::map<std::string, AST::Constant *>());
    functions.push_back(std::map<std::string, AST::ValueType>());
}

void AnalyzerContext::add(AST::Variable *variable, AST::Constant *value)
{
    std::string name = variable->getName();
    if (variables.back().find(name) != variables.back().end())
    {
        Error::VariableRedeclarationError(name).error();
    }
    variables.back()[name] = value;
}

AST::Constant *AnalyzerContext::get(AST::Variable *variable)
{
    std::string name = variable->getName();
    for (auto it = variables.rbegin(); it != variables.rend(); it++)
    {
        if (it->find(name) != it->end())
        {
            return it->at(name);
        }
    }
    Error::UndeclaredVariableError(name).error();
    return nullptr;
}

bool AnalyzerContext::exists(AST::Variable *variable)
{

    std::string name = variable->getName();
    for (auto it = variables.rbegin(); it != variables.rend(); it++)
    {
        if (it->find(name) != it->end())
        {
            return true;
        }
    }
    return false;
}
void AnalyzerContext::set(AST::Variable *variable, AST::Constant *value)
{
    std::string name = variable->getName();
    for (auto it = variables.rbegin(); it != variables.rend(); it++)
    {
        if (it->find(name) != it->end())
        {
            it->at(name) = value;
            return;
        }
    }
    Error::UndeclaredVariableError(name).error();
}

void AnalyzerContext::add(std::string name, AST::ValueType type)
{
    if (functions.back().find(name) != functions.back().end())
    {
        Error::FunctionRedeclarationError(name).error();
    }
    functions.back()[name] = type;
}

bool AnalyzerContext::exists(std::string name)
{
    for (auto it = functions.rbegin(); it != functions.rend(); it++)
    {
        if (it->find(name) != it->end())
        {
            return true;
        }
    }
    return false;
}

AST::ValueType AnalyzerContext::get(std::string name)
{
    for (auto it = functions.rbegin(); it != functions.rend(); it++)
    {
        if (it->find(name) != it->end())
        {
            return it->at(name);
        }
    }
    Error::UndeclaredFunctionError(name).error();
    return AST::ValueType::VOID;
}

void AnalyzerContext::enter()
{
    variables.push_back(std::map<std::string, AST::Constant *>());
}

void AnalyzerContext::exit()
{
    variables.pop_back();
}

bool AnalyzerContext::isGloabl()
{
    return variables.size() == 1;
}
} // namespace SED::Context