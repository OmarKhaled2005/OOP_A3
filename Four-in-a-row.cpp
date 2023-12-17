#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "Four-in-a-row.hpp"
using namespace std;

// Implementation for FourinaRow clssa
fourinarow::fourinarow() {
    n_rows = 6;
    n_cols = 7;
    
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[i * 2 + 1];
        for (int j = 0; j < i * 2 + 1; j++)
            board[i][j] = 0;
    }
}

fourinarow::~fourinarow() {
    delete[] board;
}

bool fourinarow::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(y < 1 || y > 7) && (board[x][y] == 0) && (n_moves != 42) && current_row[y-1]<=7) {
        n_moves++;
        if(n_moves%2!=0){
            mark='X';
        }
        else{
            mark='O';
        }
        board[current_row[y-1]][y] = mark;
        current_column=y;
        current_row[y-1]++;
        return true;
    } else
        return false;
}

void fourinarow:: display_board() {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                cout << board[i][j] << "     ";
            }
            cout << endl << endl;
        }
    }

bool fourinarow::is_winner(int current_row, int current_column){
        int count = 0;
        const int rows = 6, cols = 7;
        char q = mark;
        int r = current_row;

        // Horizontal Winning Checker
        for (int j = current_column; j >= 0; --j) {
            if (board[current_row][j] == q) {
                count++;
                if (count >= 4) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
        for (int j = current_column; j < cols; ++j) {
            if (board[current_row][j] == q) {
                count++;
                if (count >= 4) {
                    return true;
                }
            }
        }

        // Vertical Winning Checker
        count = 0;
        for (int i = current_row; i < rows; ++i) {
            if (board[i][current_column] == q) {
                count++;
            }
            if (count >= 4) {
                return true;
            }
        }

        count = 0;
        r = current_row;

        // Diagonal Checker (Left to right and Right to left)
        for (int i = current_column + 1; i < 7; i++) {
            if (r <= 5 && i <= 6 && i >= 0) {
                if (board[r][i] == q) {
                    count++;
                }
                r++;
            }
            if (count >= 4) {
                return true;
            }
        }
        count = 0;
        r = current_row;
        for (int i = current_column + 1; i < 7; i++) {
            if (r >= 0 && i <= 6 && i >= 0) {
                if (board[r][i] == q) {
                    count++;
                }
                r--;
            }
            if (count >= 4) {
                return true;
            }
        }

        count = 0;
        r = current_row;

        for (int i = current_column; i >= 0; i--) {
            if (r <= 5 && r >= 0 && i <= 6 && i >= 0) {
                if (board[r][i] == mark) {
                    count++;
                }
                r--;
            }
            if (count >= 4) {
                return true;
            }
        }

        count = 0;
        r = current_row;

        for (int i = current_column; i >= 0; i--) {
            if (r <= 5 && r >= 0 && i <= 6 && i >= 0) {
                if (board[r][i] == mark) {
                    count++;
                }
                r++;
            }
            if (count >= 4) {
                return true;
            }
        }

        return false;
    }



bool fourinarow::is_draw(int current_row, int current_column) {
    return (n_moves == 42 && !is_winner(current_row, current_column));
}

bool fourinarow::game_is_over(int current_row, int current_column) {
    return n_moves >= 9;
}

// Implementation for Player class
Player::Player(char symbol) : symbol(symbol) {
    name = "computer";
}

Player::Player(int order, char symbol) : symbol(symbol) {

    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
}

void Player::get_move(int& x, int& y) {
    cout << "\nPlease enter your column y (1 to 7): ";
    cin >> y;
}

string Player::To_string() {
    return (name + " symbol is " + symbol);
}

char Player::get_symbol() {
    return symbol;
}

// Implementation for RandomPlayer class
RandomPlayer::RandomPlayer(char symbol, int dimension) : Player(symbol), dimension(dimension) {
    name = "Random Computer Player";
    cout << "My name is " << name << endl;
}

void RandomPlayer::get_move(int& x, int& y) {
    y = (int)(rand() / (RAND_MAX + 1.0) * dimension);
}

// Implementation for GameManager class
GameManager::GameManager(Board* bPtr, Player* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::fourinarow_run() {
    int x, y;
    boardPtr->display_board();
    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()) {
                cout << players[i]->To_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}
   GameManager::~GameManager(){
    delete boardPtr;
   }

int main() {
    int choice;
    Player* players[2];
    players[0] = new Player(1, 'x');

    cout << "Welcome to FCAI Four in a Row Game. :)\n";
    cout << "Press 1 if you want to play with another player, press 2 if you want to play against the computer: ";
    cin >> choice;

    fourinarow* board = new fourinarow(); // Create an instance of the fourinarow class

    if (choice == 1) {
        players[1] = new Player(2, 'o');
        GameManager* gameManager = new GameManager(board, players); // Pass the board and players
        gameManager->fourinarow_run();
    } else if (choice == 2) {
        players[1] = new RandomPlayer('o', 3);
        GameManager* gameManager = new GameManager(board, players); // Pass the board and players
        gameManager->fourinarow_run();
    } else {
        cout << "Invalid choice. Exiting the game.\n";
    }

    // Clean up memory
    delete players[0];
    delete players[1];
    delete board;

    return 0;
    //
}
