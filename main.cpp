#include "mylib.h"
//#include "serverTCP.cpp"
#define CLEAN 0
#define RED 1
#define BLUE 2

node hexag[61];
//int visited[61] = { 0 };
int movePoint(int, int);
int searchRad1(int, int);
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

maxClass checkKillPoint(int point[], int col)
{
	maxClass maxKill;
	for (int i = 0; i < col; i++)
	{
		int idWho = point[i];
		int tmp = 0;
		int tmpMax = 0;
		listNode *tmpList = hexag[point[i]].next;
		while (tmpList != NULL)
		{
			if (tmpList->node->value == CLEAN)
			{
				tmpMax = searchRad1(tmpList->node->id, BLUE);
				printf("For\tid=%i\tmax=%i\trad1\n", idWho, tmpMax);
				if (tmpMax >= maxKill.max)
				{
					maxKill.idWhere = tmpList->node->id;
					maxKill.idWho = idWho;
					maxKill.max = tmpMax;
				}
			}

			listNode *tmpList2 = tmpList->node->next;
			while (tmpList2 != NULL)
			{
				if (tmpList2->node->value == CLEAN)
				{
					tmpMax = searchRad1(tmpList2->node->id, BLUE)-1;
					printf("For\tid=%i\tmax=%i\trad2\n", idWho, tmpMax);
					if (tmpMax > maxKill.max)
					{
						maxKill.idWhere = tmpList2->node->id;
						maxKill.idWho = idWho;
						maxKill.max = tmpMax;
					}
				}
				tmpList2 = tmpList2->next;
			}
			tmpList = tmpList->next;
		}
	}
	return maxKill;
}

char *botStart(char map[], int colRed, int colBlue)
{
	const int MY = RED;
	const int HIS = BLUE;
	maxClass max;
	char *newmap = new char[61];
	int *redPoint = new int[colRed];
	int *blPoint = new int[colBlue];
	//int *myKillPoint = new int[colBlue];
	int r = 0;
	int b = 0;
	for (int i = 0; i < 61; i++)
	{
		hexag[i].value = (int)map[i];
		if (hexag[i].value == RED)
		{
			redPoint[r] = hexag[i].id;
			r++;
		}
		else if (hexag[i].value == BLUE)
		{
			blPoint[b] = hexag[i].id;
			b++;
		}
	}
	
	max = checkKillPoint(redPoint, colRed);
	movePoint(max.idWho, max.idWhere);
	for (int i = 0; i < 61; i++)
	{
		newmap[i] = hexag[i].value;
	}
	return newmap;
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

int movePoint(int who, int where)
{
	int color = hexag[who].value;
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
		listNode *tmpList = hexag[i].next;
		while (tmpList != NULL)
		{
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
	movePoint(15,13);

	for (int i = 0; i < 61; i++)
	{
		printf("%i:\t%i\n",i,hexag[i].value);
	}

	serverTCP();
	printf("\nfinish\n");
	getch();
}