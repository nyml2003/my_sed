#ifndef SED_DRIVER_HPP
#define SED_DRIVER_HPP
#include "ast.hpp"
#include "location.hh"
#include "parser.hpp"



namespace SED::Driver {
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
    class Driver {
    public:
        Driver(Config config);
        ~Driver()=default;
        void setTraceParsing(bool traceParsing);
        void setTraceScanning(bool traceScanning);
        void parse();
        static void error(const yy::location &l, const std::string &m);
        yy::location location;
        bool traceScanning;
        bool traceParsing;
        std::vector<std::string> historyCode;
    };
} // Driver
inline SED::Driver::Driver driver({false, false, SED::Driver::Config::Mode::COMPILE});

#define YY_DECL \
    yy::parser::symbol_type yylex(SED::Driver::Driver& driver)

YY_DECL;
#endif //SED_DRIVER_HPP
