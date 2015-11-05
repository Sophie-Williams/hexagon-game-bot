#include "stdio.h"
#include "conio.h"
#include "fstream"
#include "iostream"
#include "stdlib.h"
#include "mylib.h"
#pragma warning(disable:4996)
using namespace std;


graphType graph;
struct matrixT
{
	connect	conn[3];
}matrix[61];

void printMatrix(matrixT matrix[])
{
	for (int i = 0; i < 61; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matrix[i].conn[j].active)
				printf("%i.%i - %i.%i\t", matrix[i].conn[j].idNew, matrix[i].conn[j].inputNew,matrix[i].conn[j].idConn, matrix[i].conn[j].inputConn);
		}
		printf("\n");
	}
}



struct playerList
{

};

nodeType *searchNode(int id)
{
	nodeType *tmp = graph.head;
	int p = 3;
	bool down = true;
	bool endColl = false;
	while (tmp->id != id)
	{
		if (tmp->input[p] == NULL)
		{
			endColl = true;
			if (down) p--;
			else p++;
			if (tmp->input[p] == NULL)
			{
				if (down) p--;
				else p++;
			}
		}
		tmp = tmp->input[p];
		if (endColl)
		{
			if (down)
			{
				p = 0;
				down = false;
			}
			else 
			{ 
				p = 3; 
				down = true; 
			}
			endColl = false;
		}
	}
	return tmp;
}
int addNode(int id, connect conn[])
{
	nodeType *nodeNew = new nodeType;
	if (id == 0)
	{
		nodeNew->id = id;
		graph.head = nodeNew;
	}
	else
	{
		nodeNew->id = id;
		nodeNew->input[conn[0].inputNew] = graph.tail;
		graph.tail->input[conn[0].inputConn] = nodeNew;
		for (int i = 1; i < 3; i++)
		{
			if (conn[i].active)
			{
				nodeType *connNode = searchNode(conn[i].idConn);
				nodeNew->input[conn[i].inputNew] = connNode;
				connNode->input[conn[i].inputConn] = nodeNew;
			}
		}
	}
	graph.tail = nodeNew;
	return 0;
}

void reCreate(char str[35], connect conn[])
{
	int i = 0;
	int j = 0;
	int c = 0;
	bool first = true;
	char tmp[5]="";
	
	//---14.3*15.0,14.4/7.1,14.5/8.2,
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			conn[j].active = true;
			tmp[c] = '\0';
			if (first)
			{
				conn[j].idNew= atoi(tmp);
			}
			else conn[j].idConn = atoi(tmp);
			strcpy(tmp,"");
			c = 0;
		}

		if (str[i] == '/')
		{
			tmp[c] = '\0';
			conn[j].inputNew = atoi(tmp);
			first = false;
			strcpy(tmp, "");
			c = 0;
		}

		if (str[i] == ',')
		{
			tmp[c] = '\0';
			conn[j].inputConn= atoi(tmp);
			j++;
			
			first = true;
			strcpy(tmp, "");
			c = 0;
		}
		if ((str[i] != '.') && (str[i] != ',') && (str[i] != '/') && (str[i] != '*'))
		{

			tmp[c] = str[i];
			c++;
		}
		i++;
	}
}

void main()
{
	char fromMtx[61][35];
	ifstream fmatrix("matrix.mx");
	for (int i = 0; i < 61; i++)
	{
		fmatrix.getline(fromMtx[i],35);
		reCreate(fromMtx[i], matrix[i].conn);
	}
	fmatrix.close();

	printMatrix(matrix);

	for (int i = 0; i < 61; i++)
	{
		addNode(i, matrix[i].conn);
	}

	for (int i = 0; i < 61; i++)
	{
		nodeType*tmpNode = searchNode(i);
		printf("%i  ->  ",tmpNode->id);
		for (int j = 0; j < 6; j++)
		{
			if (tmpNode->input[j]!=NULL)
			printf("%i, ", tmpNode->input[j]->id);
			else printf("null, ");
		}
		printf("\n");
	}
	printf("\nfinish\n");
	getch();
}