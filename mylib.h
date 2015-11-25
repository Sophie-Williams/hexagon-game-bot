#include "winsock2.h"
#include "conio.h"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "fstream"
#pragma comment(lib,"wsock32.lib")
#pragma warning(disable:4996)			/* for visual studio >=2013 */
using namespace std;

class maxClass
{
public:
	int max = 0;
	int idFrom = -1;
	int idTo = -1;
};
void serverTCP();
char *botStart(char map[], int colRed, int colBlue);

