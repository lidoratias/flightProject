//
// Created by daniel on 20/12/18.
//

#include "IfCommand.h"
#include "iostream"
#include "Interpreter.h"
#include "string.h"
#include "stdio.h"

IfCommand::IfCommand() {

}
bool twoVar(string oper, string str1, string str2){
    int number;
    if(oper == "==") {
        return Maps::instance()->getValueByVar(str1) == Maps::instance()->getValueByVar(str1);
    } else if (oper == "!=") {
        return Maps::instance()->getValueByVar(str1) != Maps::instance()->getValueByVar(str1);
    } else if (oper == ">") {
        return Maps::instance()->getValueByVar(str1) > Maps::instance()->getValueByVar(str1);

    } else if (oper == "<") {
        return Maps::instance()->getValueByVar(str1) < Maps::instance()->getValueByVar(str1);

    } else if(oper == ">=") {
        return Maps::instance()->getValueByVar(str1) >= Maps::instance()->getValueByVar(str1);

    } else if(oper == "<=") {
        return Maps::instance()->getValueByVar(str1) <= Maps::instance()->getValueByVar(str1);
    }
}
bool firstVar(string oper, string str1, string str2){
    double number = stod(str2);
    if(oper == "==") {
        return Maps::instance()->getValueByVar(str1) == number;
    } else if (oper == "!=") {
        return Maps::instance()->getValueByVar(str1) != number;
    } else if (oper == ">") {
        return Maps::instance()->getValueByVar(str1) > number;

    } else if (oper == "<") {
        return Maps::instance()->getValueByVar(str1) < number;

    } else if(oper == ">=") {
        return Maps::instance()->getValueByVar(str1) >= number;

    } else if(oper == "<=") {
        return Maps::instance()->getValueByVar(str1) <= number;
    }
}
bool secondtVar(string oper, string str1, string str2){
    double number = stod(str1);
    if(oper == "==") {
        return number == Maps::instance()->getValueByVar(str1);
    } else if (oper == "!=") {
        return number !=Maps::instance()->getValueByVar(str1);
    } else if (oper == ">") {
        return number > Maps::instance()->getValueByVar(str1);

    } else if (oper == "<") {
        return number < Maps::instance()->getValueByVar(str1);

    } else if(oper == ">=") {
        return number >=  Maps::instance()->getValueByVar(str1);

    } else if(oper == "<=") {
        return number <= Maps::instance()->getValueByVar(str1);
    }
}


void IfCommand::doCommand(vector<string> line) {
    if (line.at(0) == "if" || line.at(0) == "while") {
        char *convertTester1;
        char *convertTester2;
        strtol(line[1].c_str(), &convertTester1, 10);
        strtol(line[3].c_str(), &convertTester2, 10);
        if (*convertTester1 || !*convertTester2) {
            EnterIfWhile::instance()->setEnter(firstVar(line[2], line[1], line[3]));
        } else if (!*convertTester1 || *convertTester2) {
            EnterIfWhile::instance()->setEnter(secondtVar(line[2], line[3], line[1]));
        } else if (*convertTester1 && *convertTester2) {
            EnterIfWhile::instance()->setEnter(twoVar(line[2], line[1], line[3]));
        }
    }  else {
        if (EnterIfWhile::instance()->getEnter()) {
            if (strcmp(line.at(line.size() - 1).c_str(),"}") == 0) {
                line.pop_back();
            }
            Interpreter interpreter = Interpreter();
            interpreter.parser(line);
        }
    }
}