#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include "Stack.hpp"

using namespace ex4;

int child_pid = 0;

void kill_child(int sig)
{
    std::cout << "child_ pid kii " << std::endl;
    kill(child_pid, SIGKILL);
}

int main()
{
    // Stack *mystack = new Stack();
    // std::string a = "yakov is great";
    // std::string b = "dolev is great";
    // mystack->push(a);
    // mystack->push(b);
    // std::string out = mystack->top();
    // std::cout << out << std::endl;
    // out = mystack->pop();
    // std::cout << out << std::endl;
    // out = mystack->pop();
    // std::cout << out << std::endl;

    child_pid = fork();
    if (child_pid == -1)
    {
        return 1;
    }
    std::string param = "./server";
    if (child_pid == 0)
    {
        // child process
        char *args[] = {(char *)(param.c_str()), NULL};
        execv(args[0], args);
    }
    else
    {
        // parent process
        wait(NULL);
    }

    return 0;
}