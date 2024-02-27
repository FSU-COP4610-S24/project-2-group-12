#include <unistd.h>

int main(){
    sleep(2);
    getppid();
    getpid();
    write(1,"hello", 6);
    close(0);
    return 0;
}
