#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
using namespace std;

class Board
{
protected:
    int n_rows, n_cols;
    char **board;
    int n_moves = 0;

public:
    // Return true if move is valid and put it on board Return false otherwise
    virtual bool update_board(int x, int y, char symbol) = 0;

    // Returns true if there is any winner
    virtual bool is_winner() = 0;

    // Return true if all moves are done and no winner
    virtual bool is_draw() = 0;

    // Display the board and the pieces on it
    virtual void display_board() = 0;

    // Return true if game is over
    virtual bool game_is_over() = 0;
};

class PyramidX_O : public Board
{
public:
    PyramidX_O(){
        n_rows = 3 ;n_cols = 5;
        board = new char*[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board [i] = new char[i*2+1];
        for (int j = 0; j < i*2+1; j++)
            board[i][j] = 0;
         }
    }
    bool update_board (int x, int y, char mark){
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 4) && (board[x][y] == 0) &&(n_moves!=9)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
       return false;
    }
    void display_board() {
        for (int i=0;i<n_rows;i++) {
          if(i==0)cout << "\n               | ";
          else if(i==1) cout<<"\n       |";
          else if(i==2)cout<<"\n|";
        for (int j=0;j<i*2+1;j++) {
             cout << "(" << i << "," << j << ")";
             cout << setw(2) << board [i][j] << " |";
        }
      cout << "\n------------------------------------------------";
       }
      cout << endl;
    }


    bool is_winner() {
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1]!=0) return true;
    else if(board[0][0]==board[1][0] && board[1][0]==board[2][0] && board[1][0]!=0) return true;
    else if(board[0][0]==board[1][2] && board[1][2]==board[2][4] && board[1][2]!=0) return true;
    else if(board[1][0]==board[1][1] && board[1][1]==board[1][2] && board[1][1]!=0) return true;
    // else if(board[2][0]==board[2][1] && board[2][1]==board[2][2] && board[2][0]!=0) return true;
    // else if(board[2][1]==board[2][2] && board[2][2]==board[2][3] && board[2][1]!=0) return true;
    // else if(board[2][2]==board[2][3] && board[2][3]==board[2][4] && board[2][2]!=0) return true;
    else{
        for (int i = 0; i < 3; i++)
        {
            if (board[2][0 + i] == board[2][1 + i] && board[2][1 + i] == board[2][2 + i] && board[2][0 + i]!=0)
            {
                return true;
            }
        }
    }
         return false;
    }

       bool is_draw() {
         return (n_moves == 9 && !is_winner());
    }
       bool game_is_over () {
           return n_moves >= 9;
    }
    ~PyramidX_O(){
        delete[] board;
        }
};

class Player
{
protected:
    string name;
    char symbol;

public:
    // Give player a symbol to use in playing
    Player(char symbol) :symbol(symbol) {
    name="computer";
    } // Needed for computer players

    // give ID or order
    Player (int order, char symbol) :symbol(symbol){
     cout << "Welcome player " << order << endl;
     cout << "Please enter your name: ";
     cin >> name;
    }

    // Get desired move: x y 
    virtual void get_move (int& x, int& y) {
    cout << "\nPlease enter your move x and y";
    cin >> x >> y;
    }

    // Give player info as a string
    string To_string()
    {
    return (name + " symbol is " + symbol);
    }

    // Get symbol used by player
    char get_symbol()
    {
    return symbol;
    }
};


class RandomPlayer : public Player
{
protected:
    int dimension;

public:
    // Take a symbol and pass it to parent
    RandomPlayer (char symbol, int dimension):Player(symbol),dimension(dimension)
   {
    name = "Random Computer Player";
    cout << "My names is " << name << endl;
   }
   
    // Generate a random move
    void get_move (int& x, int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
   }
};

class GameManager
{
private:
    Board *boardPtr;
    Player *players[2];

public:
   GameManager(Board* bPtr, Player* playerPtr[2] ) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}
    void PyramidX_O_run() {
    int x, y;
    boardPtr->display_board();
    while (!boardPtr->game_is_over()) {
        for (int i:{0,1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board (x, y, players[i]->get_symbol())){
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()){
                cout  << players[i]->To_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()){
                cout << "Draw!\n";
                return;
            }
        }
    }
}
   ~GameManager(){
    delete boardPtr;
    }

};

// int main() {

//     int choice;
//     Player* players[2];
//     players[0] = new Player (1, 'x');

//     cout << "Welcome to FCAI X-O Game. :)\n";
//     cout << "Press 1 if you want to play with computer: ";
//     cin >> choice;
//     if (choice != 1)
//         players[1] = new Player (2, 'o');
//     else
//         //Player pointer points to child
//         players[1] = new RandomPlayer ('o', 3);

//     GameManager x_o_game (new PyramidX_O(), players);
//     x_o_game.PyramidX_O_run();
//     system ("pause");
// }


