//
// Created by daniel on 20/12/18.
//

#include "SetCommand.h"
#include "GlobalNewSockfd.h"
#include "iostream"

#include "DataReaderServer.h"
#include "GlobalNewSockfd.h"

#include <string.h>
#include <unistd.h>

SetCommand::SetCommand() {

}
void SetCommand::doCommand(vector<string> strings) {
    Maps::instance()->updateSymbolTable(strings[0], stod(strings[1]));
    string path = Maps::instance()->getPathByVar(strings[0]);
    string setVar = "set " + path + " " + strings[1];
    char buf[400];
    strcpy(buf, setVar.c_str());
    int i = 0;
    while ( buf[i] != '\0'){
        i++;
    }
    buf[i] = '\r';
    i++;
    buf[i] = '\n';
    i++;
    buf[i] = '\0';
// Send message to the server
    if(path != "") {
        int n = write(GlobalNewSockfd::instance()->getSockClient(), buf, strlen(buf));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

    /*cout << GlobalNewSockfd::instance()->getSockServer()<<endl;
    cout << GlobalNewSockfd::instance()->getSockClient()<<endl;*/

    //int n = write(GlobalNewSockfd::instance()->getSockServer(),setVar.c_str(),setVar.length());
    /*string str = "set controls/flight/rudder 1";
    int n = write(GlobalNewSockfd::instance()->getSockServer(),str.c_str(),str.length());
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    char buffer[str.length()];
    bzero(buffer,str.length());
    n = read(GlobalNewSockfd::instance()->getSockClient(), buffer, str.length()-1);
    cout<<buffer<<endl;

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }*/
    /*string str = "set controls/flight/rudder 1";
    int n = write(GlobalNewSockfd::instance()->getSockClient(), str.c_str(), str.length());

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }*/

}
