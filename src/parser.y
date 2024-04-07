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

%type < SED::AST::CompilationUnit* > CompUnit
%type < SED::AST::Function* > FuncDef
%type < SED::AST::Assignment* > Def
%type < SED::AST::Block* > Block
%type < SED::AST::Node* > Stmt
%type < SED::AST::Variable* > Ident
%type < std::vector< SED::AST::Node* > > CompUnitContainer BlockItemList
%type < std::vector< SED::AST::VariableDeclaration* > > DeclList
%type < std::vector< SED::AST::Assignment* > > DefList
%type < std::vector< SED::AST::RightValue* > > ValList
%type < SED::AST::RightValue* > UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp PrimaryExp Exp Cond Val
%type < SED::AST::Operator > UNARYOP
%type < SED::AST::ValueType > Type
%type < std::vector < SED::AST::Argument* > > FuncFParams
%type < SED::AST::FunctionCall* > Call
%token <std::string> IDENT
%token RETURN CONST
%token TYPE_INT TYPE_VOID TYPE_FLOAT TYPE_BOOL
%token<std::int32_t> INT_CONST
%token<float> FLOAT_CONST
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA LBRACKET RBRACKET
%token PLUS MINUS STAR SLASH PERCENT AND OR EQ NE LT GT LE GE NOT ASSIGN CONTINUE BREAK IF WHILE TRUE FALSE 
%left ELSE
%%
%start CompUnit;

CompUnit:
    CompUnitContainer { 
        if (driver.result == nullptr) {
            driver.result = new SED::AST::CompilationUnit();
        }
        driver.result->setChildren(std::move($1)); 
        $$ = driver.result; 
    }
    ;

CompUnitContainer: 
       {/* empty */ $$ = std::vector< SED::AST::Node* >();}
    | CompUnitContainer DeclList { $$ = $1; $$.insert($$.end(),$2.begin(),$2.end()); }
    | CompUnitContainer FuncDef { $$ = $1; $$.push_back($2); }
    ;

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
    Ident { $$ = (new SED::AST::Assignment())->setVariable($1); }
    | Ident ASSIGN Val { $$ = (new SED::AST::Assignment())->setVariable($1)->setValue($3); }
    ;

Val:
    Exp { $$ = $1; }
  ;

DefList:
    Def { $$ = std::vector< SED::AST::Assignment* >(); $$.push_back($1); }
    | DefList COMMA Def { $1.push_back($3); $$ = $1; }
    ;

FuncDef:
    Type IDENT LPAREN RPAREN Block {
        $$ = (new SED::AST::Function())->setReturnType($1)->setName($2)->setBlock($5);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | Type IDENT LPAREN FuncFParams RPAREN Block {
        $$ = (new SED::AST::Function())->setReturnType($1)->setName($2)->setBlock($6)->setParameters($4);
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @6.end.line;
        $$->end.column = @6.end.column;
    }

FuncFParams:
    Type Ident { $$ = std::vector< SED::AST::Argument* >(); $$.push_back((new SED::AST::Argument())->setType($1)->setVariable($2)); }
    | FuncFParams COMMA Type Ident { $1.push_back((new SED::AST::Argument())->setType($3)->setVariable($4)); $$ = $1; }
    ;

Block:
    LBRACE RBRACE { $$ = new SED::AST::Block(); }
    | LBRACE BlockItemList RBRACE { $$ = (new SED::AST::Block())->setChildren($2); }
    ;

BlockItemList:
     DeclList { 
        $$ = std::vector< SED::AST::Node* >();
        for (auto decl : $1) {
            $$.push_back(decl);
        }
    }
    | Stmt { $$ = std::vector< SED::AST::Node* >(); $$.push_back($1); }
    | BlockItemList DeclList { $$ = $1; $$.insert($$.end(),$2.begin(),$2.end()); }
    | BlockItemList Stmt { $$ = $1; $$.push_back($2); }
    ;

Stmt:
    Ident ASSIGN Exp SEMICOLON { $$ = (new SED::AST::Assignment())->setVariable($1)->setValue($3); }
    | RETURN LOrExp SEMICOLON { $$ = (new SED::AST::ReturnStatement())->setValue($2); }
    | RETURN SEMICOLON { $$ = (new SED::AST::ReturnStatement())->setValue(SED::AST::DirectRightValueInitializer::get(SED::AST::ValueType::VOID)); }
    | Block { $$ = $1; }
    | Exp SEMICOLON { $$ = $1; }
    | WHILE LPAREN Cond RPAREN Stmt { 
        $$ = (new SED::AST::WhileStatement())->setCondition($3)->setBlock(SED::AST::Block::blockify($5));
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | CONTINUE SEMICOLON { $$ = new SED::AST::ContinueStatement(); }
    | BREAK SEMICOLON { $$ = new SED::AST::BreakStatement(); }
    | IF LPAREN Cond RPAREN Stmt %prec ELSE { 
        $$ = (new SED::AST::IfStatement())->setCondition($3)->setThenBlock(SED::AST::Block::blockify($5)); 
        $$->begin.line = @1.begin.line;
        $$->begin.column = @1.begin.column;
        $$->end.line = @5.end.line;
        $$->end.column = @5.end.column;
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
         $$ = (new SED::AST::IfStatement())->setCondition($3)->setThenBlock(SED::AST::Block::blockify($5))->setElseBlock(SED::AST::Block::blockify($7));
            $$->begin.line = @1.begin.line;
            $$->begin.column = @1.begin.column;
            $$->end.line = @7.end.line;
            $$->end.column = @7.end.column;
     }
    ;

ValList:
    Exp { $$ = std::vector< SED::AST::RightValue* >(); $$.push_back($1); }
    | ValList COMMA Exp { $1.push_back($3); $$ = $1; }
    ;

Call:
    IDENT LPAREN RPAREN { 
        $$ = (new SED::AST::FunctionCall())->setName($1);
         }
    | IDENT LPAREN ValList RPAREN { $$ = (new SED::AST::FunctionCall())->setName($1)->setArgs($3); }
    ;

Ident
    : IDENT { $$ = (new SED::AST::Variable())->setName($1); }
    ;

Exp:
    AddExp { $$ = $1; }
    ;

Cond:
    LOrExp { $$ = $1; }
    ;

PrimaryExp:
    Ident { $$ = $1; }
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
    | Call { $$ = $1; }
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

%%

void yy::parser::error(const location_type& l, const std::string& m) {
     driver.error(l, m);
}

