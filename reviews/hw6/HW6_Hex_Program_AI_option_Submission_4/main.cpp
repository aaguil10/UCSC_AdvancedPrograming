//Alexander Sadeghi, Delan Diaz
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "game.h"

//network libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

const int iterations = 10000;
using namespace std;

int main(int argc, char *argv[]){    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);

    }else{
        printf("Attempting to connect to AI to play hex\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    n = read(sockfd, buffer, 255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n", buffer);
    
    cout << "Game of Hex" << endl;
    cout << "AI iterations: " << iterations << endl;
    Game newGame(iterations, 1);
    newGame.play();
    bzero(buffer,256);
	
    if (newGame.win == 0){
        send(sockfd, "AI lost!", 11,0);
    }else if(newGame.win ==1){
        send(sockfd, "AI won!", 11,0);
    }
                                   
    bzero(buffer,256);
    close(sockfd);    
}
