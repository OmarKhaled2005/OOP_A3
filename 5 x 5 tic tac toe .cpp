#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

// Player Class
class Player {
public:
    char symbol;
    string name;
    int dimension;

public:
    // Constructor
    Player(char symbol, int dimension) : symbol(symbol), dimension(dimension) {
        cout << "Please enter your name: ";
        cin >> name;
    }

    // Get desired move: x y (each between 0 and dimension-1)
    virtual void get_move(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to " << dimension - 1 << ") separated by spaces: ";
        cin >> x >> y;
    }

    // Display player info as a string
    string to_string() {
        return "Player: " + name;
    }

    // Get symbol used by player
    char get_symbol() {
        return symbol;
    }
};

// RandomPlayer Class
class RandomPlayer : public Player {
public:
    // Constructor
    RandomPlayer(char symbol, int dimension) : Player(symbol, dimension) {
        this->name = "Random Computer Player";
        cout << "My name is " << name << endl;
    }

    // Generate a random move
    void get_move(int& x, int& y) {
        x = rand() % dimension; // Generate a random move between 0 and dimension-1
        y = rand() % dimension;
    }
};

// X_O_Board Class
class X_O_Board {
public:
    int n_rows;
    int n_cols;
    char** board;
    int n_moves;

public:
    // Constructor
    X_O_Board() {
        n_rows = n_cols = 5;
        board = new char* [n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            for (int j = 0; j < n_cols; j++)
                board[i][j] = '-';
        }
        n_moves = 0;
    }

    // Return true if move is valid and put it on the board
    bool update_board(int x, int y, char mark) {
        if (!(x < 0 || x >= 5 || y < 0 || y >= 5) && (board[x][y] == '-')) {
            board[x][y] = mark;
            n_moves++;
            return true;
        }
        else {
            return false;
        }
    }

    // Display the board and the pieces on it
    void display_board() {
        for (int i = 0; i < 5; i++) {
            cout << "\n| ";
            for (int j = 0; j < 5; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    // Returns true if there is any winner
    bool is_winner(Player* player) {
        char symbol = player->get_symbol();

        // Check Horizontal and Vertical Sequences
        for (int i = 0; i < n_rows; ++i) {
            int horizontal_count = 0;
            int vertical_count = 0;

            for (int j = 0; j < n_cols; ++j) {
                // Check Horizontal Sequence
                if (board[i][j] == symbol)
                    horizontal_count++;
                else
                    horizontal_count = 0;

                // Check Vertical Sequence
                if (board[j][i] == symbol)
                    vertical_count++;
                else
                    vertical_count = 0;

                // Check if there's a winner
                if (horizontal_count >= 3 || vertical_count >= 3)
                    return true;
            }
        }

        // Check Diagonal Sequences
        for (int i = 0; i <= n_rows - 3; ++i) {
            for (int j = 0; j <= n_cols - 3; ++j) {
                // Check Diagonal from top-left to bottom-right
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                    return true;

                // Check Diagonal from top-right to bottom-left
                if (board[i][j + 2] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j] == symbol)
                    return true;
            }
        }

        return false;
    }

    // Return true if 24 moves are done and no winner
    bool is_game_over() {
        return n_moves == 24;
    }
};

// GameManager Class
class GameManager {
public:
    X_O_Board* boardPtr;
    Player* players[2];

public:
    // Constructor
    GameManager(X_O_Board* bPtr, Player* playerPtr[2]) {
        boardPtr = bPtr;
        players[0] = playerPtr[0];
        players[1] = playerPtr[1];
    }

    // Player 1 plays against Player 2
    void runPlayerVsPlayer() {
        int x, y;

        boardPtr->display_board();

        while (!boardPtr->is_game_over()) {
            for (int i : {0, 1}) {
                players[i]->get_move(x, y);
                while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                    players[i]->get_move(x, y);
                }
                boardPtr->display_board();
                if (boardPtr->is_winner(players[i])) {
                    cout << players[i]->to_string() << " wins\n";
                    return;
                }
            }
        }

        cout << "It's a draw!\n";
    }


    
        // Player 1 plays against RandomPlayer
        void runPlayerVsRandom() {
        int x, y;

        boardPtr->display_board();

        while (!boardPtr->is_game_over()) {
            for (int i : {0, 1}) {
                players[i]->get_move(x, y);
                while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                    players[i]->get_move(x, y);
                }
                boardPtr->display_board();
                if (boardPtr->is_winner(players[i])) {
                    cout << players[i]->to_string() << " wins\n";
                    return;
                }
            }
        }

        cout << "It's a draw!\n";
    }
};

int main() {
    int choice;
    Player* players[2];
    players[0] = new Player('X', 5);

    cout << "Welcome to 5x5 Tic-Tac-Toe!\n";
    cout << "Press 1 if you want to play with another player, press 2 if you want to play against the computer: ";
    cin >> choice;

    if (choice == 1) {
        players[1] = new Player('O', 5);
        GameManager ticTacToe(new X_O_Board(), players);
        ticTacToe.runPlayerVsPlayer();
    }
    else if (choice == 2) {
        players[1] = new RandomPlayer('O', 5);
        GameManager ticTacToe(new X_O_Board(), players);
        ticTacToe.runPlayerVsRandom();
    }
    else {
        cout << "Invalid choice. Exiting the game.\n";
    }

    // Cleanup dynamic memory
    delete players[0];
    delete players[1];

    return 0;
}
