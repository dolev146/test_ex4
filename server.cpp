// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
// https://www.geeksforgeeks.org/udp-server-client-implementation-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#include "Stack.hpp"
using namespace ex4;

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd, Stack *mystack)
{

    char buff[MAX];

    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer

        read(connfd, buff, sizeof(buff));
        // maybe replace with recv
        if (!recv(connfd, buff, sizeof(buff), 0))
        {
            printf("Client diconnected\n");
        }

        // print buffer which contains the client contents
        printf("From client: %s \n", buff);
        std::string to_push = std::string(buff);
        mystack->push(to_push);
    }
}

// driver function
int main()
{
    Stack *my_stack = new Stack();

    int sockfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "socket creation failed..." << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "Socket successfully created.." << std::endl;
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        std::cout << "socket bind failed..." << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "Socket successfully binded.." << std::endl;
    }

    // Now server is ready to listen and verification
    if (listen(sockfd, 5) != 0)
    {
        std::cout << "Listen failed..." << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "server listening..." << std::endl;
    }

    unsigned int len = sizeof(cli);

    // Accept the data packet from client and verification
    int connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        std::cout << "server accept faild failed..." << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "Server accept the client " << std::endl;
    }
    // Function for chatting between client and server
    func(connfd, my_stack);
    // After chatting close the socket
    close(sockfd);

    return 0;
}