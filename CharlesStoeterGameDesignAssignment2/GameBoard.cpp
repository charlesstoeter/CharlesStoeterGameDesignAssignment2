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


void GameBoard::randomizeBoard() {
    std::vector<Shape> pairs;

    for (int i = 0; i < 12; ++i) {
        pairs.push_back(static_cast<Shape>(i % NUM_SHAPES)); // repeat shapes if NUM_SHAPES < 12
        pairs.push_back(static_cast<Shape>(i % NUM_SHAPES));
    }
    pairs.push_back(EMPTY); // One empty cell for status in bottom-right

    std::shuffle(pairs.begin(), pairs.end(), std::default_random_engine());

    int idx = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = pairs[idx++];
}

Shape GameBoard::getShapeAt(int row, int col) {
    return board[row][col];
}

bool GameBoard::isRevealed(int row, int col) {
    return revealed[row][col];
}

void GameBoard::reveal(int row, int col) {
    revealed[row][col] = true;
}

void GameBoard::hide(int row, int col) {
    revealed[row][col] = false;
}

