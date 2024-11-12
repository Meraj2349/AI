#include <bits/stdc++.h>

using namespace std;

const int SIZE = 3;
char human = 'X', ai = 'O';

// Function to display the board
void displayBoard(const vector<vector<char>>& board) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            cout << board[row][col];
            if (col < SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (row < SIZE - 1) cout << "---------\n";
    }
}

// Check if there are moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (int row = 0; row < SIZE; ++row)
        for (int col = 0; col < SIZE; ++col)
            if (board[row][col] == '_')
                return true;
    return false;
}

// Evaluate the board for a winning condition
int evaluate(const vector<vector<char>>& board) {
    // Check rows and columns for a win
    for (int row = 0; row < SIZE; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == ai) return +10;
            else if (board[row][0] == human) return -10;
        }
    }
    for (int col = 0; col < SIZE; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == ai) return +10;
            else if (board[0][col] == human) return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == ai) return +10;
        else if (board[0][0] == human) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == ai) return +10;
        else if (board[0][2] == human) return -10;
    }

    return 0;
}

// Minimax algorithm
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    // If AI or human wins
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;

    // If no moves left, it's a tie
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (board[row][col] == '_') {
                    board[row][col] = ai;
                    best = max(best, minimax(board, depth + 1, false));
                    board[row][col] = '_';
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (board[row][col] == '_') {
                    board[row][col] = human;
                    best = min(best, minimax(board, depth + 1, true));
                    board[row][col] = '_';
                }
            }
        }
        return best;
    }
}

// Find the best move for the AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == '_') {
                board[row][col] = ai;
                int moveVal = minimax(board, 0, false);
                board[row][col] = '_';
                if (moveVal > bestVal) {
                    bestMove = {row, col};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, '_'));
    int row, col;
    bool humanTurn = true;

    while (isMovesLeft(board) && evaluate(board) == 0) {
        displayBoard(board);
        if (humanTurn) {
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == '_') {
                board[row][col] = human;
                humanTurn = false;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        } else {
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = ai;
            humanTurn = true;
            cout << "AI played at (" << bestMove.first << ", " << bestMove.second << ")\n";
        }
    }
    displayBoard(board);

    int score = evaluate(board);
    if (score == 10) cout << "AI wins!\n";
    else if (score == -10) cout << "You win!\n";
    else cout << "It's a tie!\n";
}

int main() {
    playGame();
    return 0;
}
