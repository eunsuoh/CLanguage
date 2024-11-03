#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

// 새 노드를 생성
Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;  // 새 노드는 항상 빨간색으로 삽입
    node->left = node->right = node->parent = NULL;
    return node;
}

// 좌회전
void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// 우회전
void rotateRight(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// 레드-블랙 트리 삽입 후 균형 조정
void fixViolation(Node **root, Node *z) {
    while (z != *root && z->parent->color == RED) {
        Node *parent = z->parent;
        Node *grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == parent->right) {
                    rotateLeft(root, parent);
                    z = parent;
                    parent = z->parent;
                }
                rotateRight(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                z = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == parent->left) {
                    rotateRight(root, parent);
                    z = parent;
                    parent = z->parent;
                }
                rotateLeft(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                z = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

// 레드-블랙 트리 삽입
void insert(Node **root, int data) {
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == NULL) *root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;

    fixViolation(root, z);
}

// 중위 순회로 트리 출력
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inorder(root->right);
}

int main() {
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);
    insert(&root, 5);

    printf("Inorder Traversal of Created Red-Black Tree:\n");
    inorder(root);
    return 0;
}
