#include <iostream>
#include <string>
#include <vector>
#include <climits>

int N;

int str_cmp(std::string &a, std::string &b){
    int count = 0;

    for (int i = 0; i < 7; i++){
        if (a[i] != b[i]){
            count++;
        }
    }

    return count;
}

int min_weight(int weight[], bool MSTset[]){
    int min_weight = INT_MAX, min_index;
    
    for (int i = 0; i < N; i++){
        if (MSTset[i] == false && weight[i] < min_weight){
            min_weight = weight[i];
            min_index = i;
        }
    }

    return min_index;
}

void primMST(int** adj){
    int weight[N];

    int parent[N];

    bool MSTset[N];

    // Initialize arrays
    for (int i = 0; i < N; i++){
        weight[i] = INT_MAX;
        MSTset[i] = false;
    }

    // set first node
    weight[0] = 0;
    parent[0] = -1;

    // the MST will have V - 1 edges
    for (int count = 0; count < N - 1; count++){
        // find the next min weight edge
        int u = min_weight(weight, MSTset);

        // add it to MST set
        MSTset[u] = true;

        for (int i = 0; i < N; i++){
            if (adj[u][i] && MSTset[i] == false && adj[u][i] < weight[i]){
                weight[i] = adj[u][i];
                parent[i] = u;
            }
        }
    }

    // calculate the total min weight
    int ans = 0;
    for (int i = 0; i < N; i++){
        ans += weight[i];
    }

    std::cout << "The highest possible quality is 1/" << ans << '.';
}

int main(){
    std::cin >> N;

    // store type codes
    std::vector<std::string> types;
    std::string tmp;
    for (int i = 0; i < N; i++){
        std::cin >> tmp;
        types.push_back(tmp);
    }

    // ask for adj space
    int** adj;
    adj = new int*[N];
    for (int i = 0; i < N; i++){
        adj[i] = new int[N];
        adj[i][i] = 0;
    }

    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            adj[i][j] = str_cmp(types[i], types[j]);
            adj[j][i] = adj[i][j];
        }
    }

    primMST(adj);

    return 0;
}