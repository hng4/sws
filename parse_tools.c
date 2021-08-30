#include "sws.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int line_http_request(char * line){
    char sws_buf[10];
    char sws_buf_e[5];
    sws_buf[10] = '\0';
    strncpy(sws_buf, line, 4);

    sws_buf[0] = toupper(sws_buf[0]);
    sws_buf[1] = toupper(sws_buf[1]);
    sws_buf[2] = toupper(sws_buf[2]);
    sws_buf[3] = toupper(sws_buf[3]);

    printf("%s\n", sws_buf);
    if(strcmp(sws_buf, "HTTP") ==0 || strcmp(sws_buf, "http") ==0){
        return 1;
    } else {
        return 0;
    }
}

struct SWS_HEADER seperate_http_request(char * request){
    SWS_HEADER_S __sws_h;
    char sws_req_buf[1000];
    char sws_rpr_buf[256];
    char sws_rpr_hve[10];

    strcpy(sws_req_buf, request);

    char* cmd = strtok(sws_req_buf," ");
    int i = 0;
    while (cmd != NULL){
        if(i == 0){
            strcpy(__sws_h.rtype, cmd);
        } else if(i == 1){
            strcpy(__sws_h.path, cmd);
        } else if(i == 2){
            strcpy(__sws_h.protocol, cmd);
            strcpy(sws_rpr_buf, cmd);
            char * splitc = strtok(sws_rpr_buf, "/");
            int f = 0;
            while(splitc != NULL){
                if(f == 0){
                    strcpy(__sws_h.hwve, splitc);
                }
                if(f == 1){
                    strcpy(__sws_h.hver, splitc);
                }
                splitc = strtok(NULL, "/");
                f = f + 1;
            }
        }
        cmd = strtok(NULL, " ");
        i = i + 1;
    }
    return __sws_h;
}

