#include "GameBoard.h"
#include <algorithm>
#include <random>
#include <vector>

//constructor
GameBoard::GameBoard() { 
    resetBoard();
    randomizeBoard();
}


void GameBoard::resetBoard() {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            revealed[i][j] = false;
}


