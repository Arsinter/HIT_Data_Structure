#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

struct TreeNode* search(struct TreeNode* root, int value, int* comparisons) {
    (*comparisons)++;
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value, comparisons);
    } else {
        return search(root->right, value, comparisons);
    }
}

int binarySearch(int arr[], int n, int value, int* comparisons) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        (*comparisons)++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == value) {
            return mid;
        }

        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void MakeRand(int arr[], int count) {
    srand((unsigned int) time(NULL)); //随机数种子;
    for (int i = 0; i < count - 1; i++) {
        int num = i + rand() % (count - 1 - i); // 取随机数
        int temp = arr[i];
        arr[i] = arr[num];
        arr[num] = temp; //交换
    }
}

int main() {
    struct TreeNode* bstRoot = NULL;

    // 产生数据
    int testData1[1024];
    for (int i = 0; i < 1024; i++) {
        testData1[i] = 2 * i + 1; // 0 - 2048 奇数
        bstRoot = insert(bstRoot, testData1[i]);
    }

    // In-order traversal (sorting)
    printf("Sorted BST:\n");
    inOrderTraversal(bstRoot);
    printf("\n\n");

    // Search for a value in BST
    int searchValueSuccess = 43; // 可变
    int searchValueFailure = 2;  // 可变
    int bstComparisonsSuccess = 0;
    int bstComparisonsFailure = 0;
    struct TreeNode* searchResultSuccess = search(bstRoot, searchValueSuccess, &bstComparisonsSuccess);
    if (searchResultSuccess != NULL) {
        printf("Value %d found in BST.\n", searchValueSuccess);
        printf("Number of comparisons: %d\n\n", bstComparisonsSuccess);
    } else {
        printf("Value %d not found in BST.\n\n", searchValueSuccess);
        printf("Number of comparisons: %d\n\n", bstComparisonsSuccess);
    }

    struct TreeNode* searchResultFailure = search(bstRoot, searchValueFailure, &bstComparisonsFailure);
    if (searchResultFailure != NULL) {
        printf("Value %d found in BST.\n", searchValueFailure);
        printf("Number of comparisons: %d\n\n", bstComparisonsFailure);
    } else {
        printf("Value %d not found in BST.\n\n", searchValueFailure);
        printf("Number of comparisons: %d\n\n", bstComparisonsFailure);
    }

    // 数据2
    int testData2[1024];
    for (int i = 0; i < 1024; i++) {
        testData2[i] = testData1[i];
    }

    MakeRand(testData2,1024);

    // 二分查找
    int binaryComparisonsSuccess = 0;
    int binaryComparisonsFailure= 0;
    int binarySearchResultSuccess = binarySearch(testData1, 1024, searchValueSuccess, &binaryComparisonsSuccess);
    if (binarySearchResultSuccess != -1) {
        printf("Value %d found using binary search.\n", searchValueSuccess);
        printf("Number of comparisons: %d\n\n", binaryComparisonsSuccess);
    } else {
        printf("Value %d not found using binary search.\n\n", searchValueSuccess);
        printf("Number of comparisons: %d\n\n", binaryComparisonsSuccess);

    }

    int binarySearchResultFailure = binarySearch(testData1, 1024, searchValueFailure, &binaryComparisonsFailure);
    if (binarySearchResultFailure != -1) {
        printf("Value %d found using binary search.\n", searchValueFailure);
        printf("Number of comparisons: %d\n\n", binaryComparisonsFailure);
    } else {
        printf("Value %d not found using binary search.\n\n", searchValueFailure);
        printf("Number of comparisons: %d\n\n", binaryComparisonsFailure);
    }

    // 比较ASL
    double avgComparisonsBST = (double)bstComparisonsSuccess / 1024;
    double avgComparisonsBinary = (double)binaryComparisonsSuccess / 1024;

    printf("Average comparisons for BST: %.2f\n", avgComparisonsBST);
    printf("Average comparisons for binary search: %.2f\n\n", avgComparisonsBinary);

    printf("Theoretical comparison for BST: log2(n) = %.2f\n", log2(1024) - 1);
    printf("Theoretical comparison for binary search: log2(n) = %.2f\n", log2(1024));

    return 0;
}
