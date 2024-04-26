
#ifndef SED_GENERATOR_HPP
#define SED_GENERATOR_HPP
#include "enumeration.hpp"
#include <map>
#include <string>
namespace SED::Enumeration
{
enum class Operator;
enum class NodeClass;
enum class ValueType;
} // namespace SED::Enumeration

namespace SED::Generator
{

extern std::map<Enumeration::Operator, std::string> mermaidOperatorMap;
extern std::string mermaidOperatorWrapper(Enumeration::Operator op);
extern std::map<Enumeration::NodeClass, std::string> mermaidNodeClassMap;
extern std::string mermaidNodeClassWrapper(Enumeration::NodeClass nodeClass);
extern std::map<Enumeration::ValueType, std::string> mermaidValueTypeMap;
extern std::string mermaidValueTypeWrapper(Enumeration::ValueType valueType);
class MermaidGenerator
{
  private:
    static size_t counter; // mermaid唯一标识符生成器

  public:
    static size_t nextCounter();  // 往后移动一位,不可逆
    static size_t getCounter();   // 获取当前的计数器
    static void refreshCounter(); // 重置计数器
    static void mermaidHeader();  // 生成mermaid的头部
    static void mermaidFooter();  // 生成mermaid的尾部
    virtual void toMermaid() = 0;
    static void putEdge();                           // 生成边,从当前计数器到下一个计数器
    static void putEdge(const std::string &message); // 生成边,从当前计数器到下一个计数器,并带有消息
    static void putEdge(size_t from, size_t to);     // 生成边,从from到to
    static void putEdge(size_t from, size_t to, const std::string &message); // 生成边,从from到to,并带有消息
    static void putLabel(const std::string &label);                          // 生成标签
    static void putLabel(Enumeration::NodeClass nodeClass);                  // 生成标签
    static void putLabel(Enumeration::Operator op);                          // 生成标签
    static void putLabel(Enumeration::ValueType valueType);                  // 生成标签
};

extern std::map<Enumeration::Operator, std::string> irOperatorMap;
extern std::string irOperatorWrapper(Enumeration::Operator op);
class IRGenerator
{
  private:
    static size_t registerCounter; // 寄存器计数器
    static size_t labelCounter;    // 标签计数器

  public:
    virtual void toIR() = 0;
    static size_t getRegister();                            // 获取当前寄存器
    static void nextRegister();                             // 往后移动一位,不可逆
    static size_t getLabel();                               // 获取当前标签
    static void nextLabel();                                // 往后移动一位,不可逆
    static std::string registerWrapper(size_t register_id); // 将寄存器id包装成字符串,供输出使用
    static std::string labelWrapper(size_t label_id);       // 将标签id包装成字符串,供输出使用
};
} // namespace SED::Generator

#endif // SED_GENERATOR_HPP
