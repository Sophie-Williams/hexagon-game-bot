//
// Created by sfaxi19 on 22.12.17.
//
//#include <sys/socket.h>
//#include <cstring>
//#include <netinet/in.h>
//#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "hexagon_bot.h"

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void tcp_server(int **hexag, int port) {
    char msgStr[32] = "You are connected to the PC";
    char recvBuffer[HEXAGON_MAP_SIZE] = {0};
    int sock, new_socket;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    listen(sock, 5);
    clilen = sizeof(cli_addr);
    new_socket = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
    if (new_socket < 0) error("ERROR on accept");
    n = write(new_socket, msgStr, strlen(msgStr));
    if (n < 0) error("ERROR write first msgStr to client");
    strcpy(msgStr, "");

    n = read(new_socket, msgStr, sizeof(msgStr));
    if (n < 0) error("ERROR reading from socket");
    printf("\nServer: %s", msgStr);

    while (read(new_socket, recvBuffer, sizeof(recvBuffer)) >= 0) {
        int colRed = 0;
        int colBlue = 0;
        printf("\nServer:  ");
        for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
            printf("%i", recvBuffer[i]);
            hexag[i][0] = (int) recvBuffer[i];
            if ((int) recvBuffer[i] == RED) colRed++;
            if ((int) recvBuffer[i] == BLUE) colBlue++;
        }
        printf("\n");
        write(new_socket, botStart(hexag, colRed, colBlue), sizeof(char[HEXAGON_MAP_SIZE]));
    }
    close(new_socket);
    close(sock);
}