//
// Created by venty on 2024/3/24.
//
#include "context.hpp"
#include "error.hpp"
#include <iostream>

namespace SED::Context
{

    AnalyzerContext::AnalyzerContext()
    {
        variables.push_back(std::map<std::string, AST::DirectRightValue *>());
        functions.push_back(std::map<std::string, AST::ValueType>());
    }

    void AnalyzerContext::add(AST::Variable *variable, AST::DirectRightValue *value)
    {
        std::string name = variable->getName();
        if (variables.back().find(name) != variables.back().end())
        {
            Error::VariableRedeclarationError(name).error();
        }
        variables.back()[name] = value;
    }

    AST::DirectRightValue *AnalyzerContext::get(AST::Variable *variable)
    {
        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return it->at(name);
            }
        }
        Error::UndefinedVariableError(name).error();
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
    void AnalyzerContext::set(AST::Variable *variable, AST::DirectRightValue *value)
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
        Error::UndefinedVariableError(name).error();
    }

    void AnalyzerContext::list()
    {
        if (variables[0].empty())
        {
            std::cout << "the variable list is empty" << std::endl;
        }
        else
        {
            std::cout << "---Variable List---" << std::endl
                      << std::endl;
            for (auto it = variables.rbegin(); it != variables.rend(); it++)
            {
                for (auto &i : *it)
                {
                    std::cout << "name: " << i.first << std::endl
                              << "value: ";
                    i.second->interpret();
                    std::cout << std::endl;
                }
            }
            std::cout << "-----------" << std::endl;
        }

        if (functions[0].empty())
        {
            std::cout << "the function list is empty" << std::endl;
        }
        else
        {
            std::cout << "---Function List---" << std::endl
                      << std::endl;

            for (auto it = functions.rbegin(); it != functions.rend(); it++)
            {
                for (auto &i : *it)
                {
                    std::cout << "name: " << i.first << std::endl
                              << "return type: " << Generator::ValueTypeToMermaid::toMermaid(i.second) << std::endl;
                }

            }
            std::cout << "-----------" << std::endl;
        }
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
        Error::UndefinedFunctionError(name).error();
        return AST::ValueType::VOID;
    }
}