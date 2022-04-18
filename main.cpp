#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include "Stack.hpp"

using namespace ex4;

int main()
{
    Stack *mystack = new Stack();
    std::string a = "yakov is gay";
    std::string b = "dolev is gay";
    mystack->push(a);
    mystack->push(b);
    std::string out = mystack->top();
    std::cout << out << std::endl;
    out = mystack->pop();
    std::cout << out << std::endl;
    out = mystack->pop();
    std::cout << out << std::endl;

    return 0;
}