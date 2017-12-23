#include <cstring>
#include "hexagon_bot.h"
#ifdef _WIN32
    #include "conio.h"
    #include "windows.h"
#endif

int main() {
    int port = 889;
    srand(time(NULL));
#ifdef _WIN32
    printf("Press SPACE for running visual program\nfrom path = %s\n",
           "\"HexagonVisual\\HexagonVisual\\bin\\Release\\HexagonVisual.exe\"");
    if ((int) getch() == 32) {
        system("start open.bat");
        printf("Starting visual program\n");
        Sleep(1000);
    } else system("cls");
#elif __linux__
    printf("Hexagon server was started on this machine with port: %d\n", 889);
#endif
    /*
    hexag[i][0] - value for this node
    hexag[i][1..6] - linkages
    */

    int **hexag = new int *[HEXAGON_MAP_SIZE];
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        hexag[i] = new int[HEXAGON_MAP_NODE_LINKS];
        for (int j = 0; j < HEXAGON_MAP_NODE_LINKS; j++) {
            if (j == 0)hexag[i][j] = 0;
            else hexag[i][j] = -1;
        }
    }
    graphCreate(hexag);
    tcp_server(hexag, port);
    printf("\nfinish\n");
    return 0;
}
