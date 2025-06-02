#include "GameBoard.h"
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

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

    // Add 4 of each shape (6 * 4 = 24)
    for (int i = 0; i < NUM_SHAPES; ++i) {
        for (int j = 0; j < 4; ++j) {
            pairs.push_back(static_cast<Shape>(i));
        }
    }

    int counts[NUM_SHAPES] = { 0 };
    for (Shape s : pairs) {
        if (s >= 0 && s < NUM_SHAPES)
            counts[s]++;
    }

    std::cout << "Shape counts:\n";
    for (int i = 0; i < NUM_SHAPES; ++i) {
        std::cout << "Shape " << i << ": " << counts[i] << "\n";
    }

    // Shuffle the 24 shapes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pairs.begin(), pairs.end(), g);

    // Fill the board, leaving (4,4) as EMPTY
    int idx = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 4 && j == 4) {
                board[i][j] = EMPTY;
            }
            else {
                board[i][j] = pairs[idx++];
            }
        }
    }

    // Debug output AFTER board is filled
    std::cout << "Randomized Board:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << static_cast<int>(board[i][j]) << "\t";
        }
        std::cout << std::endl;
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



