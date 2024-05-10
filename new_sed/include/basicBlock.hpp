#ifndef SED_BASIC_BLOCK_H
#define SED_BASIC_BLOCK_H
#include "ir.hpp"
#include <set>
#include <vector>
namespace SED::IR
{
class BasicBlock
{
    std::vector<Statement *> statements;
    std::set<size_t> next;

  public:
    BasicBlock *setStatement(const std::vector<Statement *> &_statements);
    BasicBlock *setNext(const std::set<size_t> &_next);
    std::vector<Statement *> getStatements() const;
    std::set<size_t> getNext() const;
};

class BasicBlockManager
{
    std::vector<BasicBlock *> basicBlocks;
    std::map<std::string, size_t> basicBlockMap; // 非匿名label到基本块的映射

  public:
    void load(const std::vector<Statement *> &statements);
    void output();
    void buildCFG();
    void toMermaid();
};
};     // namespace SED::IR
#endif // !SED_BASIC_BLOCK_H
