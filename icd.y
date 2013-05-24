%{
#include "iclexer.h"
#include "icparser.h"
#include "block.h"

//#include <QtDebug>
#include <QString>
#include <string>
#include <cstdio>
int yylex();
QString type;
BlockData blockdata;
%}

%error-verbose

%token TYPE VALUE FUNC INT

%%

start : prop prop prop prop spec
      ;

prop : type ':' value
     ;

type : TYPE {type = getTokenString();}
     ;

value : VALUE
{
    if (type.compare("%name", Qt::CaseInsensitive) == 0)
        icNameList->append(getTokenString());
    else if (type.compare("%pins", Qt::CaseInsensitive) == 0)
        icPinsList->append(getTokenString());
    else if (type.compare("%desc", Qt::CaseInsensitive) == 0)
        icDescList->append(getTokenString());
    else if (type.compare("%label", Qt::CaseInsensitive) == 0)
        icLabelList->append(getTokenString());
}
      ;

spec : '{' expr_list '}'
     ;

expr_list : expr_list expr | expr
          ;

expr : out func in {ICData.push_back(blockdata);blockdata.reset();}
     ;

out  : INT {blockdata.outPin.push_back(atoi(getTokenString()));}
     ;

func : '=' FUNC {blockdata.id = Block::mapBlockID(getTokenString());}
     ;

in   : '(' args ')'
     | '(' ')'
     ;

args : args ',' arg | arg
     ;

arg  : INT {blockdata.inPin.push_back(atoi(getTokenString()));}

%%

int yylex()
{
    return nextToken();
}
