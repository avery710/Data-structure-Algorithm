#include <iostream>
#include <vector>

int target_x, target_y, N, M;
void DFS(std::vector<std::vector<int>> &maze, int x, int y);

int main(){
    std::cin >> N >> M;

    int x, y;
    std::cin >> x >> y >> target_x >> target_y;

    std::vector<std::vector<int>> maze(N + 1, std::vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            std::cin >> maze[i][j];
        }
    }

    DFS(maze, x, y);

    if (maze[target_x][target_y] == -1){
        printf("Success!");
    }
    else {
        printf("Fail!");
    }

    return 0;
}

void DFS(std::vector<std::vector<int>> &maze, int x, int y){
    // exceed boarder
    if (x == 0 || y == 0 || x > N || y > M){
        return;
    }

    // cannot go through or visited
    if (maze[x][y] == 0 || maze[x][y] == -1){
        return;
    }

    maze[x][y] = -1; // mark current node as visited

    DFS(maze, x + 1, y); // down
    DFS(maze, x, y + 1); // right
    DFS(maze, x - 1, y); // up
    DFS(maze, x, y - 1); // left
}