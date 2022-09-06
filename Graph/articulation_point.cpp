#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::vector<int>> adj;
std::vector<std::pair<int, int>> ans;

void APUtil(int u, int discovery[], int low[], bool visited[], int &time, int parent){
    int children = 0;

    visited[u] = true;

    discovery[u] = low[u] = ++time;

    for (int v : adj[u]){
        // case 2 : non-visited child
        if (!visited[v]){
            children++;
            APUtil(v, discovery, low, visited, time, u);

            low[u] = std::min(low[u], low[v]);

            // case 2 : non-root & does not have back edge to ancestor
            if (parent != -1 && low[v] >= discovery[u]){
                ans[u].second++;
            }
        }
        // ancestor (back edge)
        else if (v != parent){
            low[u] = std::min(discovery[v], low[u]);
        }
    }
    // case 1 : if u is root
    if (parent == -1 && children >= 2){
        ans[u].second = children;
    }
}

void Articulation_Point(int V){
    int discovery[V];
    int low[V];
    bool visited[V];
    int time = 0, par = -1;

    // Initialize arrays
    std::pair<int, int> tmp;
    for (int i = 0; i < V; i++){
        visited[i] = false;

        tmp = std::make_pair(i, 1);
        ans[i] = tmp;
    }

    APUtil(0, discovery, low, visited, time, par);

    std::sort(ans.begin(), ans.end(), [](std::pair<int, int> &a, std::pair<int, int> &b){
        return (a.second > b.second) || (a.second == b.second && a.first < b.first);
    });
}

int main(){
    int N, M; // N cities: 0 ~ N - 1; M bombs
    std::cin >> N >> M;

    int u, v;
    std::cin >> u >> v;

    //std::vector<int> adj[N];
    adj.resize(N);
    ans.resize(N);

    while (u != -1 && v != -1){
        adj[u].push_back(v);
        adj[v].push_back(u);
        
        std::cin >> u >> v;
    }

    Articulation_Point(N);

    for (int i = 0; i < M; i++){
        std::cout << ans[i].first << ' ' << ans[i].second << std::endl;
    }

    return 0;
}