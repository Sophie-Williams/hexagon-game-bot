#include "mylib.h"

#define PORT 779
#define PORT2 889
//char myIPAddres[16];
void serverTCP(node hex[])
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
	mySockAddr.sin_family = AF_INET;
	mySockAddr.sin_port = htons(PORT);
	mySockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT2);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*if (bind(MySocket, (LPSOCKADDR)&mySockAddr, sizeof(mySockAddr)) == 0) printf("bind mysock ok...\n");
	else printf("bind my sock error...\n");*/
	connect(MySocket, (SOCKADDR *)& serverAddr, sizeof(serverAddr));
	//listen(MySocket, SOMAXCONN);

	printf("listening...\n");

	//int fromlen = sizeof(from);
	//Socket1 = accept(MySocket, (struct sockaddr*)&from, &fromlen);
	printf("Соединение с %s, ::: %d\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
	printf(":::::::::::::::::::::::::::::::::::\n");

	//Sleep(5000);
	//strcpy(outMessage, "Socket1 hello");
	//send(Socket1,outMessage,sizeof(outMessage),MSG_DONTROUTE);
//	int hex[61] = { 0, 0, 1, 2 };
	char outMessage[61]="Hi!how are you?";
	char RecvBuffer[128]="";
	do
	{
		printf("\nserver:::>%s\n", RecvBuffer);
		printf("\n");
		//strcpy(outMessage, RecvBuffer);
		//Sleep(3000);
		printf(outMessage);
		printf("\n");
		char *tmp="";
		for (int i = 0; i<61; i++)
		{
			outMessage[i] = hex[i].value;
		}
		send(MySocket, outMessage, sizeof(outMessage), MSG_DONTROUTE);

	} while (recv(MySocket, RecvBuffer, sizeof(RecvBuffer), 0) != SOCKET_ERROR);
	WSACleanup();
}