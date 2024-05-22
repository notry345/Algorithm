#include <stdio.h>
#include <stdlib.h>

typedef struct RedBlackTreeNode {
    struct RedBlackTreeNode *parent, *right, *left;
    int key;
    int color; // 0이면 black, 1이면 red
} RB_Node;

typedef struct RedBlackTree {
    RB_Node *root;
    RB_Node *nil;
} RB_Tree;

// 트리의 균형을 유지하게 해주는 rotation 연산
void left_rotate(RB_Tree *T, RB_Node *x) {

    RB_Node *y = x->right;
    x->right = y->left;

    // y가 왼쪽 서브트리를 갖는 내부 노드라면
    if (y->left != T->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    // x가 root 노드라면
    if (x->parent == T->nil) {
        T->root = y;
    }
    // x가 자신의 부모의 왼쪽 자식이라면
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    // x가 자신의 부모의 오른쪽 자식이라면
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

}

void right_rotate(RB_Tree *T, RB_Node *x) {

    RB_Node *y = x->left;
    x->left = y->right;

    // y가 오른쪽 서브트리를 갖는 내부 노드라면
    if (y->right != T->nil) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    // x가 root 노드라면
    if (x->parent == T->nil) {
        T->root = y;
    }
    // x가 자신의 부모의 오른쪽 자식이라면
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    // x가 자신의 부모의 왼쪽 자식이라면
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;

}

// 삽입 연산이 수행된 후에도 red black tree의 특성이 유지될 수 있도록 조정해주는 함수이다
void RB_insert_fixup(RB_Tree *T, RB_Node *z) {

    // y는 z의 uncle
    RB_Node *y;

    // z의 부모 노드가 red인 동안 반복하며 fixup
    while (z->parent->color == 1) {

        // z의 부모가 왼쪽 자식인 경우
        if (z->parent == z->parent->parent->left) {

            y = z->parent->parent->right;

            if (y->color == 1) { // case 1: uncle 노드가 red인 경우
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) { // case 2: uncle 노드가 black이고 z가 부모의 오른쪽 자식인 경우
                    z = z->parent;
                    left_rotate(T, z);
                    // left rotation을 마치면 case 3과 같은 형태를 띠게 된다
                }
                // case 3: uncle 노드가 black이고 z가 부모의 왼쪽 자식인 경우
                z->parent->color = 0;
                z->parent->parent->color = 1;
                right_rotate(T, z->parent->parent);
            }
        }

        // z의 부모가 오른쪽 자식인 경우 (위와 대칭적인 구조)
        else {

            y = z->parent->parent->left;

            if (y->color == 1) { // case 1: uncle 노드가 red인 경우
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) { // case 2: uncle 노드가 black이고 z가 부모의 왼쪽 자식인 경우
                    z = z->parent;
                    right_rotate(T, z);
                }
                // case 3: uncle 노드가 black이고 z가 부모의 오른쪽 자식인 경우
                z->parent->color = 0;
                z->parent->parent->color = 1;
                left_rotate(T, z->parent->parent);
            }

        }
    }
    // 레드 블랙 트리의 root 노드는 항상 black
    T->root->color = 0;
}

void RB_insert(RB_Tree *T, int key) {

    // 인자로 전달 받은 키 값을 가지는 새로운 노드 z에 메모리 할당하고 키 값 초기화
    RB_Node *z = (RB_Node*)malloc(sizeof(RB_Node));
    z->key = key;

    RB_Node *y = T->nil;
    RB_Node *x = T->root;

    // 삽입할 위치를 탐색
    while (x != T->nil) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    // y는 삽입할 새로운 노드의 부모 노드
    z->parent = y;

    // z를 삽입할 위치가 nil 노드라면 트리의 끝에 삽입
    if (y == T->nil) {
        T->root = z;
    }
    // 삽입할 위치가 nil 노드가 아닌 경우
    // z의 키 값과 z의 부모 노드 y의 키 값을 비교한 후 알맞은 위치에 삽입
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    
    // 새로운 노드 z의 자식 노드들은 nil
    z->left = T->nil;
    z->right = T->nil;
    z->color = 1; // 삽입된 node는 항상 red

    // 삽입된 노드에 의해 레드 블랙 트리의 특성이 위배될 수도 있으니 균형을 유지하도록 수정
    RB_insert_fixup(T, z);
    
}

void inorder_print(RB_Node *x) {

    if (x->key != -1) { // 노드의 키 값이 -1인 경우 nil 노드
        inorder_print(x->left);
        printf("%d, %d\n", x->key, x->color);
        inorder_print(x->right);
    }

}


int main() {

    RB_Tree *RBT = (RB_Tree*)malloc(sizeof(RB_Tree));
    
    // nil 노드에 메모리 할당 및 초기화
    RB_Node *nil = (RB_Node*)malloc(sizeof(RB_Node));
    nil->key = -1; // nil은 트리의 끝을 나타내는 특별한 노드이므로 키 값을 -1 설정
    nil->parent = NULL;
    nil->left = NULL;
    nil->right = NULL;
    nil->color = 0;
    
    RBT->root = nil;
    RBT->nil = nil;

    RB_insert(RBT, 10);
    RB_insert(RBT, 7);
    RB_insert(RBT, 18);
    RB_insert(RBT, 3);
    RB_insert(RBT, 8);
    RB_insert(RBT, 11);
    RB_insert(RBT, 22);
    RB_insert(RBT, 15);
    RB_insert(RBT, 26);

    inorder_print(RBT->root);

    return 0;

}