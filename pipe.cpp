#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

int main(void) {
    int parent_write[2];
    int child_write[2]; 
    int ws = 0;
    char *cap[2] = {(char*)"./cap", NULL};
    char buffer = 0;
    pid_t cpid = 0;

    const int READ = 0;
    const int WRITE = 1;

    pipe(parent_write);
    pipe(child_write);

    if (!(cpid = fork())) { // this is the cap
        close(child_write[READ]);
        close(parent_write[WRITE]);

        dup2(parent_write[READ], 0);
        dup2(child_write[WRITE], 1);

        if(execv(cap[0], cap) == -1){
            return 0;             
        }
    } else { // this is the pipe
        close(parent_write[READ]);
        close(child_write[WRITE]);

        dup2(parent_write[WRITE], 1);
        dup2(child_write[READ], 0);

        for (int i = 0; i < 10; i++) {
          buffer = ('a' + i);
          write(1, &buffer, 1);
          fprintf(stderr, "sent: %c\n", buffer);
          read(0, &buffer, 1);
          fprintf(stderr, "received: %c\n", buffer);
        }

        kill(cpid, 1);
        wait(&ws);
    }
    return 0;
}
