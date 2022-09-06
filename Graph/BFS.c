#include <stdio.h>
#include <stdlib.h>
#define SIZE 109

typedef struct node{
    int vertex;
    struct node* next;
}node;

typedef struct Graph{
    int numVertices;
    int* visited;
    node** adjLists;
}Graph;

typedef struct queue{
    int items[SIZE];
    int front;
    int rear;
}queue;

// Create a node
node* createNode(int v){
    node* newNode = malloc(sizeof(node));
    newNode -> vertex = v;
    newNode -> next = NULL;
    return newNode;
}

// Create graph
Graph* createGraph(int vertices){
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph -> numVertices = vertices;
    newGraph -> adjLists = malloc(vertices * sizeof(node*));
    newGraph -> visited = malloc(vertices * sizeof(int));

    // initialize adjList and visited[]
    for (int i = 0; i < vertices; i++){
        newGraph -> adjLists[i] = NULL;
        newGraph -> visited[i] = 0;
    }

    return newGraph;
}

// create a queue
queue* createQueue(){
    queue* Q = malloc(sizeof(queue));
    Q -> front = -1;
    Q -> rear = -1;

    return Q;
}

// check if the queue is empty
int isEmpty(queue* Q){
    if (Q -> rear == -1){
        return 1;
    }
    else {
        return 0;
    }
}

// Adding elements into queue
void enqueue(queue* Q, int value){
    if (Q -> rear == SIZE - 1){
        printf("Queue is full!\n");
    }
    else {
        // If nothing
        if (Q -> front == -1){
            Q -> front = 0;
        }
        Q -> rear++;
        Q -> items[Q -> rear] = value;
    }
}

// Remove elements from queue
int dequeue(queue* Q){
    int item;

    if (isEmpty(Q)){
        printf("Queue is empty\n");
        item = -1;
    }
    else {
        // pop from front
        item = Q -> items[Q -> front];
        Q -> front++;

        // check whether front exceed rear (empty), if yes, reset the queue
        if (Q -> front > Q -> rear){
            Q -> front = Q -> rear = -1;
        }
    }
    
    return item;
}

// Print the queue
void printQueue(queue* Q){
    if (isEmpty(Q)){
        printf("Queue is empty\n");
    } 
    else{
        printf("\nQueue contains: ");
        for (int i = Q -> front; i < Q -> rear + 1; i++) {
            printf("%d ", Q -> items[i]);
        }
        printf("\n");
    }
}

// BFS algo
void BFS(Graph* graph, int start){
    queue* Q = createQueue();

    graph -> visited[start] = 1;
    enqueue(Q, start);

    while (!isEmpty(Q)){
        // printQueue(Q);
        int cur = dequeue(Q);
        printf("%d ", cur);

        node* temp = graph -> adjLists[cur];

        while (temp){
            int nextVertex = temp -> vertex;

            if (graph -> visited[nextVertex] == 0){
                graph -> visited[nextVertex] = 1;
                enqueue(Q, nextVertex);
            }

            temp = temp -> next;
        }
    }
}

// Add edge (undirected edge)
void addEdge(Graph* graph, int src, int dest){
    // add edge from src to dest
    node* newNode = createNode(dest);
    newNode -> next = graph -> adjLists[src];
    graph -> adjLists[src] = newNode;

    // add edge from dest to src
    newNode = createNode(src);
    newNode -> next = graph -> adjLists[dest];
    graph -> adjLists[dest] = newNode;
}

int main(){
    int n;
    scanf("%d", &n);
    while (n != 0){
        int vertices, start;
        scanf("%d %d", &vertices, &start);

        // create a graph
        Graph* G = createGraph(vertices);

        int x;
        int** adjMatrix;
        adjMatrix = malloc(vertices * sizeof(int*));
        for (int i = 0; i < vertices; i++){
            adjMatrix[i] = malloc(vertices * sizeof(int));
            for (int j = 0; j < vertices; j++){
                scanf("%d", &adjMatrix[i][j]);
            }
        }

        for (int i = vertices - 1; i >= 0; i--){
            for (int j = vertices - 1; j >= 0; j--){
                if (adjMatrix[i][j] == 1){
                    addEdge(G, i, j);
                }
            }
        }

        BFS(G, start);

        n--;
    }

    return 0;
}