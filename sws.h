#pragma once
#define SWS_PORT  8081
#define SWS_SNAME "sws/0.1"
#define SWS_DEFBUF 5000

typedef struct SWS_HEADER {
    /*
        Protocol, Like HTTP(S)
        Path, Like /index.html
        RType, Like GET or POST
    */
    char protocol[10];
    char path[256];
    char rtype[10];
    char hver[10];
    char hwve[10];
} SWS_HEADER_S;
