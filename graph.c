#include <stdio.h>
#include <stdlib.h>

#define NumVertices 20
typedef int VertexData;
typedef int EdgeData;

// 图的存储结构（邻接矩阵）
typedef struct{
    VertexData verList[NumVertices]; //顶点表
    EdgeData edge[NumVertices][NumVertices]; //边表的邻接矩阵
    int vertexNum,edgeNum; //图的顶点数和边数
}GraphMatrix;

// 图的存储结构（邻接表）
typedef struct node{//边表结点
    int adjVertex; //邻接点域（下标）
    EdgeData cost; //边上的权值
    struct node* next;
}EdgeNode;

// 顶点表节点
typedef struct {
    VertexData vertex; //顶点数据域
    EdgeNode* firstEdge; //边链表头指针
}VertexNode;

// 图的邻接表
typedef struct{
    VertexNode vex_List[NumVertices];
    int vertex_Num,edge_Num; //图的顶点数和边数
}GraphList;

void CreateMGraphMatrix(GraphMatrix *G, int vertexNum, int edgeNum, int vertexData[], int edges[][3]){
    G->vertexNum = vertexNum;
    G->edgeNum = edgeNum;

    for (int i = 0; i < G->vertexNum; ++i) {
        G->verList[i] = vertexData[i];
    }

    for (int i = 0; i < G->vertexNum; ++i) {
        for (int j = 0; j < G->vertexNum; ++j) {
            G->edge[i][j] = 0;
        }
    }

    for (int k = 0; k < G->edgeNum; ++k) {
        int i = edges[k][0];
        int j = edges[k][1];
        int weightOfEdge = edges[k][2];

        G->edge[i][j] = weightOfEdge;
        G->edge[j][i] = weightOfEdge;
    }
}

void CreateGraphList(GraphList *G, int vertex_Num, int edge_Num, int vertexData[], int edges[][3]){
    G->vertex_Num = vertex_Num;
    G->edge_Num = edge_Num;

    for (int i = 0; i < G->vertex_Num; i++) {
        G->vex_List[i].vertex = vertexData[i];
        G->vex_List[i].firstEdge = NULL;
    }

    for (int i = 0; i < G->edge_Num; i++) {
        int tail = edges[i][0];
        int head = edges[i][1];
        EdgeData weight = edges[i][2];

        EdgeNode *p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->adjVertex = head;
        p->cost = weight;
        p->next = G->vex_List[tail].firstEdge;
        G->vex_List[tail].firstEdge = p;

        p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->adjVertex = tail;
        p->cost = weight;
        p->next = G->vex_List[head].firstEdge;
        G->vex_List[head].firstEdge = p;
    }
}

void MatrixToList(GraphMatrix* G, GraphList* L) {
    L->vertex_Num = G->vertexNum;
    L->edge_Num = G->edgeNum;

    for (int i = 0; i < G->vertexNum; ++i) {
        L->vex_List[i].vertex = G->verList[i];

        L->vex_List[i].firstEdge = NULL;
        for (int j = 0; j < G->vertexNum; ++j) {
            if (G->edge[i][j] != 0) {
                EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode));
                p->adjVertex = j;
                p->cost = G->edge[i][j];
                p->next = L->vex_List[i].firstEdge;
                L->vex_List[i].firstEdge = p;
            }
        }
    }
}

void ListToMatrix(GraphList* L, GraphMatrix* G) {
    G->vertexNum = L->vertex_Num;
    G->edgeNum = L->edge_Num;

    for (int i = 0; i < L->vertex_Num; ++i) {
        G->verList[i] = L->vex_List[i].vertex;
        for (int j = 0; j < L->vertex_Num; ++j) {
            G->edge[i][j] = 0;
        }

        EdgeNode* p = L->vex_List[i].firstEdge;
        while (p != NULL) {
            G->edge[i][p->adjVertex] = p->cost;
            p = p->next;
        }
    }
}

void DFS_Matrix(GraphMatrix* G, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", G->verList[v]);

    for (int i = 0; i < G->vertexNum; ++i) {
        if (G->edge[v][i] && !visited[i]) {
            DFS_Matrix(G, i, visited);
        }
    }
}

void DFS_Traverse_Matrix(GraphMatrix* G) {
    int visited[NumVertices];
    for (int i = 0; i < G->vertexNum; ++i) {
        visited[i] = 0;
    }

    printf("Depth First Search (DFS) result:\n");
    for (int i = 0; i < G->vertexNum; ++i) {
        if (!visited[i]) {
            DFS_Matrix(G, i, visited);
        }
    }
    printf("\n");
}

void BFS_Matrix(GraphMatrix* G, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", G->verList[v]);

    int queue[NumVertices], front = 0, rear = 0;
    queue[rear++] = v;

    while (front != rear) {
        int u = queue[front++];
        for (int i = 0; i < G->vertexNum; ++i) {
            if (G->edge[u][i] && !visited[i]) {
                visited[i] = 1;
                printf("%d ", G->verList[i]);
                queue[rear++] = i;
            }
        }
    }
}

void BFS_Traverse_Matrix(GraphMatrix* G) {
    int visited[NumVertices];
    for (int i = 0; i < G->vertexNum; ++i) {
        visited[i] = 0;
    }

    printf("Breadth First Search (BFS) result:\n");
    for (int i = 0; i < G->vertexNum; ++i) {
        if (!visited[i]) {
            BFS_Matrix(G, i, visited);
        }
    }
    printf("\n");
}

void DFS_List(GraphList* G, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", G->vex_List[v].vertex);

    EdgeNode* p = G->vex_List[v].firstEdge;
    while (p != NULL) {
        if (!visited[p->adjVertex]) {
            DFS_List(G, p->adjVertex, visited);
        }
        p = p->next;
    }
}

void DFS_Traverse_List(GraphList* G) {
    int visited[NumVertices];
    for (int i = 0; i < G->vertex_Num; ++i) {
        visited[i] = 0;
    }

    printf("Depth First Search (DFS) result:\n");
    for (int i = 0; i < G->vertex_Num; ++i) {
        if (!visited[i]) {
            DFS_List(G, i, visited);
        }
    }
    printf("\n");
}

void BFS_List(GraphList* G, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", G->vex_List[v].vertex);

    int queue[NumVertices], front = 0, rear = 0;
    queue[rear++] = v;

    while (front != rear) {
        int u = queue[front++];
        EdgeNode* p = G->vex_List[u].firstEdge;
        while (p != NULL) {
            if (!visited[p->adjVertex]) {
                visited[p->adjVertex] = 1;
                printf("%d ", G->vex_List[p->adjVertex].vertex);
                queue[rear++] = p->adjVertex;
            }
            p = p->next;
        }
    }
}

void BFS_Traverse_List(GraphList* G) {
    int visited[NumVertices];
    for (int i = 0; i < G->vertex_Num; ++i) {
        visited[i] = 0;
    }
    printf("Breadth First Search (BFS) result:\n");

    for (int i = 0; i < G->vertex_Num; ++i) {
        if (!visited[i]) {
            BFS_List(G, i, visited);
        }
    }
    printf("\n");
}

int CalculateDegree(GraphList* G, int vertex) {
    int degree = 0;
    EdgeNode* p = G->vex_List[vertex].firstEdge;

    while (p != NULL) {
        degree++;
        p = p->next;
    }

    return degree;
}

void CalculateAllDegrees(GraphList* G) {
    printf("Vertex Degrees:\n");
    for (int i = 0; i < G->vertex_Num; i++) {
        int degree = CalculateDegree(G, i);
        printf("Vertex %d: %d\n", G->vex_List[i].vertex, degree);
    }
}


int main() {
    int vertexData1[NumVertices] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 顶点数据
    int edges1[13][3] = {{0, 1, 5}, {0, 2, 10}, {1, 2, 20}, {2, 3, 15}, {3, 4, 25}, {4, 5, 30}, {5, 6, 35},
                         {6, 7, 40}, {7, 8, 45}, {8, 9, 50}, {9, 0, 55}, {0, 5, 60}, {5, 7, 65}}; // 边的数据

    GraphMatrix GMatrix;
    CreateMGraphMatrix(&GMatrix, NumVertices, 13, vertexData1, edges1);

    GraphList GList;
    int vertexData2[NumVertices] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 顶点数据
    int edges2[13][3] = {{0, 1, 5}, {0, 2, 10}, {1, 2, 20}, {2, 3, 15}, {3, 4, 25}, {4, 5, 30}, {5, 6, 35},
                         {6, 7, 40}, {7, 8, 45}, {8, 9, 50}, {9, 0, 55}, {0, 5, 60}, {5, 7, 65}}; // 边的数据

    CreateGraphList(&GList, NumVertices, 13, vertexData2, edges2);

    // 将邻接矩阵转为邻接表
    GraphList GListFromMatrix;
    MatrixToList(&GMatrix, &GListFromMatrix);

    // 将邻接表转为邻接矩阵
    GraphMatrix GMatrixFromList;
    ListToMatrix(&GList, &GMatrixFromList);

    //深度优先搜索（邻接矩阵）
    DFS_Traverse_Matrix(&GMatrix);

    // 广度优先搜索（邻接矩阵）
    BFS_Traverse_Matrix(&GMatrix);

    // 深度优先搜索（邻接表）
    DFS_Traverse_List(&GListFromMatrix);

    // 广度优先搜索（邻接表）
    BFS_Traverse_List(&GList);

    // 计算顶点度数
    CalculateAllDegrees(&GList);
    return 0;
}
