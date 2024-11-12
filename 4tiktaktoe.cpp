#include <bits/stdc++.h>
using namespace std;

const int SIZE = 4;
const char EMPTY = '_';
const char PLAYER = 'X';
const char AI = 'O';
const int MAX_DEPTH = 6; // Limit search depth

// Quick evaluation function
int evaluatePosition(vector<vector<char>>& board) {
    int score = 0;
    
    // Evaluate rows and columns
    for(int i = 0; i < SIZE; i++) {
        int rowX = 0, rowO = 0, colX = 0, colO = 0;
        for(int j = 0; j < SIZE; j++) {
            // Check row
            if(board[i][j] == PLAYER) rowX++;
            else if(board[i][j] == AI) rowO++;
            
            // Check column
            if(board[j][i] == PLAYER) colX++;
            else if(board[j][i] == AI) colO++;
        }
        // Score based on piece count
        if(rowO == 4) return 1000;
        if(rowX == 4) return -1000;
        if(colO == 4) return 1000;
        if(colX == 4) return -1000;
        
        // Partial scores
        if(rowO == 3 && rowX == 0) score += 5;
        if(rowX == 3 && rowO == 0) score -= 5;
        if(colO == 3 && colX == 0) score += 5;
        if(colX == 3 && colO == 0) score -= 5;
    }
    
    // Check diagonals
    int diagX1 = 0, diagO1 = 0, diagX2 = 0, diagO2 = 0;
    for(int i = 0; i < SIZE; i++) {
        if(board[i][i] == PLAYER) diagX1++;
        else if(board[i][i] == AI) diagO1++;
        
        if(board[i][SIZE-1-i] == PLAYER) diagX2++;
        else if(board[i][SIZE-1-i] == AI) diagO2++;
    }
    
    if(diagO1 == 4 || diagO2 == 4) return 1000;
    if(diagX1 == 4 || diagX2 == 4) return -1000;
    
    if(diagO1 == 3 && diagX1 == 0) score += 5;
    if(diagX1 == 3 && diagO1 == 0) score -= 5;
    if(diagO2 == 3 && diagX2 == 0) score += 5;
    if(diagX2 == 3 && diagO2 == 0) score -= 5;
    
    return score;
}

// Optimized Alpha-Beta pruning
int alphaBeta(vector<vector<char>>& board, int depth, int alpha, int beta, bool isMax) {
    int score = evaluatePosition(board);
    
    // Return if terminal node or max depth reached
    if(abs(score) >= 1000 || depth >= MAX_DEPTH)
        return score;
        
    bool isEmpty = false;
    for(int i = 0; i < SIZE && !isEmpty; i++)
        for(int j = 0; j < SIZE && !isEmpty; j++)
            if(board[i][j] == EMPTY)
                isEmpty = true;
                
    if(!isEmpty) return 0;

    if(isMax) {
        int best = INT_MIN;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, alphaBeta(board, depth + 1, alpha, beta, false));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if(beta <= alpha)
                        return best;  // Beta cut-off
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, alphaBeta(board, depth + 1, alpha, beta, true));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if(beta <= alpha)
                        return best;  // Alpha cut-off
                }
            }
        }
        return best;
    }
}

// Find best move for AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = alphaBeta(board, 0, INT_MIN, INT_MAX, false);
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

void displayBoard(vector<vector<char>>& board) {
    cout << "\n";
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isWinner(vector<vector<char>>& board, char player) {
    // Check rows and columns
    for(int i = 0; i < SIZE; i++) {
        bool rowWin = true, colWin = true;
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] != player) rowWin = false;
            if(board[j][i] != player) colWin = false;
        }
        if(rowWin || colWin) return true;
    }
    
    // Check diagonals
    bool diag1 = true, diag2 = true;
    for(int i = 0; i < SIZE; i++) {
        if(board[i][i] != player) diag1 = false;
        if(board[i][SIZE-1-i] != player) diag2 = false;
    }
    return diag1 || diag2;
}

int main() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, EMPTY));
    
    cout << "4x4 Tic Tac Toe\n";
    cout << "You are X, AI is O\n";
    cout << "Enter row (0-3) and column (0-3) separated by space\n";

    int moves = 0;
    while(moves < SIZE * SIZE) {
        displayBoard(board);
        
        // Player's turn
        int row, col;
        do {
            cout << "Your move: ";
            cin >> row >> col;
        } while(row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != EMPTY);
        
        board[row][col] = PLAYER;
        moves++;
        
        if(isWinner(board, PLAYER)) {
            displayBoard(board);
            cout << "You win!\n";
            return 0;
        }
        
        if(moves == SIZE * SIZE) break;

        // AI's turn
        cout << "AI is thinking...\n";
        auto [aiRow, aiCol] = findBestMove(board);
        board[aiRow][aiCol] = AI;
        moves++;
        cout << "AI placed O at position: " << aiRow << " " << aiCol << "\n";
        
        if(isWinner(board, AI)) {
            displayBoard(board);
            cout << "AI wins!\n";
            return 0;
        }
    }

    displayBoard(board);
    cout << "It's a tie!\n";
    return 0;
}