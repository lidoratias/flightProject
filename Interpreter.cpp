//
// Created by daniel on 16/12/18.
//

#include "Interpreter.h"
#include "iostream"
#include <chrono>
#include <vector>
#include <queue>
#include <stack>
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "Maps.h"
#include "Number.h"
#include "Div.h"
#include "Mul.h"
#include "Plus.h"
#include "Minus.h"
#include "string.h"
#include "stdio.h"

using namespace std;
Interpreter::Interpreter() {
    mapCommand["openDataServer"] = new OpenServerCommand();
    mapCommand["connect"] = new ConnectCommand();
    mapCommand["Print"] = new PrintCommand();
    mapCommand["Var"] = new VarCommand();
    mapCommand["Set"] = new SetCommand();
    mapCommand["If"] = new IfCommand();
    expressionParser = new ExpressionParser();
}
/*vector<string> Interpreter::lexer(string line){
    string curStr = "";
    int i;
    int spaceCounter = 0;
    for(i = 0; i < line.length(); i++){
        if(line.at(i) == ' '){
            spaceCounter++;
        }
    }
    vector<string> strings;
    for(i = 0; i < line.length(); i++){
        if(line.at(i) == ' '){
            if(curStr != "") {
                strings.push_back(curStr);
                curStr = "";
            }
        } else{
            curStr += line.at(i);
        }
    }
    strings.push_back(curStr);
    return strings;
}*/

vector<string> Interpreter::lexer(string line){
    vector<string> strings;
    string curStr = "";
    string curExp = "";
    int i;
    int spaceCounter = 0;
    if(line.at(0) == '\t'){
        for (int j = 0; j < line.length() - 1; ++j) {
            line.at(j) = line.at(j+1);
        }
        line.at(line.length() - 1) = '\0';
    }
    for(i = 0; i < line.length(); i++){
        if(line.at(i) == ' '){
            spaceCounter++;
        }
    }
    for(i = 0; i < line.length(); i++){
        if(line.at(i) == ' '){
            if(curStr != ""){
                strings.push_back(curStr);
                curStr = "";
            }
        } else if(line.at(i) == '=' && line.find("bind") == string::npos){
            strings.push_back("="); //add
            i++;
            while(i < line.length()){
                curExp += line.at(i);
                i++;
            }
            string postFix = expressionParser->shunting_yard(curExp);
            strings.push_back(to_string(expressionParser->postToExp(postFix)->calculate()));
            /*char* convertTesterint;
            char* convertTesterdouble;
            string temp;
            for(i = 0; i < curExp.length(); i++){
                if(curExp.at(i) != ' '){
                     temp += curExp.at(i);
                }
            }
            strtol(temp.c_str(), &convertTesterint, 10);
            strtod(temp.c_str() , &convertTesterdouble);
            if (*convertTesterint) {
                if( *convertTesterdouble) {
                    string postFix = expressionParser->shunting_yard(curExp);
                    strings.push_back(to_string(expressionParser->postToExp(postFix)->calculate()));
                }else {
                    strings.push_back(curExp);
                }
            } else {
                strings.push_back(curExp);
            }
*/
            string s;
           /* if(postFix.at(0) == '(') {
                s = postFix.substr(1, postFix.length() - 2);
            } else {
                s = postFix;
            }
            try {
                stod(s.c_str());
                strings.push_back(s);
            } catch (exception e){*/
         /*  if (*convertTesterint && *convertTesterdouble) {
               strings.push_back(to_string(expressionParser->postToExp(postFix)->calculate()));
           }else {

               strings.push_back(postFix);
           }*/

        } else{
            curStr += line.at(i);
        }
    }
    if (curStr != "") {
        strings.push_back(curStr);
    }
    if (line.at(line.length() - 2) == '}'){
        strings.push_back("}");
    }

    return strings;
}

void Interpreter::parser(vector<string> strings) {
    string str = strings[0];
    vector<string> argu;
    if (str == "openDataServer") {
        argu.push_back(strings.at(1));
        argu.push_back(strings.at(2));
        this->mapCommand.at("openDataServer")->doCommand(argu);
    } else {
        if (str == "connect") {
            argu.push_back(strings.at(1));
            argu.push_back(strings.at(2));
            this->mapCommand.at("connect")->doCommand(argu);
        } else {
            if (str == "var") {
                    for (int i = 1; i < strings.size() ; ++i) {
                        argu.push_back(strings[i]);
                    }
                    mapCommand.at("Var")->doCommand(argu);

            } else {
                if (str == "print") {
                    for (int i = 1; i < strings.size(); ++i) {
                        argu.push_back(strings[i]);
                    }
                    mapCommand.at("Print")->doCommand(argu);
                }else {
                    if ( Maps::instance()->getSymbolTable().count(str) == 1) {
                        argu.push_back(strings[0]);
                        argu.push_back(strings[2]);
                        mapCommand.at("Set")->doCommand(argu);
                    } else {
                        if(str == "if") {
                            vector<string> lex;
                            vector<vector<string>> vector1;
                            mapCommand["If"]->doCommand(strings);
                            getline(cin, str);
                            while(str != "}") {
                                lex = lexer(str);
                                vector1.push_back(lex);
                                if(strcmp(lex.at(lex.size() - 1).c_str(),"}") == 0) {
                                    break;
                                }
                                getline(cin, str);
                            }
                            for (int i = 0; i < vector1.size(); ++i) {
                                mapCommand["If"]->doCommand(vector1.at(i));
                            }
                        } else {
                            if(str == "while") {
                                //vector<vector<string>> vector1;
                                vector<string> lex;
                                mapCommand["If"]->doCommand(strings);
                                getline(cin, str);
                                vector<string> p;
                                p.push_back(str);
                                while(str != "}") {
                                    lex = lexer(str);
                                    //vector1.push_back(lex);
                                    if(strcmp(lex.at(lex.size() - 1).c_str(),"}") == 0) {
                                        break;
                                    }
                                    getline(cin, str);
                                    p.push_back(str);
                                }
                                while(EnterIfWhile::instance()->getEnter()){
                                    for (int i = 0; i < p.size(); ++i) {
                                        if (strcmp(p.at(i).c_str(),"}") != 0) {
                                            mapCommand["If"]->doCommand(lexer(p.at(i)));
                                        }
                                    }
                                    mapCommand["If"]->doCommand(strings);
                                }
                            } else {
                                if (str == "sleep"){
                                    chrono::microseconds(stoi(strings[1]));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
