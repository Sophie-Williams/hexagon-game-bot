#include "iostream"
//#include "stdio.h"
#include "fstream"
#include <vector>
#include "time.h"
//#pragma warning(disable:4996)			/* for visual studio >=2013 */

#define CLEAN 0
#define RED 1
#define BLUE 2
#define DEPTH 4
#define PC 1

// HEXAGON_MAP_NODE_LINKS - Number of links for nodes, and 1 link (link0) for value current node
// Example:
//          link1
//         +-----+
// link6  /       \  link2
//       /  link0  \
//       \         /
// link5  \       / link3
//         +-----+
//          link4
// HEXAGON_MAP_NODE_LINKS = 7

#define HEXAGON_MAP_NODE_LINKS 7
#define HEXAGON_MAP_SIZE 61


class Step {
public:
    int value;
    int idTo;
    int idFrom;
    int rad;
};

void tcp_server(int **hexag, int port);

void reColor(int **, int, int);

int **movePoint(int **, int, int, int);

int graphCreate(int **hexag);

char *botStart(int **, int colRed, int colBlue);
