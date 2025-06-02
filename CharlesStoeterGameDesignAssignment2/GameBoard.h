// GameBoard.h
#pragma once

enum Shape {
    EMPTY = -1,
    OCTAGON, TRIANGLE, DIAMOND, RECTANGLE,
    OVAL, CIRCLE,
    NUM_SHAPES // should equal 6 / total number of actual shapes
};

class GameBoard {
public:
    GameBoard();
    void randomizeBoard();
    void resetBoard();
    Shape getShapeAt(int row, int col);
    bool isRevealed(int row, int col);
    void reveal(int row, int col);
    void hide(int row, int col);
    bool allMatched();
    void incrementMatchCount();
    int getMatchedPairs() const;
    int getRemainingPairs() const;
    bool compare(int row1, int col1, int row2, int col2);
    void resetGame();

private:
    Shape board[5][5];           
    bool revealed[5][5];         
	int matchedPairs = 0; // keeps track of matched pairs
    
};
