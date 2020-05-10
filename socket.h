#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#define SERVER_PORT htons(10000)

void socket_comm()
{
    cout << "Server Socket initialized\n"<< endl;
    char buffer[1000];
    int n;

    int serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = SERVER_PORT;
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));

    listen(serverSock, 1);

    sockaddr_in clientAddr;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    int clientSock = accept(serverSock, (struct sockaddr *)&clientAddr, &sin_size);
    cout << "I accept you\n"<< endl;

    while (true)
    {
        bzero(buffer, 1000);

        //receive a message from a client
        //n = read(clientSock, buffer, 500);
        //cout << "Confirmation code  " << n << endl;
        //cout << "Server received:  " << buffer << endl;

        strcpy(buffer, "test");
        n = write(clientSock, buffer, strlen(buffer));
        cout << "Confirmation code  " << n << endl;
    }

    close(serverSock);
}

#endif