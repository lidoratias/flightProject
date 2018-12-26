//
// Created by daniel on 20/12/18.
//

#include "VarCommand.h"
#include "iostream"
VarCommand::VarCommand() {

}
void VarCommand::doCommand(vector<string> strings) {
    if (strings[2] == "bind") {
        Maps::instance()->updtaeVarPath(strings[0], strings[3].substr(1, strings[3].find_last_of('"') - 1));
        Maps::instance()->updtaePathVar(strings[3].substr(1, strings[3].find_last_of('"') - 1), strings[0]);
        Maps::instance()->updateSymbolTable(strings[0], 0);
    } else {
        if(Maps::instance()->getSymbolTable().count(strings[2]) == 1) {
            Maps::instance()->updateSymbolTable(strings[0], Maps::instance()->getValueByVar(strings[2]));
        } else {
            Maps::instance()->updateSymbolTable(strings[0], stod(strings[2]));
        }
    }
}
