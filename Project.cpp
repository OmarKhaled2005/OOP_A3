#include <iostream>
#include <cstdlib>
#include "Four-in-a-row.cpp"
#include "Pyramic Tic-Tac-Toe.cpp"
#include "5 x 5 Tic Tac Toe .cpp"

// Include the necessary classes and implementations

using namespace std;

int main() {
    int gameChoice;

    cout << "Welcome to the Game Menu\n";
    cout << "Please,Choose a game to play:\n";
    cout << "1. Tic-Tac-Toe\n";
    cout << "2. Four-in-a-row.cpp\n";
    cout << "3. 5x5 Tic-Tac-Toe\n";
    cout << "Enter your choice (1, 2, or 3): ";
    cin >> gameChoice;

    switch (gameChoice) {
        case 1: {
            // Tic-Tac-Toe (PyramidX_O)
            int choice;
            Player* players[2];
            players[0] = new Player(1, 'x');

            cout << "Welcome to FCAI X-O Game. :)\n";
            cout << "Press 1 if you want to play with another player, press 2 if you want to play against the computer: ";
            cin >> choice;

            if (choice == 1) {
                players[1] = new Player(2, 'o');
                GameManager x_o_game(new PyramidX_O(), players);
                x_o_game.PyramidX_O_run();
            } else if (choice == 2) {
                players[1] = new RandomPlayer('o', 3);
                GameManager x_o_game(new PyramidX_O(), players);
                x_o_game.PyramidX_O_run();
            } else {
                cout << "Invalid choice. Exiting the game.\n";
            }

            // Cleanup dynamic memory
            delete players[0];
            delete players[1];
            break;
        }
        case 2: {
           
            ConnectFourGame connectFourGame;
            connectFourGame.playGame();
            break;
        }
        case 3:{
           
            int choice;
    Playerr* playerss[2];
    playerss[0] = new Playerr('X', 5);

    cout << "Welcome to 5x5 Tic-Tac-Toe!\n";
    cout << "Press 1 if you want to play with another player, press 2 if you want to play against the computer: ";
    cin >> choice;

    if (choice == 1) {
        playerss[1] = new Playerr('O', 5);
        GameManagerr ticTacToe(new X_O_Board(), playerss);
        ticTacToe.runPlayerVsPlayer();
    }
    else if (choice == 2) {
        playerss[1] = new RandomPlayerr('O', 5);
        GameManagerr ticTacToe(new X_O_Board(), playerss);
        ticTacToe.runPlayerVsRandom();
    }
    else {
        cout << "Invalid choice. Exiting the game.\n";
    }

    // Cleanup dynamic memory
    delete playerss[0];
    delete playerss[1];

    return 0;
        }
        default:
            cout << "Invalid choice. Exiting the game.\n";
    }

    system("pause");
    return 0;
}
