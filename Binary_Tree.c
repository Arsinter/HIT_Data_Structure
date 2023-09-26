/*
    递归和非递归算法一并在main函数中给出
    作业要求：
    1．编写建立二叉树的动态（或者静态）二叉链表存储结构（左右链表示）的程
    序，并以适当的形式显示和保存二叉树；
    2．采用二叉树的上述二叉链表存储结构，编写程序实现二叉树的先序、中序和
    后序遍历的递归和非递归算法以及层序遍历算法，并以适当的形式显示和保
    存二叉树及其相应的遍历序列；
    3．设计并实现判断任意一棵二叉树是否为完全二叉树的算法。
    4．设计并实现计算任意一棵二叉树的宽度的（递归或非递归）算法。二叉树的
    宽度是指其各层结点数的最大值。
    注：二叉树的显示（输出）以适当的形式即可，不必采用可视化的图形方式
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct BTree{
    int data;
    struct BTree *LChild;
    struct BTree *RChild;
}BTree;

// 创建新节点
BTree * createNode(int data) {
    BTree* newNode = (BTree*)malloc(sizeof(BTree));
    newNode->data = data;
    newNode->LChild = newNode->RChild = NULL;
    return newNode;
}

// 创建二叉树
BTree* creteBtree(){
    int data;
    printf("Enter node data (or -1 for NULL): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    BTree* newNode = createNode(data);

    printf("Enter left child of %d:\n", data);
    newNode->LChild = creteBtree();

    printf("Enter right child of %d:\n", data);
    newNode->RChild = creteBtree();

    return newNode;
}

// 先序遍历 + 非递归
void preOrder(BTree * root){
    if (root == NULL) return;

    // 创建一个栈
    BTree* stack[1000];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        BTree* current = stack[top--];
        printf("%d ", current->data);

        if (current->RChild != NULL) {
            stack[++top] = current->RChild;
        }

        if (current->LChild != NULL) {
            stack[++top] = current->LChild;
        }
    }
}

// 先序遍历 + 递归
void preOrderRecursion(BTree* root){
    if(root == NULL){
        return;
    }
    printf("%d ",root->data);
    preOrderRecursion(root->LChild);
    preOrderRecursion(root->RChild);
}

// 中序遍历 + 非递归
void inOrder(BTree *root){
    if (root == NULL) return;

    // 创建一个栈
    BTree* stack[1000];
    int top = -1;

    BTree* current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->LChild;
        }

        current = stack[top--];
        printf("%d ", current->data);

        current = current->RChild;
    }
}

// 中序遍历 + 递归
void inOrderRecursion(BTree* root){
    if(root == NULL){
        return;
    }
    inOrderRecursion(root->LChild);
    printf("%d ",root->data);
    inOrderRecursion(root->RChild);
}

// 后序遍历 + 非递归
void postOrder(BTree *root){
    if (root == NULL) return;

    // 创建两个栈，一个用于存放遍历顺序，另一个用于辅助操作
    BTree* stack1[1000];
    BTree* stack2[1000];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        BTree* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->LChild != NULL) {
            stack1[++top1] = current->LChild;
        }

        if (current->RChild != NULL) {
            stack1[++top1] = current->RChild;
        }
    }

    while (top2 >= 0) {
        BTree* current = stack2[top2--];
        printf("%d ", current->data);
    }
}

// 后续遍历 + 递归
void postOrderRecursion(BTree* root){
    if(root == NULL){
        return;
    }
    postOrderRecursion(root->LChild);
    postOrderRecursion(root->RChild);
    printf("%d ",root->data);
}

// 层序遍历
void levelOrder(BTree* root) {

    if (root == NULL){
        return;
    }

    // 创建一个队列用于层序遍历
    BTree* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        BTree * current = queue[front++];
        printf("%d ", current->data);

        if (current->LChild != NULL) {
            queue[rear++] = current->LChild;
        }

        if (current->RChild != NULL) {
            queue[rear++] = current->RChild;
        }
    }
}

// 判断是否为完全二叉树
int isComplete(BTree* root) {
    if (root == NULL) return 1;

    // 创建一个队列用于层序遍历
    BTree* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int flag = 0; // 用于标记是否遇到过空结点

    while (front < rear) {
        BTree * current = queue[front++];

        // 如果遇到空结点后，不能再出现非空结点
        if (current == NULL) {
            flag = 1;
        } else {
            if (flag == 1) return 0; // 如果已经遇到过空结点，则不能再遇到非空结点
            queue[rear++] = current->LChild;
            queue[rear++] = current->RChild;
        }
    }

    return 1; // 遍历完毕，符合完全二叉树的定义
}

// 计算树的宽度
int calculateBtreeWidth(BTree* root){
    if (root == NULL) return 0;

    // 创建一个队列用于层序遍历
    BTree * queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int maxWidth = 0;

    while (front < rear) {
        int currentLevelWidth = rear - front; // 当前层的结点数

        if (currentLevelWidth > maxWidth) {
            maxWidth = currentLevelWidth;
        }

        while (currentLevelWidth--) {
            BTree * current = queue[front++];

            if (current->LChild != NULL) {
                queue[rear++] = current->LChild;
            }

            if (current->RChild != NULL) {
                queue[rear++] = current->RChild;
            }
        }
    }

    return maxWidth;
}

int main() {
    BTree * root = creteBtree();

    // 先序遍历
    printf("Preorder Traversal: ");
    preOrderRecursion(root);
    printf("\n");
    preOrder(root);
    printf("\n");

    // 中序遍历
    printf("Inorder Traversal: ");
    inOrderRecursion(root);
    printf("\n");
    inOrder(root);
    printf("\n");

    // 后序遍历
    printf("Postorder Traversal: ");
    postOrderRecursion(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    // 层序遍历
    printf("Level Order Traversal: ");
    levelOrder(root);
    printf("\n");

    // 判断是否为完全二叉树
    if (isComplete(root)) {
        printf("The tree is a complete binary tree.\n");
    } else {
        printf("The tree is not a complete binary tree.\n");
    }

    // 计算宽度
    int width = calculateBtreeWidth(root);
    printf("Width of the tree: %d\n", width);
    return 0;
}
