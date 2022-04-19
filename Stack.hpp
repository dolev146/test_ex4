#ifndef HEADER_H
#define HEADER_H

// #include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include "main.hpp"

namespace ex4
{

    class Node
    {
    public:
        std::string txt;
        Node *next;

        Node(std::string &txt)
        {

            this->txt = txt;
            this->next = NULL;
        };
    };

    class Stack
    {
    public:
        Node *head = NULL;
        int size = 0;
        std::string pop();
        std::string top();

        void push(std::string &txt)
        {
            pthread_mutex_init(&mutex, NULL);
            pthread_mutex_lock(&mutex);
            std::cout << "in push : ";
            std::cout << txt << std::endl;
            Node *n = new Node(txt);
            if (this->head == NULL)
            {
                this->head = n;
            }
            else
            {
                n->next = this->head;
                this->head = n;
            }
            this->size++;
            pthread_mutex_unlock(&mutex);
            pthread_mutex_destroy(&mutex);
            return;
        };
    };
}
#endif // HEADER_H