#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u, v, c;
}edge;

// sort the cost of edges
void swap(edge* a, edge*b){
    edge temp;
    temp.u = (*a).u;
    temp.v = (*a).v;
    temp.c = (*a).c;

    (*a).u = (*b).u;
    (*a).v = (*b).v;
    (*a).c = (*b).c;

    (*b).u = temp.u;
    (*b).v = temp.v;
    (*b).c = temp.c;
}

void heapify(edge* edgeList, int n, int cur_idx){
    int lchild_idx = cur_idx * 2 + 1;
    int rchild_idx = cur_idx * 2 + 2;
    int largest_idx = cur_idx;

    //check whether the index is valid
    if (lchild_idx < n && edgeList[lchild_idx].c > edgeList[largest_idx].c){
        largest_idx = lchild_idx;
    }

    if (rchild_idx < n && edgeList[rchild_idx].c > edgeList[largest_idx].c){
        largest_idx = rchild_idx;
    }

    //if the largest index has changed, meaning that the value needs to be swapped
    if (largest_idx != cur_idx){
        swap(&edgeList[cur_idx], &edgeList[largest_idx]);
        
        heapify(edgeList, n, largest_idx);
    }
}

void heapSort(edge* edgeList, int E){
    // build max heap
    for (int i = E / 2 - 1; i >= 0; i--){
        heapify(edgeList, E, i);
    }

    //pop out the max num, and fill the blank with the last node
    for (int i = E - 1; i > 0; i--){
        swap(&edgeList[0], &edgeList[i]);
        heapify(edgeList, i, 0);
    }
}

// find 
int find(int* subset, int i){
    int root = i;

    // find out the ROOT
    while (subset[root] >= 0){
        root = subset[root];
    }

    // update from i to ROOT
    while (i != root){
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}

// union
void Union(int* subset, int x, int y){
    int x_root = find(subset, x);
    int y_root = find(subset, y);

    // 越負越多elements
    if (subset[x_root] <= subset[y_root]){
        subset[x_root] += subset[y_root];
        subset[y_root] = x_root;
    }
    else {
        subset[y_root] += subset[x_root];
        subset[x_root] = y_root;
    }

}

// Kruskal's MST algo
void kruskals_mst(edge* edgeList, int V, int E){
    int subset[V];
    for (int i = 0; i < V; i++){
        subset[i] = -1;
    }

    int ans = 0;

    for (int i = 0; i < E; i++){
        int u = edgeList[i].u;
        int v = edgeList[i].v;
        int cost = edgeList[i].c;

        if (find(subset, u) != find(subset, v)){
            Union(subset, u, v);
            ans += cost;
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", ans);
}

int main(){
    int V, E;
    scanf("%d %d", &V, &E);

    edge* edgeList = malloc(E * sizeof(edge));
    int  x, y, z;
    for (int i = 0; i < E; i++){
        scanf("%d %d %d", &x, &y, &z);
        edgeList[i].u = x;
        edgeList[i].v = y;
        edgeList[i].c = z;
    }

    // sort edges (min heap)
    heapSort(edgeList, E);

    kruskals_mst(edgeList, V, E);

    return 0;
}