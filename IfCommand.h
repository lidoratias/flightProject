//
// Created by daniel on 20/12/18.
//

#ifndef PROJECT_IFCOMMAND_H
#define PROJECT_IFCOMMAND_H

#include "Command.h"
#include "Maps.h"
#include "EnterIfWhile.h"
class IfCommand : public  Command{
public:
    IfCommand();
    virtual void doCommand(vector<string>);
};


#endif //PROJECT_IFCOMMAND_H
