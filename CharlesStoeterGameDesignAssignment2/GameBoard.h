// GameBoard.h
#pragma once

enum Shape {
    EMPTY = -1,
    OCTAGON, TRIANGLE, DIAMOND, RECTANGLE,
    OVAL, CIRCLE,
    NUM_SHAPES // should equal 6
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

private:
    Shape board[5][5];           // stores shapes
    bool revealed[5][5];         // stores whether the shape is shown or not
};
