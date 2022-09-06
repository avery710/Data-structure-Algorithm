#include <iostream>
#include <vector>
#include <queue>

// global variable
int N, M, target_x, target_y;

class node{
    public:
        int x;
        int y;
        bool isValid(){
            if (x < 1 || y < 1 || x > N || y > M){
                return false;
            }
            else {
                return true;
            }
        }
};

struct queueNode{
    node n;
    int dis;
};

int row_move[] = {-1, 0, 0, 1};
int col_move[] = {0, -1, 1, 0};

int BFS(std::vector<std::vector<int>> &maze, node cur, node end);


int main(){
    std::cin >> N >> M;

    int x, y;
    std::cin >> x >> y >> target_x >> target_y;
    node start = {x, y};
    node end = {target_x, target_y};

    std::vector<std::vector<int>> maze(N + 1, std::vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            std::cin >> maze[i][j];
        }
    }

    int ans = BFS(maze, start, end);
    
    std::cout << ans;
    
    return 0;
}

int BFS(std::vector<std::vector<int>> &maze, node start, node end){
    // check start and end can go through
    if (maze[start.x][start.y] == 0 || maze[end.x][end.y] == 0){
        return -1;
    }

    // mark as visited
    maze[start.x][start.y] = -1;

    std::queue<queueNode> q;

    queueNode start_node = {start, 0};
    q.push(start_node);

    while (!q.empty()){
        queueNode cur = q.front();
        node cur_node = cur.n;

        if (cur_node.x == end.x && cur_node.y == end.y){
            return cur.dis;
        }

        q.pop();

        for (int i = 0; i < 4; i++){
            int row = cur_node.x + row_move[i];
            int col = cur_node.y + col_move[i];
            node curr = {row, col};

            if (curr.isValid() && maze[curr.x][curr.y] == 1){
                maze[curr.x][curr.y] = -1; // mark as visited
                queueNode adjaNode = {{curr.x, curr.y} , cur.dis + 1};

                q.push(adjaNode);
            }
        }
    }

    return -1;
}