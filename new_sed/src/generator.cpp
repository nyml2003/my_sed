//
// Created by venty on 2024/3/24.
//
#include "generator.hpp"
#include "value.hpp"
#include <iostream>

namespace SED::Generator
{

size_t MermaidGenerator::counter = 0;

size_t MermaidGenerator::count()
{
    return ++counter;
}

size_t MermaidGenerator::getCounter()
{
    return counter;
}

void MermaidGenerator::refreshCounter()
{
    counter = 0;
}

void MermaidGenerator::mermaidHeader()
{
    std::cout << "```mermaid" << std::endl;
    std::cout << "graph TD" << std::endl;
}

void MermaidGenerator::mermaidFooter()
{
    std::cout << "```" << std::endl;
}

void MermaidGenerator::putEdge()
{
    std::cout << counter << " --> " << counter + 1 << std::endl;
}

void MermaidGenerator::putEdge(const std::string &message)
{
    std::cout << counter << " -- " << message << " --> " << counter + 1 << std::endl;
}

void MermaidGenerator::putEdge(size_t from, size_t to)
{
    std::cout << from << " --> " << to << std::endl;
}

void MermaidGenerator::putEdge(size_t from, size_t to, const std::string &message)
{
    std::cout << from << " -- " << message << " --> " << to << std::endl;
}

void MermaidGenerator::putLabel(const std::string &label)
{
    std::cout << counter << "[" << label << "]" << std::endl;
}

size_t IRGenerator::registerCounter = 0;

size_t IRGenerator::labelCounter = 0;

size_t IRGenerator::getRegister()
{
    return registerCounter;
}

void IRGenerator::nextRegister()
{
    registerCounter++;
}

std::string IRGenerator::registerWrapper(size_t register_id)
{
    return "%" + std::to_string(register_id);
}

size_t IRGenerator::getLabel()
{
    return labelCounter;
}

void IRGenerator::nextLabel()
{
    labelCounter++;
}

std::string IRGenerator::labelWrapper(size_t label_id)
{
    return "L" + std::to_string(label_id);
}
} // namespace SED::Generator