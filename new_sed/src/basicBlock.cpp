#include "basicBlock.hpp"
namespace SED::IR
{
BasicBlock *BasicBlock::setStatement(const std::vector<SED::IR::Statement *> &_statements)
{
    statements = _statements;
    return this;
}

BasicBlock *BasicBlock::setNext(const std::set<size_t> &_next)
{
    next = _next;
    return this;
}

std::vector<SED::IR::Statement *> BasicBlock::getStatements() const
{
    return statements;
}
std::set<size_t> BasicBlock::getNext() const
{
    return next;
}

void BasicBlockManager::load(const std::vector<SED::IR::Statement *> &statements)
{
    std::vector<SED::IR::Statement *> currentBasicBlock;
    for (auto statement : statements)
    {
        auto label = dynamic_cast<SED::IR::Label *>(statement);
        if (label)
        {
            if (!currentBasicBlock.empty()) // 保存上一个基本块
            {
                basicBlocks.push_back((new BasicBlock())->setStatement(std::move(currentBasicBlock)));
                currentBasicBlock.clear();
            }
            basicBlockMap[label->getName()] = basicBlocks.size();
        }
        currentBasicBlock.push_back(statement);
    }
    if (!currentBasicBlock.empty())
    {
        basicBlocks.push_back((new BasicBlock())->setStatement(std::move(currentBasicBlock)));
    }
}

void BasicBlockManager::output()
{
    for (size_t i = 0; i < basicBlocks.size(); i++)
    {
        std::cout << "BasicBlock " << i << std::endl;
        for (auto statement : basicBlocks[i]->getStatements())
        {
            statement->output();
        }
    }
}

void BasicBlockManager::buildCFG()
{
    // 找到main函数
    size_t mainIndex = 0;
    for (size_t i = 0; i < basicBlocks.size(); i++)
    {
        auto statements = basicBlocks[i]->getStatements();
        for (auto statement : statements)
        {
            auto label = dynamic_cast<SED::IR::Label *>(statement);
            if (label && label->getName() == "main")
            {
                mainIndex = i;
                break;
            }
        }
    }
    if (mainIndex == 0)
    {
        throw new std::runtime_error("main function not found");
        return;
    }
    // 从第0个基本块开始，连一条边到main函数
    std::set<size_t> next;
    next.insert(mainIndex);
    basicBlocks[0]->setNext(next);
    for (size_t i = 1; i < basicBlocks.size(); i++)
    {
        auto statements = basicBlocks[i]->getStatements();
        for (auto statement : statements)
        {
            auto gotoStatement = dynamic_cast<SED::IR::Goto *>(statement);
            if (gotoStatement)
            {
                std::set<size_t> next = basicBlocks[i]->getNext();
                next.insert(basicBlockMap[gotoStatement->getLabel()]);
                basicBlocks[i]->setNext(next);
            }
            auto ifzStatement = dynamic_cast<SED::IR::Ifz *>(statement);
            if (ifzStatement)
            {
                std::set<size_t> next = basicBlocks[i]->getNext();
                next.insert(basicBlockMap[Generator::IRGenerator::labelWrapper(ifzStatement->getLabel())]);
                basicBlocks[i]->setNext(next);
            }
            auto assignCallStatement = dynamic_cast<SED::IR::AssignCall *>(statement);
            if (assignCallStatement)
            {
                std::set<size_t> next = basicBlocks[i]->getNext();
                next.insert(basicBlockMap[assignCallStatement->getFunction()]);
                basicBlocks[i]->setNext(next);
            }
        }
        if (i != basicBlocks.size() - 1)
        {
            std::set<size_t> next = basicBlocks[i]->getNext();
            next.insert(i + 1);
            basicBlocks[i]->setNext(next);
        }
    }
}

void BasicBlockManager::toMermaid()
{
    std::cout << "```mermaid" << std::endl;
    std::cout << "flowchart" << std::endl;
    for (size_t i = 0; i < basicBlocks.size(); i++)
    {
        std::cout << "subgraph BasicBlock" << i << std::endl;
        std::cout << "bb" << i << "[\"" << std::endl;
        for (auto statement : basicBlocks[i]->getStatements())
        {
            statement->output();
        }
        std::cout << "\"]" << std::endl;
        std::cout << "end" << std::endl;
    }
    for (size_t i = 0; i < basicBlocks.size(); i++)
    {
        for (auto next : basicBlocks[i]->getNext())
        {
            std::cout << "BasicBlock" << i << " --> BasicBlock" << next << std::endl;
        }
    }
    std::cout << "```" << std::endl;
}
}; // namespace SED::IR