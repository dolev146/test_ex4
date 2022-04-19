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
#include "Stack.hpp"
using namespace ex4;

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd, Stack *mystack)
{

    char buff[MAX];
    // int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s \n", buff);
        std::string to_push = std::string(buff);
        mystack->push(to_push);

        // bzero(buff, MAX);
        // n = 0;
        // copy server message in the buffer
        // while ((buff[n++] = getchar()) != '\n')
        //     ;

        // and send that buffer to client
        // write(connfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        // if (strncmp("exit", buff, 4) == 0 || strncmp("EXIT", buff, 4) == 0 || (strncmp(buff, "LOCAL", 4)) == 0)
        // {
            // printf("Server Exit...\n");
            // break;
        // }
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

    // int isConnect = 1;
    // while (true)
    // {
    //     if (isConnect)
    //     {
    //         addr_size = sizeof(client_addr);
    //         client_sock = accept(sockfd, (SA *)&cli, &addr_size);
    //         printf("[+]Client connected.\n");
    //         isConnect = 0;
    //     }

    //     bzero(buffer, 1024);
    //     if (!recv(client_sock, buffer, sizeof(buffer), 0))
    //     {
    //         close(client_sock);
    //         isConnect = 1;
    //     }
    //     else
    //     {
    //         for (int i = 0; i < 1024; i++)
    //         {
    //             printf("%c", buffer[i]);
    //         }
    //         printf("\n");
    //     }
    // }

    return 0;
}