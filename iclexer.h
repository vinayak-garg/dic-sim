#ifndef ICLEXER_H
#define ICLEXER_H

#include <fstream>
#include <string>

//extern std::ifstream *infile;
extern void initLexer(std::ifstream *_infile);
extern void  yyerror(char const *);
//extern int   yylex();
//extern char* yytext;
//extern int   yyleng;

//extern void* setUpBuffer(char const* text);
//extern void  tearDownBuffer(void* buffer);
extern int nextToken();
extern const char *getTokenString();
/*
typedef struct
{
    char* token;
    char* text;
    void* buffer;
} Lexer;

void initLexer(const char *t)
{
    strcpy(text, t);
    // Use the interface to set up the buffer
    buffer = setUpBuffer(text);
}
void clearLexer()
{
    // Tear down your interface
    tearDownBuffer(buffer);
}
*/
//char* theToken() const {return token;}


#endif // ICLEXER_H
