#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} LNode, *LinkList;

LinkList createNode(int data) {
    LinkList newNode = (LinkList)malloc(sizeof(LNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

LinkList createList(int arr[], int n) {
    if (n == 0) return NULL;

    LinkList head = createNode(arr[0]);
    LinkList current = head;

    for (int i = 1; i < n; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }

    return head;
}

void printList(LinkList head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void deleteElement(LinkList* head, int target) {
    if (*head == NULL) return;

    LinkList prev = NULL;
    LinkList current = *head;

    while (current != NULL) {
        if (current->data == target) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            current = prev ? prev->next : *head;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void removeDuplicates(LinkList* head) {
    if (*head == NULL) return;

    LinkList current = *head;

    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            LinkList temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

void reverseList(LinkList* head) {
    LinkList prev = NULL;
    LinkList current = *head;
    LinkList next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

LinkList leftShift(LinkList head, int k) {
    if (head == NULL || k <= 0) return head;

    LinkList fast = head;
    LinkList slow = head;

    for (int i = 0; i < k; i++) {
        if (fast == NULL) return head;
        fast = fast->next;
    }

    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    fast->next = head;
    head = slow->next;
    slow->next = NULL;

    return head;
}

LinkList rightShift(LinkList head, int k) {
    if (head == NULL || k <= 0) return head;

    int length = 1;
    LinkList tail = head;

    while (tail->next != NULL) {
        length++;
        tail = tail->next;
    }

    k = k % length;
    if (k == 0) return head;

    LinkList newTail = head;
    for (int i = 0; i < length - k - 1; i++) {
        newTail = newTail->next;
    }

    tail->next = head;
    head = newTail->next;
    newTail->next = NULL;

    return head;
}

LinkList mergeSortedLists(LinkList list1, LinkList list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    LinkList mergedList = NULL;
    LinkList current = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            if (mergedList == NULL) {
                mergedList = list1;
                current = list1;
            } else {
                current->next = list1;
                current = current->next;
            }
            list1 = list1->next;
        } else {
            if (mergedList == NULL) {
                mergedList = list2;
                current = list2;
            } else {
                current->next = list2;
                current = current->next;
            }
            list2 = list2->next;
        }
    }

    if (list1 != NULL) {
        current->next = list1;
    } else {
        current->next = list2;
    }

    return mergedList;
}

int main() {
    int arr1[] = {1, 3, 3, 5, 7, 9, 9};
    int arr2[] = {2, 4, 6, 8, 10};

    LinkList list1 = createList(arr1, 7);
    LinkList list2 = createList(arr2, 5);

    printf("Original Linklist 1: ");
    printList(list1);
    printf("Original Linklist 2: ");
    printList(list2);

    // 删除给定元素的算法
    deleteElement(&list1, 3);
    printf("Linklist 1 after deleting element 3: ");
    printList(list1);

    // 删除所有重复元素的算法
    removeDuplicates(&list1);
    printf("Linklist 1 after deleting element copy: ");
    printList(list1);

    // 逆置算法
    reverseList(&list1);
    printf("Linklist 1 after reversing: ");
    printList(list1);

    // 循环左移2位的算法
    list1 = leftShift(list1, 2);
    printf("Linklist 1 after leftShifting 2: ");
    printList(list1);

    // 循环右移2位的算法
    list1 = rightShift(list1, 2);
    printf("Linklist 1 after rightShifting 2: ");
    printList(list1);

    // 合并两个已排好序的线性表的算法
    LinkList mergedList = mergeSortedLists(list1, list2);
    printf("Linklist after merging: ");
    printList(mergedList);

    return 0;
}
