#include <stdio.h>
#include <stdlib.h>

// 顺序表
typedef struct {
    int *elem;
    int length;
    int listSize;
}Seqlist;

Seqlist createSeqList(int n) {
    Seqlist L;
    L.elem = (int*)malloc(sizeof(int) * n); // 为elem分配内存
    if (L.elem == NULL) {
        // 处理内存分配失败的情况
        exit(1); // 退出程序或者采取其他错误处理措施
    }

    printf("Input the SeqList (separated by spaces):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &L.elem[i]);
    }
    L.length = n;
    return L;
}

int insertSeq(Seqlist *pl,int i,int e)
{
    int *newele;
    int j;
    if (i<1||i>pl->length){
        printf("Wrong insert position");
        return -1;
    }
    if(pl->length>= pl->listSize){
        newele = (int *) realloc(pl->elem,(pl->listSize+10)* sizeof(int ));
        if (!newele){ exit(-1);}
        pl->elem=newele;
        pl->listSize+=10;
    }
    for (j=pl->length-1;j>=i-1;j--){
        pl->elem[j+1]=pl->elem[j];
    }
    pl->elem[i-1]=e;
    pl->length++;
    return 0;
}

// 顺序存储结构删除指定元素
void deleteSeqlist(Seqlist *list, int target) {
    int i, j;
    for (i = 0; i < list->length; i++) {
        if (list->elem[i] == target) {
            for (j = i; j < list->length - 1; j++) {
                list->elem[j] = list->elem[j+1];
            }
            list->length--;
            break;
        }
    }
}

// 顺序存储结构删除重复元素
void deleteSeqlistCopy(Seqlist *list) {
    int i, j;
    for (i = 0; i < list->length; i++) {
        while (i < list->length - 1 && list->elem[i] == list->elem[i+1]) {
            for (j = i+1; j < list->length - 1; j++) {
                list->elem[j] = list->elem[j+1];
            }
            list->length--;
        }
    }
}

// 顺序存储结构逆置
void reverseSeqlist(Seqlist *list) {
    int i, temp;
    for (i = 0; i < list->length / 2; i++) {
        temp = list->elem[i];
        list->elem[i] = list->elem[list->length - i - 1];
        list->elem[list->length - i - 1] = temp;
    }
}

// 顺序存储结构循环左移 k 位
void leftShift(Seqlist *list, int k) {
    if (k <= 0 || k >= list->length) {
        return; // 无需移动或移动超出范围
    }

    // 申请临时空间用于存放移动后的元素
    int *temp = (int *)malloc(list->length * sizeof(int));
    if (!temp) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }

    // 将元素复制到临时数组
    for (int i = 0; i < list->length; i++) {
        temp[i] = list->elem[i];
    }

    // 左移k位
    for (int i = 0; i < list->length; i++) {
        list->elem[i] = temp[(i + k) % list->length];
    }

    // 释放临时数组的内存
    free(temp);
}

// 顺序存储结构循环右移 k 位
void rightShift(Seqlist *list, int k) {
    if (k <= 0 || k >= list->length) {
        return; // 无需移动或移动超过列表长度，直接返回
    }

    int *newElem = (int *)malloc(list->listSize * sizeof(int));
    if (newElem == NULL) {
        exit(EXIT_FAILURE); // 内存分配失败
    }

    // 将元素向右移动k位
    for (int i = 0; i < list->length; i++) {
        newElem[(i + k) % list->length] = list->elem[i];
    }

    free(list->elem); // 释放原有的内存
    list->elem = newElem;
}


// 顺序存储结构合并两个有序线性表
void mergeSeq(Seqlist *list1, Seqlist *list2, Seqlist *result) {
    int i = 0, j = 0, k = 0;
    while (i < list1->length && j < list2->length) {
        if (list1->elem[i] <= list2->elem[j]) {
            result->elem[k++] = list1->elem[i++];
        } else {
            result->elem[k++] = list2->elem[j++];
        }
    }
    while (i < list1->length) {
        result->elem[k++] = list1->elem[i++];
    }
    while (j < list2->length) {
        result->elem[k++] = list2->elem[j++];
    }
    result->length = k;
}

void printSeq(Seqlist l)
{
    if(l.length==0){
        printf("Empty Seq!\n");
        return;
    }
    printf("Seq is:\n");
    for (int i = 0; i < l.length; i++) {
        printf("%d ",l.elem[i]);
    }
    printf("\n");
}


int main() {
    int numSeqlist;
    int e = 0,i = 0,kl = 0,kr = 0;

    Seqlist a,b,c;

    printf("num of Seqlist is:\n");
    scanf(" %d", &numSeqlist);
    a = createSeqList(numSeqlist);
    printSeq(a);
    b = createSeqList(numSeqlist);
    printSeq(b);

    printf("data you wanna insert is:\n");
    scanf("%d", &e);
    printf("position you wanna insert is:\n");
    scanf("%d", &i);
    if (insertSeq(&a, i, e)) {
        printf("insert successfully!\n");
        printSeq(a);
    }

    printf("The element you wanna delete:");
    scanf(" %d", &e);
    deleteSeqlist(&a, e);
    printSeq(a);

    printf("delete copy:\n");
    deleteSeqlistCopy(&a);
    printSeq(a);

    printf("Left shift k:\n");
    scanf("%d", &kl);
    leftShift(&a, kl);
    printSeq(a);

    printf("Right shift k:\n");
    scanf("%d", &kr);
    rightShift(&a, kr);
    printSeq(a);

    printf("to merge\n");
    mergeSeq(&a, &b, &c);
    printSeq(c);

    printf("Reverse the Seqlist\n");
    reverseSeqlist(&a);
    printSeq(a);

    return 0;
}
