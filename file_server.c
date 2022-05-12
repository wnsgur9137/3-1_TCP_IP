#include <stdio.h>
#include <stdlib.h>
#include <strng.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
        int serv_sd, clnt_sd;
        FILE * fp;
        char buf[BUF_SIZE];
        int read_cnt;

        struct sockaddr_in serv_adr, clnt_adr;
        socklen_t clnt_adr_sz;

        if(argc!=2) {
                printf("Usage: %s <port>\n", argv[0]);
                exit(1);
        }

        fp=fopen("file_server.c", "rb");
        serv_sd=socket(PF_INET, SOCK_STREAM, 0);
        
        
}
