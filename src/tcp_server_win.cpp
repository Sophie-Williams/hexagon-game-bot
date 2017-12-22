#include "winsock2.h"
#include "windows.h"
#include "conio.h"
#include "iostream"
#include "hexagon_bot.h"

#pragma comment(lib,"wsock32.lib")

void tcp_server(int **hexag, int port) {
	setlocale(LC_ALL, "RUSSIAN");
	WSADATA WsaData;
	SOCKADDR_IN serverAddr;
	SOCKET Socket;
	char msgStr[32] = "You are connected to the PC";
	char recvBuffer[HEXAGON_MAP_SIZE];

	printf("Connecting...\n");
	if (WSAStartup(0x0101, &WsaData) == SOCKET_ERROR) {
		printf("WSAStartup() failed: %ld\n", GetLastError());
		getch();
		return;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("IP:\n%s :: %d\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
	connect(Socket, (SOCKADDR *)& serverAddr, sizeof(serverAddr));

	send(Socket, msgStr, strlen(msgStr), MSG_DONTROUTE);
	strcpy(msgStr, "");
	if (recv(Socket, msgStr, sizeof(msgStr), 0) != SOCKET_ERROR) {
		printf("\nServer: %s", msgStr);
	}
	else {
		printf("Socket error\n");
		getch();
		return;
	}
	while (recv(Socket, recvBuffer, sizeof(recvBuffer), 0) != SOCKET_ERROR) {
		int colRed = 0;
		int colBlue = 0;
		printf("\nServer:  ");
		for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
			printf("%i", recvBuffer[i]);
			hexag[i][0] = (int)recvBuffer[i];
			if ((int)recvBuffer[i] == RED) colRed++;
			if ((int)recvBuffer[i] == BLUE) colBlue++;
		}
		printf("\n");
		send(Socket, botStart(hexag, colRed, colBlue), sizeof(char[HEXAGON_MAP_SIZE]), MSG_DONTROUTE);
	}
	WSACleanup();
}