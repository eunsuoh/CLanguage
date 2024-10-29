#include <stdio.h>
#include <stdbool.h>

#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY ' '

char board[3][3] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};

void print_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool is_winner(char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool is_full() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

int minimax(int depth, char player, int alpha, int beta) {
    char opponent = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;

    if (is_winner(PLAYER_X)) return 10 - depth; // AI wins
    if (is_winner(PLAYER_O)) return depth - 10; // Opponent wins
    if (is_full()) return 0; // Tie

    if (player == PLAYER_X) { // AI's turn
        int max_eval = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int eval = minimax(depth + 1, PLAYER_O, alpha, beta);
                    board[i][j] = EMPTY;
                    max_eval = (eval > max_eval) ? eval : max_eval;
                    alpha = (alpha > eval) ? alpha : eval;
                    if (beta <= alpha) break; // Beta cutoff
                }
            }
        }
        return max_eval;
    } else { // Opponent's turn
        int min_eval = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int eval = minimax(depth + 1, PLAYER_X, alpha, beta);
                    board[i][j] = EMPTY;
                    min_eval = (eval < min_eval) ? eval : min_eval;
                    beta = (beta < eval) ? beta : eval;
                    if (beta <= alpha) break; // Alpha cutoff
                }
            }
        }
        return min_eval;
    }
}

void best_move() {
    int best_val = -1000;
    int best_row = -1, best_col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X; // AI move
                int move_val = minimax(0, PLAYER_O, -1000, 1000);
                board[i][j] = EMPTY;
                if (move_val > best_val) {
                    best_row = i;
                    best_col = j;
                    best_val = move_val;
                }
            }
        }
    }
    board[best_row][best_col] = PLAYER_X;
}

int main() {
    printf("Tic-Tac-Toe with Minimax and Alpha-Beta Pruning\n");
    while (true) {
        print_board();
        if (is_winner(PLAYER_O)) {
            printf("Player O wins!\n");
            break;
        }
        if (is_full()) {
            printf("It's a tie!\n");
            break;
        }

        // Player O's turn
        int row, col;
        printf("Player O, enter your move (row and column): ");
        scanf("%d %d", &row, &col);
        if (board[row][col] == EMPTY) {
            board[row][col] = PLAYER_O;
        } else {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // AI's turn
        best_move();
        if (is_winner(PLAYER_X)) {
            print_board();
            printf("Player X wins!\n");
            break;
        }
    }
    return 0;
}
