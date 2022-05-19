#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2);
}

int main(int argc, char *argv[]) {
    int i;
    struct sigaction act;       // 구조체로 사용하는 것 (더 많이 사용).
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask); // 초기화 
    act.sa_flags=0;
    sigaction(SIGALRM, &act, 0);    // act -> timeout에 대한 주소값

    alarm(2);

    for(i=0; i<3; i++) {
        puts("wait...");
        sleep(100);
    }
    return 0;
}


