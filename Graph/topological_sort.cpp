#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int N, M; // N筆資料，M次比較

void topologicalSort(vector<int> *adj){
    vector<int> in_degree(N + 1, 0);

    // Traverse adjacency lists to fill indegrees of vertices / O(V+E)
    for (int i = 1; i <= N; i++){
        for (auto x : adj[i]){
            in_degree[x]++;
        }
    }

    // if the vertex's indegree = 0 , put it into priority queue
    priority_queue<int, vector<int>, greater<int>> Q;
    for (int i = 1; i <= N; i++){
        if (in_degree[i] == 0){
            Q.push(i);
        }
    }

    // create a vector to store topological results
    vector<int> ans;

    while (!Q.empty()){
        int u = Q.top();
        Q.pop();
        ans.push_back(u);

        for (int x : adj[u]){
            in_degree[x]--;
            if (in_degree[x] == 0){
                Q.push(x);
            }
        }
    }

    // Print topological order
    for (int i : ans){
        cout << i << ' ';
    }
    cout << endl;

    return;
}

int main(){
    while (cin >> N){
        if (N == EOF){
            break;
        }
        cin >> M;

        vector<int> adj[N + 1];

        // add edges
        int a, b;
        for (int i = 0; i < M; i++){
            cin >> a >> b;
            adj[a].push_back(b);
        }
        
        topologicalSort(adj);
    }
    
    return 0;
}