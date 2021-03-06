%option noyywrap
%option yylineno
     
%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include "parser.tab.h"

const std::string error_alert = "\x1b[31merror\x1b[0m: ";

%}

IDENTIFIER              [_a-z]
DIGIT                   [0-9]
PUNCT                   [\(\)\:\;]

%x COMMENT

%%
"DECLARE"               { return DECLARE; }
"IN"                    { return IN; }
"END"                   { return END; }

"READ"                  { return READ; }
"WRITE"                 { return WRITE; }

"IF"                    { return IF; }
"THEN"                  { return THEN; }
"ELSE"                  { return ELSE; }
"ENDIF"                 { return ENDIF; }

"WHILE"                 { return WHILE; }
"DO"                    { return DO; }
"ENDWHILE"              { return ENDWHILE; }
"ENDDO"                 { return ENDDO; }

"FOR"                   { return FOR; }
"FROM"                  { return FROM; }
"TO"                    { return TO; }
"DOWNTO"                { return DOWNTO; }
"ENDFOR"                { return ENDFOR; }

":="                    { return ASSIGN; }

"="                     { return EQ; }
"!="                    { return NEQ; }
"<"                     { return LT; }
">"                     { return GT; }
"<="                    { return LEQ; }
">="                    { return GEQ; }

"+"                     { return ADD; }
"-"                     { return SUB; }
"/"                     { return DIV; }
"%"                     { return MOD; }
"*"                     { return MUL; }
{IDENTIFIER}+           { 
                            yylval.pidentifier = new std::string(yytext);
                            return pidentifier;
                        }
{DIGIT}+                { yylval.num = std::stoll(yytext); return num; }
{PUNCT}                 { return yytext[0]; }
\[.*\]                  { /*ignore comments TODO: make comments better again*/ }
"["                     { BEGIN(COMMENT); }
<COMMENT>{
    [^\]]               ;
    "]"                 BEGIN(INITIAL);
}

[ \t\r\n]+                { /*ignore whitespaces*/ }
.                       { return ERROR; }
%%

