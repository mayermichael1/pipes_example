#include <ctype.h>
#include <unistd.h>

int main(void){
    
    char buffer = 0;
    while(true){
        read(STDIN_FILENO, &buffer, 1);
        buffer = toupper(buffer);
        write(STDOUT_FILENO, &buffer, 1);
    }

    return 0;
}
