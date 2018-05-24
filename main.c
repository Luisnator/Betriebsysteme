#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    while(1)
    {
        char test[100];
        scanf("%s", test);
        printf(test);
        int status;
        pid = fork();
        pid = waitpid(pid,status,0);
        execve('/bin/ls',test,NULL);
    }
    return 0;
}