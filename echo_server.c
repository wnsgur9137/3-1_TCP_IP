#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
        
        // 소켓 생성
        int serv_sock;
        int clnt_sock;
        char message[BUF_SIZE];
        int str_len, i;

        struct sockaddr_in serv_adr;
        struct sockaddr_in clnt_adr;
        socklen_t clnt_adr_sz;

//        char message[] = "Hello World!"; // 출력할 메세지

        if(argc != 2) { // 입력한 값이 2단어?가 아닐 경우
                printf("Usage : %s <port>\n", argv[0]);
                exit(1);
        }

        // serv_sock = (int domain, int type, int protocol)
        // domain : 소켓이 사용할 프로토콜 체계(Protocol Family) 정보 전달.
        // type : 소켓의 데이터 전송방식에 대한 정보 전달.
        // protocol : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달.
        //            -> 하나의 프로토콜 체계 안에 데이터의 전송방식이 동일한 프로토콜이 둘 이상 존재.(IPPRO_TCP, IPPRO_UDP)
        // PF_INET = IPv4,  SOCK_STREAM = 연결지향형 소켓, 0 = protocol)
        serv_sock = socket(PF_INET, SOCK_STREAM, 0);

        if(serv_sock == -1) // 실패 시 실행
                error_handling("socket() error"); // error_handling 함수 실행.

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family=AF_INET;
        serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
        serv_adr.sin_port = htons(atoi(argv[1]));

        if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
                error_handling("bind() error");
        
        if(listen(serv_sock, 5) == -1)
                error_handling("listen() error");

        clnt_adr_sz = sizeof(clnt_adr);

        for(i=0; i<5; i++){
            clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
            if(clnt_sock==-1)
                error_handling("accept() error");
            else
                printf("Connected client %d \n", i+1);
            while((str_len==read(clnt_sock, message, BUF_SIZE))!=0)
                    write(clnt_sock, message, str_len);
            close(clnt_sock);

        }


//        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
//
//        if(clnt_sock == -1)
//                error_handling("accept() error");
        
//        write(clnt_sock, message, sizeof(message));
//        close(clnt_sock);   // 무조건 닫아줘야함
        close(serv_sock);
        return 0;
}

void error_handling(char *message) {
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
