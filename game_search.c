#include <stdio.h>
#include <limits.h>

// Minimax function definition
int minimax(int depth, int nodeIndex, int isMaximizingPlayer, int alpha, int beta, int *leaf_values, int maxDepth) {
    // If we reach a leaf node or maximum depth, return the leaf value
    if (depth == maxDepth)
        return leaf_values[nodeIndex];
    
    if (isMaximizingPlayer) { // Max node
        int maxEval = INT_MIN;
        for (int i = 0; i < 2; i++) { // Loop over two child nodes
            int eval = minimax(depth + 1, nodeIndex * 2 + i, 0, alpha, beta, leaf_values, maxDepth);
            maxEval = eval > maxEval ? eval : maxEval;
            alpha = alpha > eval ? alpha : eval;
            if (beta <= alpha)
                break; // Alpha-beta pruning
        }
        return maxEval;
    } else { // Min node
        int minEval = INT_MAX;
        for (int i = 0; i < 2; i++) { // Loop over two child nodes
            int eval = minimax(depth + 1, nodeIndex * 2 + i, 1, alpha, beta, leaf_values, maxDepth);
            minEval = eval < minEval ? eval : minEval;
            beta = beta < eval ? beta : eval;
            if (beta <= alpha)
                break; // Alpha-beta pruning
        }
        return minEval;
    }
}

int main() {
    int maxDepth = 3; // Maximum depth of the game tree
    int numLeaves = 1 << maxDepth; // Calculate the number of leaf nodes as 2^maxDepth
    int leaf_values[numLeaves];

    // Prompt user to input values for each leaf node
    printf("Enter the values for the leaf nodes (%d total):\n", numLeaves);
    for (int i = 0; i < numLeaves; i++) {
        printf("Leaf node %d: ", i + 1);
        scanf("%d", &leaf_values[i]);
    }

    int alpha = INT_MIN, beta = INT_MAX;
    int optimalValue = minimax(0, 0, 1, alpha, beta, leaf_values, maxDepth);
    printf("Optimal value: %d\n", optimalValue);
    return 0;
}
