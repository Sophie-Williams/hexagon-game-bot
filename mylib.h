#include "winsock2.h"
#include "conio.h"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "fstream"
#include <vector>
#include "time.h"
#pragma comment(lib,"wsock32.lib")
#pragma warning(disable:4996)			/* for visual studio >=2013 */
using namespace std;

class Step {
public:
	int value;
	int idTo;
	int idFrom;
	int rad;
};

void serverTCP(int**);
char *botStart(int**, int colRed, int colBlue);

