#include <iostream>
#include <thread>
#include "map"
#include "DataReaderServer.h"
#include "Client.h"
#include "Interpreter.h"
using namespace std;

int main()
{

    //DataReaderServer dataReaderServer = DataReaderServer(5400, 10);
    //dataReaderServer.createServer();
    //Client client = Client("127.0.0.1", 5402);
    //client.openClient();*/
    /*vector<string> vector1;
    vector1.push_back("a");
    vector1.push_back("b");
    vector<string>* strs = &vector1;
    cout<<strs->at(0);
    cout<<strs->at(1);*/
    ExpressionParser expP = ExpressionParser();
    string str = expP.shunting_yard("(2*-2)/4");
    double val = expP.postToExp(str)->calculate();
    cout << val << endl;

    /*Interpreter interpreter = Interpreter();
    string str;
    try {
        getline(cin, str);
        while (str != "print \"done\"") {
            vector<string> strings = interpreter.lexer(str);
            interpreter.parser(strings);
            getline(cin, str);
        }
    }
    catch (exception exception1) {
        cout<<exception1.what();
    }*/
}
