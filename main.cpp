#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[9];

void resetBoard() {
    for (int i = 0; i < 9; i++) board[i] = '1' + i;
}

void drawBoard() {
    cout << "\n";
    for (int r = 0; r < 3; r++) {
        cout << " " << board[r*3] << " | " << board[r*3+1] << " | " << board[r*3+2] << "\n";
        if (r < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool checkWin(char p) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},   // rows
        {0,3,6},{1,4,7},{2,5,8},   // columns
        {0,4,8},{2,4,6}            // diagonals
    };
    for (int i = 0; i < 8; i++) {
        if (board[w[i][0]] == p && board[w[i][1]] == p && board[w[i][2]] == p)
            return true;
    }
    return false;
}

bool isFull() {
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X' && board[i] != 'O') return false;
    return true;
}

bool isFree(int i) {
    return board[i] != 'X' && board[i] != 'O';
}

// Try placing 'p' in each free square; return the square that wins, or -1
int findWinningMove(char p) {
    for (int i = 0; i < 9; i++) {
        if (isFree(i)) {
            char saved = board[i];
            board[i] = p;
            bool win = checkWin(p);
            board[i] = saved;
            if (win) return i;
        }
    }
    return -1;
}

void computerMove() {
    int move = findWinningMove('O');          // 1. win if possible
    if (move == -1) move = findWinningMove('X'); // 2. block the player
    if (move == -1 && isFree(4)) move = 4;       // 3. take center
    if (move == -1) {                            // 4. random free square
        do { move = rand() % 9; } while (!isFree(move));
    }
    board[move] = 'O';
    cout << "Computer chose square " << move + 1 << ".\n";
}

void playerMove() {
    int choice;
    while (true) {
        cout << "Your move (1-9): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        if (choice < 1 || choice > 9) {
            cout << "Pick a number between 1 and 9.\n";
        } else if (!isFree(choice - 1)) {
            cout << "That square is taken.\n";
        } else {
            board[choice - 1] = 'X';
            break;
        }
    }
}

int main() {
    srand((unsigned)time(0));
    char again;

    do {
        resetBoard();
        cout << "=== TIC-TAC-TOE ===\nYou are X, computer is O.\n";

        while (true) {
            drawBoard();
            playerMove();
            if (checkWin('X')) { drawBoard(); cout << "You win! 🎉\n"; break; }
            if (isFull())      { drawBoard(); cout << "It's a draw!\n"; break; }

            computerMove();
            if (checkWin('O')) { drawBoard(); cout << "Computer wins!\n"; break; }
            if (isFull())      { drawBoard(); cout << "It's a draw!\n"; break; }
        }

        cout << "Play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
