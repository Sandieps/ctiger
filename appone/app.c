//
//  app.c
//  appone
//
//  Created by sandie on 29/09/20.
//

#include "app.h"
#include <err.h>
#include <pthread/pthread.h>
#include <unistd.h>
#include "string.h"
#include "netinet/in.h"
#include "netdb.h"
#include <stdlib.h>
#include <arpa/inet.h>

#define MAXLINE 256 * 4096
#define MAXSUB  50000

void httprequest(const char * host,const char* httpmethod,const char* requesturi,const char* requestbody){
    
    int sock = 0;
    struct hostent *server;
    char** pp;
    clock_t processortime;
    struct sockaddr_in server_address;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <=0 ) {
        err(1, "sock not opening\n\n");
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    const char* hostname = &host[0];
    if ((server = gethostbyname(hostname)) == NULL ) {
        printf("there is no hostname please check : %s\n\n", hostname);
        exit(1);
    }
    char strr[50];
    if ( (pp = server->h_addr_list) != NULL ) {
        printf("address of the server: %s\n\n", inet_ntop(server->h_addrtype, *pp, strr, sizeof(strr)));
    }
              
    server_address.sin_addr.s_addr = inet_addr(inet_ntop(server->h_addrtype, *pp, strr, sizeof(strr)));
    connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
              
    char sendline [MAXLINE + 1]; char recvline [MAXLINE + 1];
    ssize_t n, extra = 0;
    snprintf(sendline, sizeof(sendline),
               "%s %s HTTP/1.0\r\n"
               "Host: %s\r\n"
               "Content-Type: application/json\r\n"
               "Accept: application/json\r\n"
               "Content-length: %lu\r\n\r\n"
               "%s", httpmethod, requesturi , hostname, strlen(requestbody), requestbody);
              
    printf("hyper text transfer protocol request line:\n%s\n\n", sendline);
    processortime = clock();
    write(sock, sendline, strlen(sendline));
    while ((n = read(sock, recvline + extra , sizeof  recvline - extra )) > 0) {
        
        extra += n; recvline[extra] = '\0';
                
    }
    processortime = clock() - processortime;
    close(sock);
    printf("the processor clock duration is : %lu Hertz\n\n", processortime);
    printf("the address of the memory is :%p\n\n",recvline);
    printf("hyper text transfer protocol response line is :\n%s\n\n", recvline);
        
    char* lines = recvline;
    char* nextline = NULL;
    while (lines) {
        nextline = strchr(lines, '\n');
        if (nextline)*nextline = '\0';
            lines = nextline ? (nextline+1) : NULL;
            break;
    }
    printf("%s", recvline);
            
    char* hlines = lines;
        
    while (hlines) {
        nextline = strchr(hlines, '\n');
        if (nextline)*nextline = '\n';
            hlines = nextline ? (nextline+1) : NULL;
        if (*hlines == (char)'\r'){
            if (nextline)*nextline = '\0';break;
        }
    }
        
    char * h = hlines;
    while (h) {
        nextline = strchr(hlines, '\n');
        if (nextline)*nextline = '\0';
        h = nextline ? (nextline+1) : NULL;
        break;
    }

}
