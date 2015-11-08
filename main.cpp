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
//int visited[61] = { 0 };

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
	while (tmpList != NULL)
	{
		if (tmpList->node->value == color)
			tmp++;
		tmpList = tmpList->next;
	}

	return tmp;
}

void reColor(int id, int color)
{
	listNode *tmpList = hexag[id].next;
	while (tmpList != NULL)
	{
		if ((tmpList->node->value != color) && (tmpList->node->value!=CLEAN))
		{
			tmpList->node->value = color;
		}
		tmpList = tmpList->next;
	}
}

bool visited(int id, int visitMass[])
{
	for (int i = 0; i < 18; i++)
	{
		if (id == visitMass[i]) return 1;
	}
	return 0;
}

int move(int who, int where, int color)
{
	int rad = 0;
	int rad2visited[18] = { 0 };
	bool repeat = true;
	listNode *tmpList = hexag[who].next;

	while (tmpList != NULL)
	{
		if (!repeat)
		{
			listNode *tmpList2 = tmpList->node->next;
			while (tmpList2 != NULL)
			{
				if (!visited(tmpList2->node->id,rad2visited))
				if (tmpList2->node->id == where)
				{
					rad = 2;
					break;
				}
				tmpList2 = tmpList2->next;
			}
		}
		else if (tmpList->node->id == where)
		{
			rad = 1;
			break;
		}

		tmpList = tmpList->next;
		if ((tmpList == NULL) && (repeat))
		{
			tmpList = hexag[who].next;
			repeat = false;
		}
	}

	if (rad == 1)
	{
		hexag[where].value = color;
		reColor(where,color);
	}
	else if (rad == 2)
	{
		hexag[who].value = CLEAN;
		hexag[where].value = color;
		reColor(where, color);
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

	hexag[6].value = RED;
	hexag[12].value = RED;
	hexag[20].value = RED;
	hexag[22].value = RED;
	hexag[15].value = BLUE;

	printf("\nSumm = %i\n", searchRad1(13, RED));
	move(15,13, hexag[15].value);

	for (int i = 0; i < 61; i++)
	{
		printf("%i:\t%i\n",i,hexag[i].value);
	}
	printf("\nfinish\n");
	getch();
}