%skeleton "lalr1.cc"

%code requires {
    #include "ast.hpp"
    #include "value.hpp"
    
    namespace SED{
        namespace Driver{
            class Driver;
        }
    }
    using Driver = SED::Driver::Driver;
}

%code {
    #include "driver.hpp"
    #include "context.hpp"
}


%language "c++"
%locations
%param { Driver &driver }

%define api.value.type variant
%define api.token.raw
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.assert

%define parse.error detailed
%define parse.lac full
%define parse.trace

%type < SED::AST::Assignment* > Def
%type < SED::AST::Node* > Stmt
%type<SED::AST::Variable*> Var
%type < std::vector< SED::AST::VariableDeclaration* > > DeclList
%type < std::vector< SED::AST::Assignment* > > DefList
%type < SED::AST::RightValue* > UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp PrimaryExp Exp Val AssignExp
%type < SED::AST::Operator > UNARYOP
%type < SED::AST::ValueType > Type
%token <std::string> IDENT
%token RETURN CONST
%token TYPE_INT TYPE_VOID TYPE_FLOAT TYPE_BOOL
%token<std::int32_t> INT_CONST
%token<float> FLOAT_CONST
%token LPAREN RPAREN SEMICOLON COMMA PRINT
%token PLUS MINUS STAR SLASH PERCENT AND OR EQ NE LT GT LE GE NOT TRUE FALSE BREAK LIST
%right ASSIGN
%%
%start Stmt;



DeclList :
    Type DefList SEMICOLON {
        $$ = std::vector< SED::AST::VariableDeclaration* >();
        for (auto def : $2) {
            auto decl = (new SED::AST::VariableDeclaration())->setType($1)->setVariable(def->getVariable());
            decl->getVariable()->setValueType($1);
            if (def->getValue() != nullptr) {
                decl->setValue(def->getValue());
            }else{
                decl->setValue(SED::AST::DirectRightValueInitializer::get($1));
            }
            $$.push_back(decl);
            decl->begin.line = @1.begin.line;
            decl->begin.column = @1.begin.column;
            decl->end.line = @3.end.line;
            decl->end.column = @3.end.column;
        }
    }
    | CONST DeclList {
        for (auto decl : $2) {
            decl->setIsConst(true);
        }
        $$ = $2;
    }
    ;

Type:
    TYPE_INT { $$ = SED::AST::ValueType::INT_32; }
    | TYPE_FLOAT { $$ = SED::AST::ValueType::FLOAT_32; }
    | TYPE_VOID { $$ = SED::AST::ValueType::VOID; }
    | TYPE_BOOL { $$ = SED::AST::ValueType::BOOLEAN; }
    ;

Def:
    Var { $$ = (new SED::AST::Assignment())->setVariable($1); }
    | Var ASSIGN Val { $$ = (new SED::AST::Assignment())->setVariable($1)->setValue($3); }
    ;

Val:
    AssignExp { $$ = $1; }
  ;

DefList:
    Def { $$ = std::vector< SED::AST::Assignment* >(); $$.push_back($1); }
    | DefList COMMA Def { $1.push_back($3); $$ = $1; }
    ;

Stmt:
     {  }
    | Stmt PRINT LPAREN AssignExp RPAREN SEMICOLON {$4->interpret();}
    | Stmt DeclList { 
        for (auto decl : $2) {
            decl->interpret();
        }

    }
    | Stmt BREAK SEMICOLON { 
        (new SED::AST::BreakStatement())->interpret();
    
    }
    | Stmt LIST SEMICOLON { 
        analyzerContext.list();
        
    }
    | Stmt AssignExp SEMICOLON { 
        try{
            $2->interpret();
        }catch(std::runtime_error& e){
            $2->dump(e.what(), SED::Error::ErrorType::WARNING);
            break;
        }
    }
    | Stmt SEMICOLON { 
        
    }
    ;

Var
    : IDENT { $$ = (new SED::AST::Variable())->setName($1); }
    ;

Exp:
    AssignExp { $$ = $1; }
    ;


PrimaryExp:
    Var { $$ = $1; }
    | LPAREN Exp RPAREN { $$ = $2; }
    | INT_CONST { $$ = (new SED::AST::Int32())->setValue($1); }
    | FLOAT_CONST { $$ = (new SED::AST::Float32())->setValue($1); }
    | TRUE { $$ = (new SED::AST::Boolean())->setValue(true); }
    | FALSE { $$ = (new SED::AST::Boolean())->setValue(false); }
    ;

UNARYOP:
    MINUS { $$ = SED::AST::Operator::NEG; }
    | NOT { $$ = SED::AST::Operator::NOT; }
    | PLUS { $$ = SED::AST::Operator::POS; }
    ;

UnaryExp:
    PrimaryExp { $$ = $1; }
    | UNARYOP UnaryExp {
        $$ = (new SED::AST::Unary())->setOp($1)->setExpr($2);
    } 
    ;

MulExp:
    UnaryExp { $$ = $1; }
    | MulExp STAR UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::MUL)->setLeft($1)->setRight($3);
    }
    | MulExp SLASH UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::DIV)->setLeft($1)->setRight($3);
    }
    | MulExp PERCENT UnaryExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::MOD)->setLeft($1)->setRight($3);
    }
    ;

AddExp:
    MulExp { $$ = $1; }
    | AddExp PLUS MulExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::ADD)->setLeft($1)->setRight($3);
    }
    | AddExp MINUS MulExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::SUB)->setLeft($1)->setRight($3);
    }
    ;

RelExp:
    AddExp { $$ = $1; } 
    | RelExp LT AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::LT)->setLeft($1)->setRight($3);
    }
    | RelExp GT AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::GT)->setLeft($1)->setRight($3);
    }
    | RelExp LE AddExp { 
        $$ = ( new SED::AST::Binary())->setOp(SED::AST::Operator::LE)->setLeft($1)->setRight($3);
    }
    | RelExp GE AddExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::GE)->setLeft($1)->setRight($3);
    }
    ;

EqExp:
    RelExp { $$ = $1; }
    | EqExp EQ RelExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::EQ)->setLeft($1)->setRight($3);
    }
    | EqExp NE RelExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::NE)->setLeft($1)->setRight($3);
    }
    ;

LAndExp:
    EqExp { $$ = $1; }
    | LAndExp AND EqExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::AND)->setLeft($1)->setRight($3);
    }

LOrExp:
    LAndExp { $$ = $1; }
    | LOrExp OR LAndExp { 
        $$ = (new SED::AST::Binary())->setOp(SED::AST::Operator::OR)->setLeft($1)->setRight($3);
    }

AssignExp:
    LOrExp { $$ = $1; }
    | Var ASSIGN AssignExp { 
        (new SED::AST::Assignment())->setVariable($1)->setValue($3)->interpret();
        $$ = $3;
    }
    ;

%%

void yy::parser::error(const location_type& l, const std::string& m) {
     driver.error(l, m);
}

