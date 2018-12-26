//
// Created by daniel on 16/12/18.
//

#include "OpenServerCommand.h"
#include "DataReaderServer.h"
#include "thread"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include "iostream"


void openServer(vector<string> input){
    DataReaderServer server = DataReaderServer(stoi(input.at(0)),stoi(input.at(1)));
    server.createServer();

}
OpenServerCommand ::OpenServerCommand() {

}
void OpenServerCommand::doCommand(vector<string> strings){
    if(strings.size() != 2){
        throw "wrong amount of inputs";
    }
    char* convertTester1;
    char* convertTester2;
    strtol(strings[0].c_str(), &convertTester1, 10);
    strtol(strings[0].c_str(), &convertTester2, 10);
    if (*convertTester1 || *convertTester2) {
        throw "one or more of the arguments isn't a number";
    }
    else {
        thread server(openServer, strings);
        server.detach();
    }
}