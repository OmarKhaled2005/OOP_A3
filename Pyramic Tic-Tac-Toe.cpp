#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "Pyramic Tic-Tac-Toe.h"
using namespace std;

// Set the board
X_O_Board::X_O_Board () {
   n_rows = 3 ;n_cols = 5;
   board = new char*[n_rows];
   for (int i = 0; i < n_rows; i++) {
      board [i] = new char[i*2+1];
      for (int j = 0; j < i*2+1; j++)
         board[i][j] = 0;
   }
}

bool X_O_Board::update_board (int x, int y, char mark){
   // Only update if move is valid
   if (!(x < 0 || x > 2 || y < 0 || y > 4) && (board[x][y] == 0) &&(n_moves!=9)) {
      board[x][y] = toupper(mark);
      n_moves++;
      return true;
   }
   else
      return false;
}

// Display the board and the pieces on it
void X_O_Board::display_board() {
   for (int i=0;i<n_rows;i++) {
       if(i==0)cout << "\n      | ";
       else if(i==1) cout<<"\n    |";
       else if(i==2)cout<<"\n|";
       for (int j=0;j<i*2+1;j++) {
         cout << setw(2) << board [i][j] << " |";
      }
      cout << "\n-----------------------------";
   }
   cout << endl;
}




bool X_O_Board::is_winner() {
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] &&board[1][1]!=0)return true;
    else if(board[0][0]==board[1][0] &&board[1][0]==board[2][0] &&board[1][0]!=0) return true;
    else if(board[0][0]==board[1][2]&&board[1][2]==board[2][4] &&board[1][2]!=0)return true;
    else if(board[1][0]==board[1][1]&&board[1][1]==board[1][2] &&board[1][1]!=0)return true;
    else{
        for (int i = 0; i < 3; i++)
        {
            if (board[2][0 + i] == board[2][1 + i] && board[2][2 + i] == board[2][1 + i] && board[2][0 + i]!=0)
            {
                return true;
            }
        }
    }
    return false;
}

bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over () {
    return n_moves >= 9;
}

X_O_Board::~X_O_Board()
{
    delete[] board;
}

Player::Player(char symbol) :symbol(symbol) {
    name="computer";
}

Player::Player (int order, char symbol) :symbol(symbol){
     cout << "Welcome player " << order << endl;
     cout << "Please enter your name: ";
     cin >> name;
}

void Player::get_move (int& x, int& y) {
    cout << "\nPlease enter your move x and y";
    cin >> x >> y;
}

string Player::To_string()
{
    return (name + " symbol is " + symbol);
}

char Player::get_symbol()
{
    return symbol;
}

RandomPlayer::RandomPlayer (char symbol, int dimension):Player(symbol),dimension(dimension)
{
    name = "Random Computer Player";
    cout << "My names is " << name << endl;
}
// Generate a random move
void RandomPlayer::get_move (int& x, int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
}
GameManager::GameManager(Board* bPtr, Player* playerPtr[2] ) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
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
GameManager::~GameManager()
{
    delete boardPtr;
}



