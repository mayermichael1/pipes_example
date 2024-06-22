#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

union pipeStruct{
    struct{
        int out;
        int in;
    };

    struct{
        int write;
        int read;
    };
};

int main(void) {
    pipeStruct writeToParentPipe = {};
    pipeStruct writeToChildPipe = {};
    pid_t childPid = 0;

    pipe((int*)&writeToParentPipe);
    pipe((int*)&writeToChildPipe);

    if (!(childPid = fork())) { // this is the cap
        close(writeToChildPipe.in);
        close(writeToParentPipe.out);

        dup2(writeToChildPipe.out, STDIN_FILENO);
        dup2(writeToParentPipe.in, STDOUT_FILENO);

        char *cap[2] = {(char*)"./cap", NULL};
        if(execv(cap[0], cap) == -1){
            return 0;             
        }
    } else { // this is the pipe
        close(writeToParentPipe.in);
        close(writeToChildPipe.out);

        for (int i = 0; i < 10; i++) {
          char buffer = ('a' + i);
          write(writeToChildPipe.in , &buffer, 1);
          fprintf(stdout, "sent: %c\n", buffer);
          read(writeToParentPipe.out, &buffer, 1);
          fprintf(stdout, "received: %c\n", buffer);
        }

        kill(childPid, 1);
        wait(NULL);
    }
    return 0;
}
