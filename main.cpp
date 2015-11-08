#include "conio.h"
#include "stdio.h"
#include "fstream"
#include "iostream"
#include "mylib.h"
#pragma warning(disable:4996)
#define CLEAN 0
#define RED 1
#define BLUE 2
using namespace std;
node hexag[61];
int visited[61] = { 0 };

void bindNodes(int id, int idHex)
{
	listNode *newList = new listNode;
	newList->node = &hexag[id];
	listNode *tmpList = hexag[idHex].next;
	if (tmpList == NULL)
	{
		hexag[idHex].next = newList;
	}
	else
	{
		while (tmpList->next != NULL)
		{
			tmpList = tmpList->next;
		}
		tmpList->next = newList;
	}
}

void parsingString(int idHex, char str[35])
{
	int i = 0;
	int c = 0;
	int id = 0;
	char tmp[3] = "";
	hexag[idHex].id = idHex;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
		{
			tmp[c] = '\0';
			id = atoi(tmp);
			strcpy(tmp, "");
			c = 0;
			bindNodes(id,idHex);
		}

		if (str[i] != ',')
		{

			tmp[c] = str[i];
			c++;
		}
		i++;
	}
}

int graphCreate()
{
	ifstream fmatrix("matrix2.mx");
	char tmp[35];
	for (int i = 0; i < 61; i++)
	{
		fmatrix.getline(tmp, 35);
		parsingString(i,tmp);
	}
	fmatrix.close();
	return 0;
}

int searchRad1(int id, int color)
{
	int tmp = 0;
	listNode *tmpList = hexag[id].next;
	printf("id = %i\nvalue = %i\nnodes: ", hexag[id].id, hexag[id].value);

	while (tmpList != NULL)
	{
		if (tmpList->node->value == color)
			tmp++;
		printf("%i\t", tmpList->node->value);
		tmpList = tmpList->next;
	}

	return tmp;
}

int move(int who, int were)
{
	listNode *tmpList = hexag[who].next;
	int rad = 0;
	while (tmpList != NULL)
	{
		if (tmpList->node->id == were)
		{
			rad = 1;
			continue;
		}
		tmpList = tmpList->next;
	}



	return 0;
}
void main()
{
	graphCreate();
	
	for (int i = 0; i < 61; i++)
	{
		printf("id=%i:\t",hexag[i].id);
		listNode *tmpList = hexag[i].next;
		while (tmpList != NULL)
		{
			printf("%i\t",tmpList->node->id);
			tmpList = tmpList->next;
		}
		printf("\n");
	}

	hexag[21].value = RED;
	printf("\nSumm = %i\n", searchRad1(13, RED));
	move(14,13);
	printf("\nfinish\n");
	getch();
}