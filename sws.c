#include "sws.h"
#include "parse_tools.c"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[]){
    if(argc < 1){
        printf("sws: not enough arguments.");
    }

    int port = SWS_PORT;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-length: 18\nServer: sws\r\n\n Hello from server\r\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){ printf("sws: socket failed."); exit(EXIT_FAILURE); } printf("sws: started socket\n");
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){ printf("sws: setsockopt error."); exit(EXIT_FAILURE); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){ printf("sws: bind failed."); exit(EXIT_FAILURE); } printf("sws: socket binded\n");
    if (listen(server_fd, 3) < 0){ printf("sws: listen failed."); exit(EXIT_FAILURE); } printf("sws: socket now listening\n");
/*    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
        printf("sws: accept error.");
        exit(EXIT_FAILURE);
    }*/
    printf("sws: waiting on new connections\n");
    while(new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)){
        valread = read( new_socket , buffer, SWS_DEFBUF);

        char sws_req_buf[SWS_DEFBUF];
        strcpy(sws_req_buf, buffer);

        char* cmd = strtok(sws_req_buf,"\n");
        int i = 0;
        while (cmd != NULL){
            if(i == 0){
                SWS_HEADER_S __sws_req_b = seperate_http_request(cmd);
                printf("%s\n", __sws_req_b.path);
                if(strcmp(__sws_req_b.path, "/") == 0){
                    __sws_req_b.path = "/index.html";
                }
            }
            cmd = strtok(NULL, "\n");
            i = i + 1;
        }
        send(new_socket , hello , strlen(hello) , 0 );

    }
    return 0;
}
