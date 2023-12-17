// FourInARowGame.hpp
#ifndef FOURINAROWGAME_HPP
#define FOURINAROWGAME_HPP

#include <iostream>
#include <random>

using namespace std;

class FourInARowGame {
private:
    char game_board[6][7];
    int col_limiter[7];
    int counter;
    char player;

    int randint(int min, int max);

    void displayBoard();

    bool WinnerCheck(int current_row, int current_column);

public:
    FourInARowGame();

    bool playGame();
};

// Class definition for XO game classes
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
class Board {
protected:
    int n_rows, n_cols;
    char** board;
    int n_moves = 0;

public:
    // Return true if the move is valid and put it on the board
    // within board boundaries in an empty cell
    // Return false otherwise
    virtual bool update_board(int x, int y, char symbol) = 0;
    // Returns true if there is any winner
    // either X or O
    // Written in a complex way. DO NOT DO LIKE THIS.
    virtual bool is_winner() = 0;
    // Return true if all moves are done and no winner
    virtual bool is_draw() = 0;
    // Display the board and the pieces on it
    virtual void display_board() = 0;
    // Return true if the game is over
    virtual bool game_is_over() = 0;
};

// This class represents a 3 x 3 board
// used in X_O game
class X_O_Board : public Board {
public:
    X_O_Board();
    bool update_board(int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
};

// This class represents a player who has
// a name and a symbol to put on the board
class Player {
protected:
    string name;
    char symbol;

public:

    Player(char symbol); // Needed for computer players
    Player(int order, char symbol);
    // Get the desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);
    // Give player info as a string
    string to_string();
    // Get the symbol used by the player
    char get_symbol();
};


class RandomPlayer : public Player {
protected:
    int dimension;

public:
    // Take a symbol and pass it to the parent
    RandomPlayer(char symbol, int dimension);
    // Generate a random move
    void get_move(int& x, int& y);
};

class GameManager {
private:
    Board* boardPtr;
    Player* players[2];

public:
    GameManager(Board*, Player* playerPtr[2]);
    void run();

};

#endif // FOURINAROWGAME_HPP
