#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define BOARD_SIZE 15
#define WIN_COUNT 5

char board[BOARD_SIZE][BOARD_SIZE];
char EMPTY = ' ';
char PLAYER = 'X';    // AI
char OPPONENT = 'O';  // User

void initialize_board() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = EMPTY;
}

void print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool check_direction(int row, int col, int delta_row, int delta_col, char player) {
    int count = 0;
    for (int i = 0; i < WIN_COUNT; i++) {
        int r = row + i * delta_row;
        int c = col + i * delta_col;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count == WIN_COUNT;
}

bool is_winning_move(char player) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (check_direction(row, col, 1, 0, player) ||  // Horizontal
                check_direction(row, col, 0, 1, player) ||  // Vertical
                check_direction(row, col, 1, 1, player) ||  // Diagonal \
                check_direction(row, col, 1, -1, player))   // Diagonal /
                return true;
        }
    }
    return false;
}

int count_in_a_row(int row, int col, int delta_row, int delta_col, char player) {
    int count = 0;
    for (int i = 0; i < 4; i++) { // Check for patterns of 4
        int r = row + i * delta_row;
        int c = col + i * delta_col;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

int evaluate_board() {
    int score = 0;
    // Improved evaluation considering open sequences
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == PLAYER) {
                if (count_in_a_row(row, col, 1, 0, PLAYER) == 4) score += 100;  // Horizontal 4 in a row
                if (count_in_a_row(row, col, 0, 1, PLAYER) == 4) score += 100;  // Vertical 4 in a row
                if (count_in_a_row(row, col, 1, 1, PLAYER) == 4) score += 100;  // Diagonal \ 4 in a row
                if (count_in_a_row(row, col, 1, -1, PLAYER) == 4) score += 100; // Diagonal / 4 in a row
                if (count_in_a_row(row, col, 1, 0, PLAYER) == 3) score += 10;   // Horizontal 3 in a row
                if (count_in_a_row(row, col, 0, 1, PLAYER) == 3) score += 10;   // Vertical 3 in a row
                if (count_in_a_row(row, col, 1, 1, PLAYER) == 3) score += 10;   // Diagonal \ 3 in a row
                if (count_in_a_row(row, col, 1, -1, PLAYER) == 3) score += 10;  // Diagonal / 3 in a row
            } else if (board[row][col] == OPPONENT) {
                if (count_in_a_row(row, col, 1, 0, OPPONENT) == 4) score -= 100;
                if (count_in_a_row(row, col, 0, 1, OPPONENT) == 4) score -= 100;
                if (count_in_a_row(row, col, 1, 1, OPPONENT) == 4) score -= 100;
                if (count_in_a_row(row, col, 1, -1, OPPONENT) == 4) score -= 100;
                if (count_in_a_row(row, col, 1, 0, OPPONENT) == 3) score -= 10;
                if (count_in_a_row(row, col, 0, 1, OPPONENT) == 3) score -= 10;
                if (count_in_a_row(row, col, 1, 1, OPPONENT) == 3) score -= 10;
                if (count_in_a_row(row, col, 1, -1, OPPONENT) == 3) score -= 10;
            }
        }
    }
    return score;
}

int minimax(int depth, int alpha, int beta, bool maximizing_player) {
    if (is_winning_move(PLAYER)) return 1000 - depth;
    if (is_winning_move(OPPONENT)) return depth - 1000;
    if (depth == 0) return evaluate_board();

    if (maximizing_player) {
        int max_eval = INT_MIN;
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = PLAYER;
                    int eval = minimax(depth - 1, alpha, beta, false);
                    board[row][col] = EMPTY;
                    max_eval = (eval > max_eval) ? eval : max_eval;
                    alpha = (alpha > eval) ? alpha : eval;
                    if (beta <= alpha) return max_eval;
                }
            }
        }
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = OPPONENT;
                    int eval = minimax(depth - 1, alpha, beta, true);
                    board[row][col] = EMPTY;
                    min_eval = (eval < min_eval) ? eval : min_eval;
                    beta = (beta < eval) ? beta : eval;
                    if (beta <= alpha) return min_eval;
                }
            }
        }
        return min_eval;
    }
}

void best_move(int depth) {
    int best_val = INT_MIN;
    int best_row = -1, best_col = -1;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == EMPTY) {
                board[row][col] = PLAYER;
                int move_val = minimax(depth - 1, INT_MIN, INT_MAX, false);
                board[row][col] = EMPTY;
                if (move_val > best_val) {
                    best_val = move_val;
                    best_row = row;
                    best_col = col;
                }
            }
        }
    }

    if (best_row != -1 && best_col != -1) {
        board[best_row][best_col] = PLAYER;
    }
}

void user_move() {
    int row, col;
    printf("Enter your move (row and column): ");
    scanf("%d %d", &row, &col);
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY) {
        board[row][col] = OPPONENT;
    } else {
        printf("Invalid move. Try again.\n");
        user_move();
    }
}

int main() {
    initialize_board();
    int depth = 3;

    while (true) {
        print_board();
        best_move(depth);
        if (is_winning_move(PLAYER)) {
            print_board();
            printf("AI wins!\n");
            break;
        }
        
        print_board();
        user_move();
        if (is_winning_move(OPPONENT)) {
            print_board();
            printf("You win!\n");
            break;
        }
        
        // Dynamic depth adjustment
        depth = (depth < 5) ? depth + 1 : depth; // Increase search depth as the game progresses
    }

    return 0;
}
