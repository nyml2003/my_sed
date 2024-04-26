#ifndef SED_ENUMERATION_HPP
#define SED_ENUMERATION_HPP

namespace SED::Enumeration
{
enum class NodeClass
{
    // Unknown, 如果是这个类型，说明有错误
    UNKNOWN,
    // Constant
    CONSTANT,
    // Mutable
    UNARY,
    BINARY,
    VARIABLE,
    FUNCTION_CALL,
    // Statement
    RETURN_STATEMENT,
    WHILE_STATEMENT,
    IF_STATEMENT,
    CONTINUE_STATEMENT,
    EXPRESSION_STATEMENT,
    BREAK_STATEMENT,
    ASSIGNMENT,
    // others
    VARIABLE_DECLARATION,
    FUNCTION_DECLARATION,
    FUNCTION_DEFINITION,
    COMPILATION_UNIT,
    BLOCK,
};
enum class Operator
{
    UNKNOWN,
    /*数的运算*/
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    /*逻辑运算*/
    AND,
    OR,
    /*比较运算*/
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    /*一元运算*/
    POS,
    NEG,
    NOT
};
enum class ValueType
{
    VOID,
    INT_32,
    FLOAT_32,
    BOOLEAN,
    POINTER,
    CHAR,
};
};     // namespace SED::Enumeration
#endif // SED_ENUMERATION_HPP