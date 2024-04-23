
#ifndef SED_DRIVER_HPP
#define SED_DRIVER_HPP
#include "ast.hpp"
#include "location.hh"
#include "parser.hpp"
namespace SED::Driver
{
struct Config
{
    bool traceParsing;
    bool traceScanning;
    enum class Mode
    {
        COMPILE,
        EXPLANATION
    } mode;
};
class Driver
{
  public:
    Driver(Config config);
    ~Driver() = default;
    void setTraceParsing(bool traceParsing);
    void setTraceScanning(bool traceScanning);
    void setSourceFileName(const std::string &sourceFileName);
    void setOutputFileName(const std::string &outputFileName);
    void setErrorFileName(const std::string &errorFileName);
    void parse();
    static void error(const yy::location &l, const std::string &m);
    void scan_begin(); // 初始化词法分析器, 实现在scanner.l中，主要将sourceFileName和yyin绑定
    void scan_end();   // 释放源代码所在的文件流, 实现在scanner.l中
    yy::location location;
    AST::CompilationUnit *result{nullptr};
    bool traceScanning;
    bool traceParsing;
    std::string sourceFileName; // 源代码文件名
    std::string outputFileName; // 输出文件名, 会对标准输出流进行重定向
    std::string errorFileName;  // 报错信息的输出，会对标准错误流进行重定向
};
} // namespace SED::Driver
inline SED::Driver::Driver driver({false, false, SED::Driver::Config::Mode::COMPILE});

#define YY_DECL yy::parser::symbol_type yylex(SED::Driver::Driver &driver)

YY_DECL;
#endif // SED_DRIVER_HPP
