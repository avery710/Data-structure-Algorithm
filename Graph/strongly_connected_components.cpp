#include <iostream>
#include <vector>
#include <stack>

class Graph{
    int V;
    std::vector<int> *adj;

    // Fills Stack with vertices (in increasing order of finishing times). 
    // The top element of stack has the maximum finishing time.
    void fillOrder(int vertex, bool visited[], std::stack<int> &Stack);
    void Graph::DFSUtil(int vertex, bool visited[]);
    
public:
    Graph(int V);
    void addEdge(int u, int v, int d);
    void printSCC();
    Graph getTranspose();
};

// Initialize graph (ask for space)
Graph::Graph(int V){
    this -> V = V;
    adj = new std::vector<int>[V + 1];
}

void Graph::addEdge(int u, int v, int d){
    adj[u].push_back(v);
    if (d == 2){
        adj[v].push_back(u);
    }
}

Graph Graph::getTranspose(){
    Graph g(V);
    for (int v = 1; v <= V; v++){
        std::vector<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); i++){
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

// fill the finish time order in stack
void Graph::fillOrder(int vertex, bool visited[], std::stack<int> &Stack){
    visited[vertex] = true;

    std::vector<int>::iterator i;
    for (i = adj[vertex].begin(); i != adj[vertex].end(); i++){
        if (!visited[*i]){
            fillOrder(*i, visited, Stack);
        }
    }

    Stack.push(vertex);
}

void Graph::DFSUtil(int vertex, bool visited[]){
    visited[vertex] = true;

    std::vector<int>::iterator i;
    for (i = adj[vertex].begin(); i != adj[vertex].end(); i++){
        if (!visited[*i]){
            DFSUtil(*i, visited);
        }
    }
}

void Graph::printSCC(){
    std::stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS : finish time record)
    bool visited[V + 1];
    for (int i = 1; i <= V; i++){
        visited[i] = false;
    }

    for (int i = 1; i <= V; i++){
        if (visited[i] == false){
            fillOrder(i, visited, Stack);
        }
    }

    Graph g2 = getTranspose();

    // Mark all the vertices as not visited (For second DFS : transpose graph DFS)
    for (int i = 1; i <= V; i++){
        visited[i] = false;
    }

    int v = Stack.top();

    g2.DFSUtil(v, visited);

    for (int i = 1; i <= V; i++){
        if (!visited[i]){
            std::cout << 0 << std::endl;
            return;
        }
    }

    std::cout << 1 << std::endl;
    return;
}

int main(){
    int N, M; // N cities, M flights
    std::cin >> N >> M;

    while (N != 0 && M != 0){
        Graph G(N);

        int u, v, d;
        for (int i = 0; i < M; i++){
            std::cin >> u >> v >> d;
            G.addEdge(u, v, d);
        }

        G.printSCC();
        std::cin >> N >> M;
    }

    return 0;
}