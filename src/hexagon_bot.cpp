//
// Created by sfaxi19 on 22.12.17.
//
#include <cstring>
#include "iostream"
#include "hexagon_bot.h"

int searchRad1(int, int);


void bindNodes(int **hexag, int idLink, int idNode) {
    int i = 1;
    while ((hexag[idNode][i] != -1) && (i < 7)) {
        i++;
    }
    hexag[idNode][i] = idLink;
}

Step estimate(int **hexag, int idFrom, int idTo, int rad) {
    Step step;
    int blue = 0;
    int red = 0;
    int **tmpHexag = new int *[HEXAGON_MAP_SIZE];
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        tmpHexag[i] = new int[7];
    }
    tmpHexag = movePoint(hexag, idFrom, idTo, rad);
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        switch (tmpHexag[i][0]) {
            case BLUE:
                blue++;
                break;
            case RED:
                red++;
                break;
            default:
                break;
        }
    }
    step.idFrom = idFrom;
    step.idTo = idTo;
    step.rad = rad;
    step.value = red - blue;
    return step;
}

std::vector<int> searchMyPoints(int **hexag, int color) {
    std::vector<int> points;
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        if (hexag[i][0] == color) {
            points.insert(points.end(), i);
        }
    }
    return points;
}

Step min_el(std::vector<Step> scores) {
    Step min;
    min.value = 255;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i].value < min.value) {
            min.value = scores[i].value;
            min.idTo = scores[i].idTo;
            min.idFrom = scores[i].idFrom;
            min.rad = scores[i].rad;
        }
    }
    return min;
}

int max_el_id(std::vector<Step> steps) {
    int max = -255;
    int idMax = 0;
    for (int i = 0; i < steps.size(); i++) {
        if (steps[i].value > max) {
            max = steps[i].value;
            idMax = i;
        }
    }
    return idMax;
}

Step max_el(std::vector<Step> steps) {
    Step max;
    max.value = -255;
    for (int i = 0; i < steps.size(); i++) {
        if (steps[i].value > max.value) {
            max.value = steps[i].value;
            max.idTo = steps[i].idTo;
            max.idFrom = steps[i].idFrom;
            max.rad = steps[i].rad;
        }
    }
    return max;
}

void showVector(std::vector<Step> steps, int rad, int level) {
    int sum = 0;
    printf("level = %i\n", level);
    for (int i = 0; i < steps.size(); i++) {
        printf("%2i|", steps[i].value);
    }
    printf("\n");
}

Step random(std::vector<Step> steps) {
    int tmp;
    if (steps.size() == 1) return steps[0];
    int max = steps.size() - 1;
    tmp = 0 + rand() % max;
    return steps[tmp];
}

std::vector<Step> amputation(std::vector<Step> steps, int level) {
    int sum = 0;
    int mean = 0;
    int max = -255;
    int min = 255;
    Step tmp = random(steps);
    for (int i = 0; i < steps.size(); i++) {
        if (steps[i].value > max) max = steps[i].value;
        if (steps[i].value < min) min = steps[i].value;
    }
    mean = (int) ((max + min) / 2);
    for (int i = 0; i < steps.size();) {
        if (level % 2 != 0) {
            if (steps[i].value < mean) {
                steps.erase(steps.begin() + i);
            } else i++;
        } else {
            if (steps[i].value > mean) {
                steps.erase(steps.begin() + i);
            } else i++;
        }
    }
    if (steps.size() == 0) steps.insert(steps.end(), tmp);
    return steps;
}

void finish() {
    printf("The End\n");
}

Step checkKillPoint(int **hexag, int color, int idFrom, int idTo, int rad, int level) {
    std::vector<int> points;
    std::vector<Step> steps;
    std::vector<Step> steps2;
    int from;
    bool visited[HEXAGON_MAP_SIZE] = {0};
    level++;
    int **tmpHexag = new int *[HEXAGON_MAP_SIZE];
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        tmpHexag[i] = new int[7];
    }
    if (idFrom != -1) {
        tmpHexag = movePoint(hexag, idFrom, idTo, rad);
    } else {
        for (int i = 0; i < HEXAGON_MAP_SIZE; i++)
            for (int j = 0; j < 7; j++)
                tmpHexag[i][j] = hexag[i][j];
    }

    points = searchMyPoints(tmpHexag, color);
    for (int i = 0; i < points.size(); i++) {
        int j = 1;
        from = points[i];

        visited[points[i]] = true;
        /*radius 1*/
        while ((tmpHexag[points[i]][j] != -1) && (j < 7)) {
            visited[tmpHexag[points[i]][j]] = true;
            if (tmpHexag[tmpHexag[points[i]][j]][0] == CLEAN) {
                steps.insert(steps.end(), estimate(tmpHexag, from, tmpHexag[points[i]][j], 1));
            }
            j++;
        }

        /*radius 2*/
        j = 1;
        while ((tmpHexag[points[i]][j] != -1) && (j < 7)) {
            int c = 1;
            while ((tmpHexag[tmpHexag[points[i]][j]][c] != -1) && (c < 7)) {
                if ((!visited[tmpHexag[tmpHexag[points[i]][j]][c]]) &&
                    (tmpHexag[tmpHexag[tmpHexag[points[i]][j]][c]][0] == CLEAN)) {
                    visited[tmpHexag[tmpHexag[points[i]][j]][c]] = true;
                    steps.insert(steps.end(), estimate(tmpHexag, from, tmpHexag[tmpHexag[points[i]][j]][c], 2));
                }
                c++;
            }
            j++;
        }
    }
    if (steps.size() != 0) {
        steps = amputation(steps, level);
    }
    if (level < DEPTH) {
        if (level == 1) {
            for (int i = 0; i < steps.size(); i++) {
                steps2.insert(steps2.end(),
                              checkKillPoint(tmpHexag, color % 2 + 1, steps[i].idFrom, steps[i].idTo, steps[i].rad,
                                             level));
            }
        } else {
            if (level % 2 == 0) {
                Step min = min_el(steps);
                return checkKillPoint(tmpHexag, color % 2 + 1, min.idFrom, min.idTo, min.rad, level);
            } else {
                Step max = max_el(steps);
                return checkKillPoint(tmpHexag, color % 2 + 1, max.idFrom, max.idTo, max.rad, level);
            }
        }
    }
    if (level == DEPTH) {
        return max_el(steps);
    }
    if (level == 1) {
        return steps[max_el_id(steps2)];
    }
}

int **movePoint(int **hexag, int fromNode, int toNode, int rad) {
    int **tmpHexag = new int *[HEXAGON_MAP_SIZE];
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        tmpHexag[i] = new int[7];
        for (int j = 0; j < 7; j++) tmpHexag[i][j] = hexag[i][j];
    }
    if (rad == 1) {
        tmpHexag[toNode][0] = tmpHexag[fromNode][0];
        reColor(tmpHexag, toNode, tmpHexag[fromNode][0]);
        return tmpHexag;
    }
    if (rad == 2) {
        tmpHexag[toNode][0] = tmpHexag[fromNode][0];
        reColor(tmpHexag, toNode, tmpHexag[fromNode][0]);
        tmpHexag[fromNode][0] = CLEAN;
        return tmpHexag;
    }
    return tmpHexag;
}

char *botStart(int **hexag, int colRed, int colBlue) {
    Step myStep;
    int com = 0;
    int pl = 0;
    char *newmap;
    newmap = new char[HEXAGON_MAP_SIZE];

    myStep = checkKillPoint(hexag, PC, -1, -1, 1, 0);
    printf("-->From: %i - To: %i\n", myStep.idFrom, myStep.idTo);

    hexag = movePoint(hexag, myStep.idFrom, myStep.idTo, myStep.rad);
    printf("Sending: ");
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        printf("%i", hexag[i][0]);
        newmap[i] = hexag[i][0];
    }
    printf("\n");
    return newmap;
}

void parsingString(int **hexag, int idNode, char str[35]) {
    int i = 0;
    int c = 0;
    int idLink = 0;
    char tmp[3] = "";
    while (str[i] != '\0') {
        if (str[i] == ',') {
            tmp[c] = '\0';
            idLink = atoi(tmp);
            strcpy(tmp, "");
            c = 0;
            bindNodes(hexag, idLink, idNode);
        }

        if (str[i] != ',') {
            tmp[c] = str[i];
            c++;
        }
        i++;
    }
}

int graphCreate(int **hexag) {
    std::ifstream fmatrix("matrix2.mx");
    char tmp[35];
    for (int i = 0; i < HEXAGON_MAP_SIZE; i++) {
        fmatrix.getline(tmp, 35);
        parsingString(hexag, i, tmp);
    }
    fmatrix.close();
    return 0;
}

void reColor(int **hexag, int idNode, int toColor) {
    int i = 1;
    while ((hexag[idNode][i] != -1) && (i < 7)) {
        if ((hexag[hexag[idNode][i]][0] != toColor) && (hexag[hexag[idNode][i]][0] != CLEAN))
            hexag[hexag[idNode][i]][0] = toColor;
        i++;
    }
}