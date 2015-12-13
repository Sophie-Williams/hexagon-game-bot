#include "mylib.h"

#define PORT 889
void serverTCP(int **hexag) {
	setlocale(LC_ALL, "RUSSIAN");
	WSADATA WsaData;
	SOCKADDR_IN serverAddr;
	SOCKET Socket;
	char msgStr[32] = "You are connected to the PC";
	char recvBuffer[61];

	printf("Connecting...\n");
	if (WSAStartup(0x0101, &WsaData) == SOCKET_ERROR) {
		printf("WSAStartup() failed: %ld\n", GetLastError());
		getch();
		return;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("Addres:\n%s :: %d\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
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
		for (int i = 0; i < 61; i++) {
			printf("%i", recvBuffer[i]);
			hexag[i][0] = (int)recvBuffer[i];
			if ((int)recvBuffer[i] == 1)colRed++;
			if ((int)recvBuffer[i] == 2)colBlue++;
		}
		printf("\n");
		send(Socket, botStart(hexag, colRed, colBlue), sizeof(char[61]), MSG_DONTROUTE);
	}
	WSACleanup();
}