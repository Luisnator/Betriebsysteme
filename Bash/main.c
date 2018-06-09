#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t pid;
    int *status;
    while(1)
    {
        if(WIFEXITED(status)) {


            char command[5000];
            char *splitted;

            //Hostname
            char host[5000];
            gethostname(host, sizeof(host));

            //Directory
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));


            //Host and Directory
            printf("%s(%s)>", host, cwd);
            //Read Command
            scanf(" %[^\n]s", command);
            getchar();
            splitted = strtok(command, " ");
            if (splitted[0] == *"cd") {
                splitted = strtok(NULL, " ");
                chdir(&splitted[0]);
            }
            if (splitted[0] == *"exit") {
                return 0;
            } else
            {
                char *prog = &splitted[0];
                char **test;
                int count = sizeof(splitted);
                test = malloc(sizeof(char*)*(count+1));
                int i = 0;
                while(i < count)
                {

                    test[i] = &splitted[0];
                    splitted = strtok(NULL," ");
                    i++;
                }
                test[i] = (char *)NULL;
                //Create Process
                pid = fork();
                waitpid(pid, status, WUNTRACED | WCONTINUED);
                if(pid == 0)
                {
                    execvp(prog,test);
                }

            }
        }
    }
    return 0;
}
