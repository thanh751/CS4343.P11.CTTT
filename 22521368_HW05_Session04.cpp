//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 04 - Homework 05
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'X';
const char AI_PLAYER = 'O';
const char EMPTY = ' ';

struct Move {
    int row, col;
};

class TicTacToe {
private:
    vector<vector<char>> board;
public:
    TicTacToe() : board(3, vector<char>(3, EMPTY)) {}

    void displayBoard() {
        cout << "Current board:\n";
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                cout << board[i][j];
                if(j<2) cout << " | ";
            }
            cout << "\n";
            if(i<2) cout << "--+---+--\n";
        }
    }

    bool isMovesLeft() {
        for(auto &row : board)
            for(auto cell : row)
                if(cell == EMPTY)
                    return true;
        return false;
    }

    char checkWinner() {
        // Rows
        for(int i=0;i<3;i++) {
            if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!=EMPTY)
                return board[i][0];
        }
        // Columns
        for(int j=0;j<3;j++) {
            if(board[0][j]==board[1][j] && board[1][j]==board[2][j] && board[0][j]!=EMPTY)
                return board[0][j];
        }
        // Diagonals
        if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=EMPTY)
            return board[0][0];
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=EMPTY)
            return board[0][2];
        return EMPTY;
    }

    int minimax(int depth, bool isMax) {
        char winner = checkWinner();
        if(winner == AI_PLAYER)
            return 10 - depth;
        if(winner == HUMAN)
            return depth - 10;
        if(!isMovesLeft())
            return 0;

        if(isMax) {
            int best = numeric_limits<int>::min();
            for(int i=0;i<3;i++) {
                for(int j=0;j<3;j++) {
                    if(board[i][j]==EMPTY) {
                        board[i][j] = AI_PLAYER;
                        best = max(best, minimax(depth+1, false));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for(int i=0;i<3;i++) {
                for(int j=0;j<3;j++) {
                    if(board[i][j]==EMPTY) {
                        board[i][j] = HUMAN;
                        best = min(best, minimax(depth+1, true));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }
    }

    Move findBestMove() {
        int bestVal = numeric_limits<int>::min();
        Move bestMove = { -1, -1 };
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==EMPTY) {
                    board[i][j] = AI_PLAYER;
                    int moveVal = minimax(0, false);
                    board[i][j] = EMPTY;
                    if(moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void makeMove(int row, int col, char player) {
        if(board[row][col] == EMPTY)
            board[row][col] = player;
    }

    void playGame() {
        int row, col;
        while(isMovesLeft()) {
            displayBoard();
            cout << "Your move (row and column): ";
            cin >> row >> col;
            if(row <0 || row >2 || col <0 || col >2 || board[row][col]!=EMPTY){
                cout << "Invalid move. Try again.\n";
                continue;
            }
            makeMove(row, col, HUMAN);
            if(checkWinner() == HUMAN) {
                displayBoard();
                cout << "You win!\n";
                return;
            }
            if(!isMovesLeft()){
                displayBoard();
                cout << "It's a draw!\n";
                return;
            }
            cout << "AI is making a move...\n";
            Move aiMove = findBestMove();
            makeMove(aiMove.row, aiMove.col, AI_PLAYER);
            if(checkWinner() == AI_PLAYER){
                displayBoard();
                cout << "AI wins!\n";
                return;
            }
        }
        displayBoard();
        cout << "It's a draw!\n";
    }
};

int main(){
    TicTacToe game;
    game.playGame();
    return 0;
}