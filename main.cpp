#include "mylib.h"
//#include "serverTCP.cpp"
#define CLEAN 0
#define RED 1
#define BLUE 2

int hexag[61][7];
int movePoint(int, int);
int searchRad1(int, int);

void bindNodes(int idLink, int idNode)
{
	int i = 1;
	while ((hexag[idNode][i] != -1) && (i<7))
	{
		i++;
	}
	hexag[idNode][i] = idLink;
}

maxClass checkKillPoint(int point[], int col)
{
	maxClass maxKill;
	for (int i = 0; i < col; i++)
	{
		int idFrom = point[i];
		int tmp = 0;
		int tmpMax = 0;
		int j = 1;

		while ((hexag[point[i]][j] != -1) && (j<7))
		{
			if (hexag[hexag[point[i]][j]][0] == CLEAN)
			{
				tmpMax = searchRad1(hexag[point[i]][j], BLUE);
				printf("For\tid=%i\tmax=%i\trad1\n", idFrom, tmpMax);
				if (tmpMax >= maxKill.max)
				{
					maxKill.idTo = hexag[point[i]][j];
					maxKill.idFrom = idFrom;
					maxKill.max = tmpMax;
				}
			}
			j++;
		}

		j = 1;
		while ((hexag[point[i]][j] != -1) && (j<7))
		{
			int c = 1;
			while ((hexag[hexag[point[i]][j]][c] != -1) && (c<7))
			{
				if (hexag[hexag[hexag[point[i]][j]][c]][0] == CLEAN)
				{
					tmpMax = searchRad1(hexag[hexag[point[i]][j]][c], BLUE) - 1;
					printf("For\tid=%i\tmax=%i\trad1\n", idFrom, tmpMax);
					if (tmpMax > maxKill.max)
					{
						maxKill.idTo = hexag[point[i]][j];
						maxKill.idFrom = idFrom;
						maxKill.max = tmpMax;
					}
				}
				c++;
			}
			j++;
		}
	}
	return maxKill;
}

char *botStart(char map[], int colRed, int colBlue)
{
	const int COM = RED;
	const int PLAYER = BLUE;
	maxClass max;
	char *newmap = new char[61];
	int *comPoint = new int[colRed];
	int *plPoint = new int[colBlue];
	//int *myKillPoint = new int[colBlue];
	int com = 0;
	int pl = 0;
	for (int i = 0; i < 61; i++)
	{
		hexag[i][0] = (int)map[i];
		if (hexag[i][0] == COM)
		{
			comPoint[com] = i;
			com++;
		}
		else if (hexag[i][0] == PLAYER)
		{
			plPoint[pl] = i;
			pl++;
		}
	}
	
	printf("was get:\n");
	for (int i = 0; i < 61; i++) printf("%i", hexag[i][0]);
	printf("\n");
	max = checkKillPoint(comPoint, colRed);
	printf("post checkKill:\n");
	for (int i = 0; i < 61; i++) printf("%i",hexag[i][0]);
	printf("\n");
	movePoint(max.idFrom, max.idTo);
	for (int i = 0; i < 61; i++)
	{
		newmap[i] = hexag[i][0];
	}
	return newmap;
}

void parsingString(int idNode, char str[35])
{
	int i = 0;
	int c = 0;
	int idLink = 0;
	char tmp[3] = "";
	//hexag[idHex].id = idHex;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
		{
			tmp[c] = '\0';
			idLink = atoi(tmp);
			strcpy(tmp, "");
			c = 0;
			bindNodes(idLink,idNode);
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

int searchRad1(int idNode, int color)
{
	int tmp = 0;

	int i = 1;
	
	while ((hexag[idNode][i] != -1) && (i<7))
	{
		if (hexag[hexag[idNode][i]][0] == color)
			tmp++;
		i++;
	}
	return tmp;
}

void reColor(int idNode, int toColor)
{
	printf("remake in:%i\n", toColor);
	int i = 1;
	while ((hexag[idNode][i] != -1) && (i<7))
	{
		if ((hexag[hexag[idNode][i]][0] != toColor) && (hexag[hexag[idNode][i]][0] != CLEAN))
			hexag[hexag[idNode][i]][0] = toColor;
		i++;
	}

	printf("post reColor:\n");
	for (int i = 0; i < 61; i++) printf("%i", hexag[i][0]);
	printf("\n");
}

bool visited(int id, int visitMass[])
{
	for (int i = 0; i < 18; i++)
	{
		if (id == visitMass[i]) return 1;
	}
	return 0;
}

//---movePoint return 1 if all right
int movePoint(int fromNode, int toNode)
{
	int toColor = hexag[fromNode][0];
	int i = 1;

	while ((hexag[fromNode][i] != -1) && (i<7))
	{
		//visited[hexag[fromNode][i]] = 1;
		if (hexag[fromNode][i] == toNode)
		{
			hexag[toNode][0] = hexag[fromNode][0];
			printf("pre reColor:\n");
			for (int i = 0; i < 61; i++) printf("%i", hexag[i][0]);
			printf("\n");
			reColor(toNode, toColor);
			return 1;
		}
		i++;
	}

	while ((hexag[fromNode][i] != -1) && (i<7))
	{
		int j = 1;
		while ((hexag[hexag[fromNode][i]][j] != -1) && (j<7))
		{
			if (hexag[hexag[fromNode][i]][j]==toNode)
			{
				hexag[toNode][0] = hexag[fromNode][0];
				hexag[fromNode][0] = CLEAN;
				printf("pre reColor:\n");
				for (int i = 0; i < 61; i++) printf("%i", hexag[i][0]);
				printf("\n");
				reColor(toNode, toColor);
				return 1;
			}
		}
	}

	printf("post move:\n");
	for (int i = 0; i < 61; i++) printf("%i",hexag[i][0]);
	printf("\n");
	return 0;
}

void main()
{
	for (int i = 0; i < 61; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j == 0)hexag[i][j] = 0;
			else hexag[i][j] = -1;
		}
	}
	graphCreate();

	printf("\nSumm = %i\n", searchRad1(13, RED));
	//movePoint(15,13);

	printf("main:\n");
	for (int i = 0; i < 61; i++) printf("%i",hexag[i][0]);
	printf("\n");

	serverTCP();
	printf("\nfinish\n");
	getch();
}