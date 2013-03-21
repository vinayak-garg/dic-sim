#ifndef ICPARSER_H
#define ICPARSER_H

#include "blockdata.h"

#include <vector>

#include <QtGui>

extern int yyparse();

extern QStringList *icNameList;
extern QStringList *icPinsList;
extern QStringList *icDescList;
extern QStringList *icLabelList;
extern std::vector<BlockData> ICData;

class Parser
{
public:
    void parse()
    {
        yyparse();
    }
};

#endif // ICPARSER_H
