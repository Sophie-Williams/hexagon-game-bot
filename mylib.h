
#include "winsock2.h"
#include "conio.h"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "fstream"
#pragma comment(lib,"wsock32.lib")
#pragma warning(disable:4996)

using namespace std;

struct node
{
	int id=-1;
	int value;
	bool visited = false;
	struct listNode *next = NULL;
};


struct listNode
{
	node *node = NULL;
	listNode *next = NULL;
};

void serverTCP(node hex[]);

