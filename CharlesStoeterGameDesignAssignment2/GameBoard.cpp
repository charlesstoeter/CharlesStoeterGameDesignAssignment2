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
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            revealed[i][j] = false;
        }
    }
}


void GameBoard::randomizeBoard() {
    std::vector<Shape> pairs;

    for (int i = 0; i < 12; ++i) {
        pairs.push_back(static_cast<Shape>(i % NUM_SHAPES)); // repeat shapes if NUM_SHAPES < 12
        pairs.push_back(static_cast<Shape>(i % NUM_SHAPES));
    }
    

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pairs.begin(), pairs.end(), g);

    if (pairs.size() != 25) {
        throw std::runtime_error("Pairs vector size must be 25!");
    }

    int idx = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 4 && j == 4) {
                board[i][j] = EMPTY; // explicitly mark bottom-right as empty
                continue;
            }
            board[i][j] = pairs[idx++];
        }
    }
}

Shape GameBoard::getShapeAt(int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
        return board[row][col];

    }
    return EMPTY;
}

bool GameBoard::isRevealed(int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
                return revealed[row][col];

    }
    return false;
}

void GameBoard::reveal(int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
        revealed[row][col] = true;

    }
}

void GameBoard::hide(int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
        revealed[row][col] = false;

    }
}

bool GameBoard::allMatched() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] != EMPTY && !revealed[i][j]) {
                return false;

            }
        }
            
    }
        

    return true;

}

// Increment the count of matched pairs
void GameBoard::incrementMatchCount() {
    matchedPairs++;
}

int GameBoard::getMatchedPairs() const {
    return matchedPairs;
}

int GameBoard::getRemainingPairs() const {
    return 12 - matchedPairs;
}

bool GameBoard::compare(int row1, int col1, int row2, int col2) {
    // Don't allow comparing the same cell
    if (row1 == row2 && col1 == col2) {
        return false;
    }

    // Return true if the shapes in the two different cells match
    Shape shape1 = getShapeAt(row1, col1);
    Shape shape2 = getShapeAt(row2, col2);

    return shape1 == shape2;
}

void GameBoard::resetGame() {
    resetBoard();
    randomizeBoard();
    matchedPairs = 0; // reset match count
}



