%{
#include <stdio.h>
%}

%%
"def"|"return"|"if"|"else"|"elif"|"while"|"for"|"in"|"import"   { printf("KEYWORD(%s)\n", yytext); }
[0-9]+\.[0-9]+                                                                     { printf("FLOAT_CONST(%s)\n", yytext); }
[0-9]+                                                                             { printf("INT_CONST(%s)\n", yytext); }
\'([^\\\n]|(\\.))\'                                                                { printf("CHAR_CONST(%s)\n", yytext); }
\"([^\\\n]|(\\.))*\"                                                               { printf("STRING_CONST(%s)\n", yytext); }
"true"|"false"                                                                     { printf("BOOL_CONST(%s)\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                                                             { printf("IDENTIFIER(%s)\n", yytext); }
"=="|"!="|"<="|">="|"<"|">"                                                         { printf("OPERATOR(%s)\n", yytext); }
"&&"|"||"|"!"                                                                       { printf("OPERATOR(%s)\n", yytext); }
"&"|"|"|"^"|"<<"|">>"                                                               { printf("OPERATOR(%s)\n", yytext); }
"="|"+="|"-="|"*="|"/="|"%="                                                        { printf("OPERATOR(%s)\n", yytext); }
"++"|"--"                                                                           { printf("OPERATOR(%s)\n", yytext); }
"?"|":"                                                                             { printf("OPERATOR(%s)\n", yytext); }
"+"|"-"|"*"|"/"|"%"                                                                 { printf("OPERATOR(%s)\n", yytext); }
";"                                                                                 { printf("DELIMITERS(%s)\n", yytext); }
"("                                                                                 { printf("DELIMITERS(%s)\n", yytext); }
")"                                                                                 { printf("DELIMITERS(%s)\n", yytext); }
"{"|","|";"|":"                                                                     { printf("DELIMITERS(%s)\n", yytext); }
"}"|"["|"]"                                                                         { printf("DELIMITERS(%s)\n", yytext); }
"."|"::"|"->"|"..."                                                                 { printf("PUNCTUATORS(%s)\n", yytext); }
[ \t\n]+                                                                            { /* skip whitespace */ }
.                                                                                   { printf("UNKNOWN(%s)\n", yytext); }
%%

int main(void) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
