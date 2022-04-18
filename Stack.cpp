#include "Stack.hpp"

namespace ex4
{
    std::string Stack::pop()
    {
        std::string txt = this->head->txt;
        Node *temp = this->head;
        this->head = this->head->next;
        this->size--;
        delete temp;
        return txt;
    }
    std::string Stack::top()
    {
        return this->head->txt;
    }
    void Stack::push(std::string &txt)
    {
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
        return;
    }

}