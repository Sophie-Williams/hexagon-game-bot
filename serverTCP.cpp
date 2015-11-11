#include "mylib.h"

#define PORT 779
#define PORT2 889
//char myIPAddres[16];
void serverTCP()
{
	setlocale(LC_ALL, "RUSSIAN");
	WSADATA WsaData;
	SOCKADDR_IN mySockAddr, serverAddr;
	printf("SocketProg:\n");
	printf("My addres: ");
	//getIp();

	printf(", ::: %i\n", PORT);
	

	SOCKET MySocket;

	if (WSAStartup(0x0101, &WsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup() failed: %ld\n", GetLastError());
		getch();
		return;
	}

	MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT2);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*if (bind(MySocket, (LPSOCKADDR)&mySockAddr, sizeof(mySockAddr)) == 0) printf("bind mysock ok...\n");
	else printf("bind my sock error...\n");*/
	connect(MySocket, (SOCKADDR *)& serverAddr, sizeof(serverAddr));
	printf(" %s, ::: %d\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
	//listen(MySocket, SOMAXCONN);
	//int fromlen = sizeof(from);
	//Socket1 = accept(MySocket, (struct sockaddr*)&from, &fromlen);
	char outMessage[61];
	char msgStr[32] = "You are connected to the PC";
	char RecvBuffer[61];
	int recvHex[61];

	send(MySocket, msgStr, strlen(msgStr), MSG_DONTROUTE);
	strcpy(msgStr, "");
	if (recv(MySocket, msgStr, sizeof(msgStr), 0) != SOCKET_ERROR)
	{
		printf("\nserver:::>%s", msgStr);
	}
	else printf("socket error\n");
	//Sleep(5000);
	//strcpy(outMessage, "Socket1 hello");
	//send(Socket1,outMessage,sizeof(outMessage),MSG_DONTROUTE);
	int hex[61];

	while (recv(MySocket, RecvBuffer, sizeof(RecvBuffer), 0) != SOCKET_ERROR)
	{
		int colRed = 0;
		int colBlue = 0;
		printf("\nserver:::>");
		for (int i = 0; i < 61; i++)
		{
			printf("%i", RecvBuffer[i]);
			if ((int)RecvBuffer[i] == 1)colRed++;
			if ((int)RecvBuffer[i] == 2)colBlue++;
		}
		printf("\n");
		char * str = botStart(RecvBuffer,colRed,colBlue);
		for (int i = 0; i < 61; i++)
		{
			outMessage[i]=(int)str[i];
		}
		send(MySocket, outMessage, sizeof(outMessage), MSG_DONTROUTE);
		//break;
	} 
	WSACleanup();
}