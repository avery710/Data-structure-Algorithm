// single scource shortest path
// Dijkstra's algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int V;

int extract_min(int dis[], bool SPTset[]){
    int min_value = INT_MAX, min_index;

    for (int i = 1; i <= V; i++){
        if (SPTset[i] == false && dis[i] < min_value){
            min_value = dis[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int** graph, int root){
    int dis[V + 1];

    bool SPTset[V + 1];

    for (int i = 1; i <= V; i++){
        dis[i] = INT_MAX;
        SPTset[i] = false;
    }

    // set the root node
    dis[root] = 0;

    for (int i = 0; i < V - 1; i++){
        int u = extract_min(dis, SPTset);

        SPTset[u] = true;

        for (int v = 1; v <= V; v++){
            if (SPTset[v] == false && graph[u][v] && dis[u] + graph[u][v] < dis[v]){
                dis[v] = dis[u] + graph[u][v];
            }
        }
    }

    for (int i = 1; i <= V; i++){
        printf("%d %d\n", i, dis[i]);
    }

    return;
}

int main(){
    scanf("%d", &V);

    // adj matrix space
    int** graph;
    graph = malloc((V + 1) * sizeof(int*));
    for (int i = 0; i <= V; i++){
        graph[i] = malloc((V + 1) *sizeof(int));
        for (int j = 0; j <= V; j++){
            graph[i][j] = 0;
        }
    }

    // scan in adj list
    int u, v, weight;
    for (int i = 0; i < V - 1; i++){
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    int root;
    scanf("%d", &root);

    dijkstra(graph, root);

    return 0;
}