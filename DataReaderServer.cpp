//
// Created by daniel on 17/12/18.
//

#include "DataReaderServer.h"
#include "GlobalNewSockfd.h"

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include "iostream"
using namespace std;

DataReaderServer::DataReaderServer(int server_port, int server_rate) {
    port = server_port;
    rate = server_rate;
}

void DataReaderServer::createServer(){
    int sockfd;
    int  clilen;
    char buffer[400];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    GlobalNewSockfd::instance()->setSockServer(accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen));
    //newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (GlobalNewSockfd::instance()->getSockServer()  < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    bzero(buffer,400);
    int i = 0;
    double val = 0;
    int k = 0;
    int h = 0;
    char buffer2[400];
    n = read(GlobalNewSockfd::instance()->getSockServer(), buffer, 399);
    while (true) {
        k= 0;
        while(buffer[k] != '\n'){
            buffer2[k] = buffer[k];
            k++;
        }
        buffer2[k] = '\0';
        //cout<<buffer2<<endl;

        k++;
        h = 0;
        while(buffer[k] != '\0' && buffer[k] != '\n'){
            buffer[h] = buffer[k];
            h++;
            k++;
        }
        buffer[h] ='\0';

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        i = 0;
        string value = "";
        for (int j = 0; j < 23; ++j) {
            value = "";
            while (buffer2[i] != ',' && buffer2[i] != '\0') {
                value = value + buffer2[i];
                i++;
            }
            try {
                val = stod(value);
            } catch (exception e) {

            }
            Maps::instance()->updatePathValue(Maps::instance()->getPathByIndex(j), val);
            try {
                Maps::instance()->updateSymbolTable(
                        Maps::instance()->getVarByPath(Maps::instance()->getPathByIndex(j)), val);
            } catch (exception e) {

            }
            i++;
        }
        n = read(GlobalNewSockfd::instance()->getSockServer(), buffer + h, 399 - h);
    }
}
