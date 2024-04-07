%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include "driver.hpp"
%}
%option noyywrap nounput noinput batch debug nodefault
%{
    yy::parser::symbol_type make_NUMBER_INT(const std::string&s,const yy::parser::location_type& loc, int base);
    yy::parser::symbol_type make_NUMBER_FLOAT(const std::string&s,const yy::parser::location_type& loc);
%}

%{
    # define YY_USER_ACTION loc.columns(yyleng);
%}
%%
%{
    yy::location& loc=driver.location;
    loc.step();
%}
"," {return yy::parser::make_COMMA(loc);}
";" {return yy::parser::make_SEMICOLON(loc);}
"(" {return yy::parser::make_LPAREN(loc);}
")" {return yy::parser::make_RPAREN(loc);}
"{" {return yy::parser::make_LBRACE(loc);}
"}" {return yy::parser::make_RBRACE(loc);}
"[" {return yy::parser::make_LBRACKET(loc);}
"]" {return yy::parser::make_RBRACKET(loc);}
"+" {return yy::parser::make_PLUS(loc);}
"-" {return yy::parser::make_MINUS(loc);}
"*" {return yy::parser::make_STAR(loc);}
"/" {return yy::parser::make_SLASH(loc);}
"%" {return yy::parser::make_PERCENT(loc);}
"==" {return yy::parser::make_EQ(loc);}
"!=" {return yy::parser::make_NE(loc);}
"<" {return yy::parser::make_LT(loc);}
"<=" {return yy::parser::make_LE(loc);}
">" {return yy::parser::make_GT(loc);}
">=" {return yy::parser::make_GE(loc);}
"=" {return yy::parser::make_ASSIGN(loc);}
"&&" {return yy::parser::make_AND(loc);}
"||" {return yy::parser::make_OR(loc);}
"!" {return yy::parser::make_NOT(loc);}

"0."[0-9]+ {return make_NUMBER_FLOAT(yytext, loc);}
[0-9][1-9]*"."[0-9]* {return make_NUMBER_FLOAT(yytext, loc);}


"0x"[0-9a-fA-F]+ {return make_NUMBER_INT(yytext, loc, 16);}
"0b"[01]+ {return make_NUMBER_INT(yytext, loc, 2);}
"0"[0-7]* {return make_NUMBER_INT(yytext, loc, 8);}
"0" {return make_NUMBER_INT(yytext, loc, 10);}
[1-9][0-9]* {return make_NUMBER_INT(yytext, loc, 10);}


"int" {return yy::parser::make_TYPE_INT(loc);}
"void" {return yy::parser::make_TYPE_VOID(loc);}
"float" {return yy::parser::make_TYPE_FLOAT(loc);}
"const" {return yy::parser::make_CONST(loc);}
"if" {return yy::parser::make_IF(loc);}
"else" {return yy::parser::make_ELSE(loc);}
"while" {return yy::parser::make_WHILE(loc);}
"break" {return yy::parser::make_BREAK(loc);}
"continue" {return yy::parser::make_CONTINUE(loc);}
"return" {return yy::parser::make_RETURN(loc);}
"bool" {return yy::parser::make_TYPE_BOOL(loc);}
"true" {return yy::parser::make_TRUE(loc);}
"false" {return yy::parser::make_FALSE(loc);}
[ \t\r]+ {loc.step();}

\n+ {loc.lines(yyleng); loc.step();}


[a-zA-Z_][a-zA-Z0-9_]* return yy::parser::make_IDENT(yytext, loc);



. throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));

<<EOF>> return yy::parser::make_YYEOF(loc);

%%

yy::parser::symbol_type make_NUMBER_INT(const std::string&s,const yy::parser::location_type&loc, int base) {
    errno=0;
    long value=strtol(s.c_str(), nullptr, base);
    if (! (INT_MIN<=value && value<=INT_MAX) || errno==ERANGE) {
        throw yy::parser::syntax_error(loc, "integer overflow: " + s);
    }
    std::int32_t i32=static_cast<std::int32_t>(value);
    return yy::parser::make_INT_CONST(i32, loc);
}

yy::parser::symbol_type make_NUMBER_FLOAT(const std::string&s,const yy::parser::location_type& loc) {
    errno=0;
    double value=strtod(s.c_str(), nullptr);
    if (errno==ERANGE) {
        throw yy::parser::syntax_error(loc, "float overflow: " + s);
    }
    return yy::parser::make_FLOAT_CONST(value, loc);
}

void Driver::scan_begin() {
    yy_flex_debug=this->traceScanning;
    yyin=freopen(this->sourceFileName.empty() || this->sourceFileName=="-" ? nullptr : this->sourceFileName.c_str(), "r", stdin);
}

void Driver::scan_end() {
    if (yyin) {
        fclose(yyin);
    }
}