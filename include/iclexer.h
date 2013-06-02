#ifndef ICLEXER_H
#define ICLEXER_H

#include <fstream>
#include <string>

extern void initLexer(std::ifstream *_infile);
extern void  yyerror(char const *);

extern int nextToken();
extern const char *getTokenString();

#endif // ICLEXER_H
