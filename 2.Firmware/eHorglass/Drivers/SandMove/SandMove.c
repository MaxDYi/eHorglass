#include "SandMove.h"


coord Sand_GetLoopCoord(uint8_t index, uint8_t direction, uint8_t randNum) {
    coord xy;
    switch (direction % 8)
    {
    case (0): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {7,0},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7},
            {6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7},
            {5,0},{5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},
            {4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},
            {3,0},{3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},
            {2,0},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},
            {1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},
            {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7}
        };
        xy.x = loopCoords[index][0];
        xy.y = loopCoords[index][1];
        break;
    }
    case (1): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
           {7,7},
           {6,7},{7,6},
           {5,7},{6,6},{7,5},
           {4,7},{5,6},{6,5},{7,4},
           {3,7},{4,6},{5,5},{6,4},{7,3},
           {2,7},{3,6},{4,5},{5,4},{6,3},{7,2},
           {1,7},{2,6},{3,5},{4,4},{5,3},{6,2},{7,1},
           {0,7},{1,6},{2,5},{3,4},{4,3},{5,2},{6,1},{7,0},
           {0,6},{1,5},{2,4},{3,3},{4,2},{5,1},{6,0},
           {0,5},{1,4},{2,3},{3,2},{4,1},{5,0},
           {0,4},{1,3},{2,2},{3,1},{4,0},
           {0,3},{1,2},{2,1},{3,0},
           {0,2},{1,1},{2,0},
           {0,1},{1,0},
           {0,0}
        };
        /*
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {7,7},
            {6,7},{7,6},
            {6,6},{5,7},{7,5},
            {5,6},{6,5},{4,7},{7,4},
            {5,5},{4,6},{6,4},{3,7},{7,3},
            {4,5},{5,4},{3,6},{6,3},{2,7},{7,2},
            {4,4},{3,5},{5,3},{2,6},{6,2},{1,7},{7,1},
            {3,4},{4,3},{2,5},{5,2},{1,6},{6,1},{0,7},{7,0},
            {3,3},{2,4},{4,2},{1,5},{5,1},{0,6},{6,0},
            {2,3},{3,2},{1,4},{4,1},{0,5},{5,0},
            {2,2},{1,3},{3,1},{0,4},{4,0},
            {1,2},{2,1},{0,3},{3,0},
            {1,1},{0,2},{2,0},
            {0,1},{1,0},
            {0,0}
        };
        */
        if (randNum == 0) {
            xy.x = loopCoords[index][0];
            xy.y = loopCoords[index][1];
        }
        else {
            xy.x = loopCoords[index][1];
            xy.y = loopCoords[index][0];
        }
        break;

    }
    case (2): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {0,7},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7},
            {0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},
            {0,5},{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},
            {0,4},{1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},
            {0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},
            {0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
            {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
            {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0}

        };
        xy.x = loopCoords[index][0];
        xy.y = loopCoords[index][1];
        break;
    }
    case (3): {
        /*
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
           {0,7},
           {1,7},{0,6},
           {1,6},{2,7},{0,5},
           {2,6},{1,5},{3,7},{0,4},
           {2,5},{3,6},{1,4},{4,7},{0,3},
           {3,5},{4,6},{2,4},{1,3},{5,7},{0,2},
           {3,4},{4,5},{2,3},{5,6},{1,2},{6,7},{0,1},
           {4,4},{3,3},{5,5},{2,2},{6,6},{1,1},{7,7},{0,0},
           {4,3},{5,4},{3,2},{6,5},{2,1},{7,6},{1,0},
           {5,3},{4,2},{6,4},{3,1},{7,5},{2,0},
           {5,2},{6,3},{4,1},{7,4},{3,0},
           {5,1},{6,2},{7,3},{4,0},
           {6,1},{7,2},{5,0},
           {7,1},{6,0},
           {7,0},
        };
        */
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
             {0,7},
             {1,7},{0,6},
             {2,7},{1,6},{0,5},
             {3,7},{2,6},{1,5},{0,4},
             {4,7},{3,6},{2,5},{1,4},{0,3},
             {5,7},{4,6},{3,5},{2,4},{1,3},{0,2},
             {6,7},{5,6},{4,5},{3,4},{2,3},{1,2},{0,1},
             {7,7},{6,6},{5,5},{4,4},{3,3},{2,2},{1,1},{0,0},
             {7,6},{6,5},{5,4},{4,3},{3,2},{2,1},{1,0},
             {7,5},{6,4},{5,3},{4,2},{3,1},{2,0},
             {7,4},{6,3},{5,2},{4,1},{3,0},
             {7,3},{6,2},{5,1},{4,0},
             {7,2},{6,1},{5,0},
             {7,1},{6,0},
             {7,0}
        };
        if (randNum == 0) {
            xy.x = loopCoords[index][0];
            xy.y = loopCoords[index][1];
        }
        else {
            xy.x = loopCoords[index][1];
            xy.y = loopCoords[index][0];
        }
        break;
    }
    case (4): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},
            {1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},
            {2,0},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},
            {3,0},{3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},
            {4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},
            {5,0},{5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},
            {6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7},
            {7,0},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7}
        };
        xy.x = loopCoords[index][0];
        xy.y = loopCoords[index][1];
        break;
    }
    case (5): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {0,0},
            {1,0},{0,1},
            {2,0},{1,1},{0,2},
            {3,0},{2,1},{1,2},{0,3},
            {4,0},{3,1},{2,2},{1,3},{0,4},
            {5,0},{4,1},{3,2},{2,3},{1,4},{0,5},
            {6,0},{5,1},{4,2},{3,3},{2,4},{1,5},{0,6},
            {7,0},{6,1},{5,2},{4,3},{3,4},{2,5},{1,6},{0,7},
            {7,1},{6,2},{5,3},{4,4},{3,5},{2,6},{1,7},
            {7,2},{6,3},{5,4},{4,5},{3,6},{2,7},
            {7,3},{6,4},{5,5},{4,6},{3,7},
            {7,4},{6,5},{5,6},{4,7},
            {7,5},{6,6},{5,7},
            {7,6},{6,7},
            {7,7}
        };
        if (randNum == 0) {
            xy.x = loopCoords[index][0];
            xy.y = loopCoords[index][1];
        }
        else {
            xy.x = loopCoords[index][1];
            xy.y = loopCoords[index][0];
        }
        break;
    }
    case (6): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},
            {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
            {0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
            {0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},
            {0,4},{1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},
            {0,5},{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},
            {0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},
            {0,7},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7}
        };
        xy.x = loopCoords[index][0];
        xy.y = loopCoords[index][1];
        break;
    }
    case (7): {
        int loopCoords[LED_WIDTH * LED_WIDTH][2] = {
            {7,0},
            {6,0},{7,1},
            {5,0},{6,1},{7,2},
            {4,0},{5,1},{6,2},{7,3},
            {3,0},{4,1},{5,2},{6,3},{7,4},
            {2,0},{3,1},{4,2},{5,3},{6,4},{7,5},
            {1,0},{2,1},{3,2},{4,3},{5,4},{6,5},{7,6},
            {0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},
            {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},
            {0,2},{1,3},{2,4},{3,5},{4,6},{5,7},
            {0,3},{1,4},{2,5},{3,6},{4,7},
            {0,4},{1,5},{2,6},{3,7},
            {0,5},{1,6},{2,7},
            {0,6},{1,7},
            {0,7}
        };
        if (randNum == 0) {
            xy.x = loopCoords[index][0];
            xy.y = loopCoords[index][1];
        }
        else {
            xy.x = loopCoords[index][1];
            xy.y = loopCoords[index][0];
        }
        break;
    }
    }
    return xy;
}

void Sand_GetTarget(coord now_xy, coord* target_xy, uint8_t direction) {
    int operandsX[DIRECTION_NUM] = { 1,1,0,-1,-1,-1,0,1 };
    int operandsY[DIRECTION_NUM] = { 0,1,1,1,0,-1,-1,-1 };
    target_xy[MID].x = now_xy.x + operandsX[direction];
    target_xy[MID].y = now_xy.y + operandsY[direction];
    target_xy[LEFT].x = now_xy.x + operandsX[(direction + 1) % 8];
    target_xy[LEFT].y = now_xy.y + operandsY[(direction + 1) % 8];
    target_xy[RIGHT].x = now_xy.x + operandsX[(direction - 1) % 8];
    target_xy[RIGHT].y = now_xy.y + operandsY[(direction - 1) % 8];
}

uint8_t Sand_GetUpLed(uint8_t gDirection) {
    if (gDirection < DIRECTION_NUM / 2) {
        return LED_SCREEN_1;
    }
    else {
        return LED_SCREEN_2;
    }
}

uint8_t Sand_GetDownLed(uint8_t gDirection) {
    if (gDirection < DIRECTION_NUM / 2) {
        return LED_SCREEN_2;
    }
    else {
        return LED_SCREEN_1;
    }
}

uint8_t Sand_IsBorder(int x) {
    if (x < 0 || x>LED_WIDTH - 1) {
        return OUT;
    }
    else {
        return IN;
    }
}

uint8_t Sand_IsVertex(coord target_xy, uint8_t direction) {
    if (Sand_IsUpVertex(target_xy, direction) == TRUE || Sand_IsDownVertex(target_xy, direction) == TRUE) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

uint8_t Sand_IsDownVertex(coord target_xy, uint8_t direction) {
    if ((direction < DIRECTION_NUM / 2)) {
        if (target_xy.x == LED_WIDTH && target_xy.y == LED_WIDTH) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        if (target_xy.x == -1 && target_xy.y == -1) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
}

uint8_t Sand_IsUpVertex(coord target_xy, uint8_t direction) {
    if ((direction < DIRECTION_NUM / 2)) {
        if (target_xy.x == -1 && target_xy.y == -1) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        if (target_xy.x == LED_WIDTH && target_xy.y == LED_WIDTH) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
}

uint8_t Sand_TargetIsEmpty(coord target_xy, uint8_t nowLEDNum, uint8_t direction, uint8_t* now_screen, uint8_t* next_screen) {
    uint8_t upLED = Sand_GetUpLed(direction);
    if (Sand_IsDownVertex(target_xy, direction) && nowLEDNum == upLED) {
        if (target_xy.x >= LED_WIDTH && target_xy.y >= LED_WIDTH) {
            target_xy.x = 0;
            target_xy.y = 0;
        }
        else if (target_xy.x < 0 && target_xy.y < 0) {
            target_xy.x = LED_WIDTH - 1;
            target_xy.y = LED_WIDTH - 1;
        }
        else {

        }

        //printf("targetX:%d\ttargetY:%d\r\n", target_xy.x, target_xy.y);
        uint8_t targetEmpty = Sand_TargetIsEmpty(target_xy, 1 - nowLEDNum, direction, next_screen, now_screen);
        if (targetEmpty == FULL) {
            return FULL;
        }
        else {
            return EMPTY;
        }
    }
    else if (Sand_IsBorder(target_xy.x) == OUT || Sand_IsBorder(target_xy.y) == OUT) {
        return FULL;
    }
    else {
        for (uint8_t i = 0;i < LED_WIDTH;i++) {
            for (uint8_t j = 0;j < LED_WIDTH;j++) {
                if (now_screen[target_xy.x * LED_WIDTH + target_xy.y] == 1) {
                    //uint8_t index=target_xy.x * LED_WIDTH + target_xy.y;
                    //printf("index:%d\r\n",index);
                    return FULL;
                }
            }
        }
        return EMPTY;
    }
}

void Sand_MoveToTarget(coord now_xy, coord target_xy, uint8_t direction, uint8_t nowLEDNum, uint8_t* now_screen, uint8_t* next_screen) {
    //printf("targetX:%d\ttargetY:%d\r\n", target_xy.x, target_xy.y);
    uint8_t upLED = Sand_GetUpLed(direction);
    if (Sand_IsDownVertex(target_xy, direction) && nowLEDNum == upLED) {
        target_xy.x = (target_xy.x + LED_WIDTH) % LED_WIDTH;
        target_xy.y = (target_xy.y + LED_WIDTH) % LED_WIDTH;
        now_screen[now_xy.x * LED_WIDTH + now_xy.y] = 0;
        next_screen[target_xy.x * LED_WIDTH + target_xy.y] = 1;
    }
    else {
        now_screen[now_xy.x * LED_WIDTH + now_xy.y] = 0;
        now_screen[target_xy.x * LED_WIDTH + target_xy.y] = 1;
    }
}

void Sand_UpdateScreen(uint8_t* nowScreen, uint8_t* nextScreen, uint8_t nowLEDNum, uint8_t sandNum, uint8_t gDirection) {
    uint8_t randNum = rand() % 2;
    for (uint8_t i = 0;i < LED_WIDTH * LED_WIDTH;i++) {
        coord now_xy = Sand_GetLoopCoord(i, gDirection, randNum);
        if (nowScreen[now_xy.x * LED_WIDTH + now_xy.y] == 1) {
            coord target_xy[3];
            Sand_GetTarget(now_xy, target_xy, gDirection);
            uint8_t midEmpty = Sand_TargetIsEmpty(target_xy[MID], nowLEDNum, gDirection, nowScreen, nextScreen);
            uint8_t leftEmpty = Sand_TargetIsEmpty(target_xy[LEFT], nowLEDNum, gDirection, nowScreen, nextScreen);
            uint8_t rightEmpty = Sand_TargetIsEmpty(target_xy[RIGHT], nowLEDNum, gDirection, nowScreen, nextScreen);
            if (midEmpty == EMPTY) {
                Sand_MoveToTarget(now_xy, target_xy[MID], gDirection, nowLEDNum, nowScreen, nextScreen);
            }
            else if ((leftEmpty == EMPTY) && (rightEmpty == FULL)) {
                Sand_MoveToTarget(now_xy, target_xy[LEFT], gDirection, nowLEDNum, nowScreen, nextScreen);
            }
            else if ((leftEmpty == FULL) && (rightEmpty == EMPTY)) {
                Sand_MoveToTarget(now_xy, target_xy[RIGHT], gDirection, nowLEDNum, nowScreen, nextScreen);
            }
            else if ((leftEmpty == EMPTY) && (rightEmpty == EMPTY)) {
                if (randNum == 0) {
                    Sand_MoveToTarget(now_xy, target_xy[LEFT], gDirection, nowLEDNum, nowScreen, nextScreen);
                }
                else {
                    Sand_MoveToTarget(now_xy, target_xy[RIGHT], gDirection, nowLEDNum, nowScreen, nextScreen);
                }
            }
            else {
                //break;
            }
        }
        else {
            continue;
        }
    }
}