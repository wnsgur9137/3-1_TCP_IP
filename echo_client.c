#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
        
        int sock;
        char message[BUF_SIZE];
        int str_len, recv_len, recv_cnt;
        struct sockaddr_in serv_adr;

//        struct sockaddr_in serv_addr;
//        char message[30];
//        int str_len;
//        int idx=0, read_len=0;

        if(argc != 3) { // 입력이 잘못 되었을 경우
                printf("Usage : %s <port>\n", argv[0]);
                exit(1);
        }

        // IPv4, TCP, protocl = 0
        sock = socket(PF_INET, SOCK_STREAM, 0);
        if(sock == -1)
                error_handling("socket() error");

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family=AF_INET;
        serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_adr.sin_port = htons(atoi(argv[2]));

        if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
                error_handling("socket() error");
        else
                puts("Connected..................");
        
        while(1) {
                fputs("Input message(0 to quit): ", stdout);
                fgets(message, BUF_SIZE, stdin);

                if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
                        break;
                str_len=write(sock, message, strlen(message));

                recv_len=0;
                while(recv_len<str_len) {
                        recv_cnt=read(sock, &message[recv_len], BUF_SIZE-1);
                        if(recv_cnt==-1)
                                error_handling("read() error!");
                        recv_len+=recv_cnt;
                }

                message[recv_len]=0;
                printf("Message from server : %s", message);
        }

//        str_len=read(sock,message,sizeof(message)-1);
//        if(str_len == -1)
//                error_handling("read() error");
//        printf("Message from server : %s \n", message);
//        
//        while(read_len==read(sock, &message[idx++], 1)){
//                if(read_len == -1)
//                        error_handling("read() error!");
//                str_len += read_len;
//        }
//
//        printf("Message from server: %s \n", message);
//        printf("Function read call cont: %d \n", str_len);
        close(sock);
        return 0;
}

void error_handling(char *message) {
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
