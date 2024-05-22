#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTreeNode {
    struct BinarySearchTreeNode *parent, *right, *left;
    int key;
} Node;

typedef struct BinarySearchTree {
    Node *root;
} Tree;

void tree_insert(Tree *T, int key) {

    // 노드 z는 인자로 전달 받은 키 값을 가지는, 트리에 삽입할 노드이다
    Node *z = (Node*)malloc(sizeof(Node));
    z->key = key;
    z->parent = NULL;
    z->left = NULL;
    z->right = NULL;

    Node *y = NULL;
    Node *x = T->root;

    // 노드 z를 삽입할 위치를 찾기 위해 키 값의 크기를 비교하며 트리를 타고 내려간다
    while (x != NULL) {
        y = x;
        if (key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    // x가 NULL을 만나면, 다시말해 leaf node에 도달하게 되면
    // 해당 노드를 노드 z의 부모로 지정한다
    z->parent = y;

    // 노드 z의 부모인 노드 y의 값과 노드 z의 값을 비교하여 알맞은 위치에 노드 z 삽입한다
    if (y == NULL) {
        T->root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }

}

// 재귀적으로 자기 자신을 호출하며 트리의 원소들을 작은 값부터 순차적으로 출력하는 함수이다
void inorder_tree_walk(Node *x) {

    if (x != NULL) {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }

}

// 특정 키 값을 가진 노드를 검색하는 재귀 함수이다
// x는 검색을 시작할 노드를 가르키는 포인터이다
Node* tree_search(Node *x, int key) {

    // 현재 노드 x가 NULL이거나 찾고자 하는 키 값과 같은 키 값을 가지면 검색을 종료한다
    if (x == NULL || key == x->key) {
        return x;
    }

    // 찾고자 하는 키 값이 현재 노드인 x의 키 값보다 작은 경우, 왼쪽 서브트리로 이동하여 검색을 계속한다
    if (key < x->key) {
        return tree_search(x->left, key);
    }
    
    // 찾고자 하는 키 값이 현재 노드인 x의 키 값보다 큰 경우, 오른쪽 서브트리로 이동하여 검색을 계속한다
    else {
        return tree_search(x->right, key);
    }

}

// 이진 탐색 트리에서 가장 작은 값을 가지는, 제일 왼쪽에 위치한 노드를 찾아서 반환하는 함수이다
Node* tree_minimum(Node *x) {

    while (x->left != NULL) {
        x = x->left;
    }

    return x;
}

// 이진 탐색 트리에서 가장 큰 값을 가지는, 제일 오른쪽에 위치한 노드를 찾아서 반환하는 함수이다
Node* tree_maximum(Node *x) {

    while (x->right != NULL) {
        x = x->right;
    }

    return x;
}


// 주어진 노드 x의 다음 노드를 탐색하는 함수이다
Node* tree_successor(Node *x) {

    // x의 오른쪽 서브트리가 비어있지 않은 경우,
    // tree_minimum 함수를 호툴하여 오른쪽 서브트리의 가장 작은 값을 반환한다
    if (x->right != NULL) {
        return tree_minimum(x->right);
    }

    // x의 오른쪽 서브트리가 비어있는 경우,
    // 왼쪽 위로 올라갈 수 있을 때까지 트리를 타고 올라가며 successor를 탐색한다
    Node *y = x->parent;

    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    
    return y;

}

// 주어진 노드 x의 직전 노드를 탐색하는 함수이다
Node* tree_predecessor(Node *x) {

    // x의 왼쪽 서브트리가 비어있지 않은 경우,
    // tree_maximum 함수를 호출하여 왼쪽 서브트리의 가장 큰 값을 반환한다
    if (x->left != NULL) {
        return tree_maximum(x->left);
    }

    // x의 왼쪽 서브트리가 비어있는 경우,
    // 오른쪽 위로 올라갈 수 있을 때까지 트리를 타고 올라가며 predecessor를 탐색한다
    Node *y = x->parent;

    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    
    return y;

}

// 이진 탐색 트리에서 노드 z를 삭제하는 함수이다
void tree_delete(Tree *T, Node *z) {

    Node *y;

    // z가 자식을 갖지 않는 경우
    if (z->left == NULL || z->right == NULL) {
        y = z;
    }
    // z가 자식을 갖는 경우, z의 successor를 찾아 후계자 노드 y를 찾는다
    else {
        y = tree_successor(z);
    }

    Node *x;

    // 후계자 노드 y의 자식을 찾아서 노드 x에 할당한다
    if (y->left != NULL) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    // y의 자식 노드 x가 존재하는 경우,
    // x의 부모 포인터가 y가 아니라 y의 부모를 가르키게 한다
    if (x != NULL) {
        x->parent = y->parent;
    }

    // y의 부모가 NULL인 경우는 y가 트리의 root 노드인 경우이다
    if (y->parent == NULL) {
        T->root = x;
    }
    // y가 자신의 부모 노드의 왼쪽 자식 노드인 경우이다
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    // y가 자신의 부모 노드의 오른쪽 자식 노드인 경우이다
    else {
        y->parent->right = x;
    }

    if (y != z) {
        z->key = y->key;
    }

    return y;

}

int main() {

    Tree *T = (Tree*)malloc(sizeof(Tree));
    T->root = NULL;

    tree_insert(T, 56);
    tree_insert(T, 26);
    tree_insert(T, 200);
    tree_insert(T, 18);
    tree_insert(T, 28);
    tree_insert(T, 190);
    tree_insert(T, 213);
    tree_insert(T, 12);
    tree_insert(T, 24);
    tree_insert(T, 27);

    // 노드 삽입 테스트
    printf("\n<insertion test>\n");
    inorder_tree_walk(T->root);
    printf("\n");

    // 노드 검색 테스트
    printf("\n<various search test>\n");
    Node *x = tree_search(T->root, 190);
    printf("%d ", x->key);
    printf("\n");

    Node *min = tree_minimum(T->root);
    printf("minimum : %d ", min->key);
    printf("\n");

    Node *max = tree_maximum(T->root);
    printf("maximum : %d ", max->key);
    printf("\n");

    Node *suc = tree_successor(T->root);
    printf("successor : %d ", suc->key);
    printf("\n");

    Node *pre = tree_predecessor(T->root);
    printf("predecessor : %d ", pre->key);
    printf("\n");

    // 노드 삭제 테스트
    printf("\n<deletion test>\n");
    tree_delete(T, T->root->right->left);
    inorder_tree_walk(T->root);
    printf("\n");

    tree_delete(T, T->root->left->right);
    inorder_tree_walk(T->root);
    printf("\n");

    tree_delete(T, T->root->left);
    inorder_tree_walk(T->root);
    printf("\n");

    return 0;
}