#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int vertex;
    struct node* next;
}node;

typedef struct Graph{
    int numVertices;
    int* visited;
    node** adjLists;
}Graph;

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

// DFS algo
void DFS(Graph* graph, int v){
    printf("%d ", v);

    node* temp = graph -> adjLists[v];

    graph -> visited[v] = 1;

    while (temp != NULL){
        int nextVertex = temp -> vertex;

        if (graph -> visited[nextVertex] == 0){
            DFS(graph, nextVertex);
        }

        temp = temp -> next;
    }
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

        DFS(G, start);

        n--;
    }

    return 0;
}