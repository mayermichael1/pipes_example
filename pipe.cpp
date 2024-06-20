#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

//TODO: try to read and write the pipes direclty
//TODO: refactor the code

static const int READ = 0;
static const int WRITE = 1;

int main(void) {
    int parentWritePipe[2] = {0};
    int childWritePipe[2] = {0}; 
    pid_t childPid = 0;

    pipe(parentWritePipe);
    pipe(childWritePipe);

    if (!(childPid = fork())) { // this is the cap
        close(childWritePipe[READ]);
        close(parentWritePipe[WRITE]);

        dup2(parentWritePipe[READ], STDIN_FILENO);
        dup2(childWritePipe[WRITE], STDOUT_FILENO);

        char *cap[2] = {(char*)"./cap", NULL};
        if(execv(cap[0], cap) == -1){
            return 0;             
        }
    } else { // this is the pipe
        close(parentWritePipe[READ]);
        close(childWritePipe[WRITE]);

        for (int i = 0; i < 10; i++) {
          char buffer = ('a' + i);
          write(parentWritePipe[WRITE], &buffer, 1);
          fprintf(stdout, "sent: %c\n", buffer);
          read(childWritePipe[READ], &buffer, 1);
          fprintf(stdout, "received: %c\n", buffer);
        }

        kill(childPid, 1);
        wait(NULL);
    }
    return 0;
}
