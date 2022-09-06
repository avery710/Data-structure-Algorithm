#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#define MAX_SIZE 1009

int N, M, a, b;
std::string str1, str2;
std::vector<int> blocks[MAX_SIZE];
typedef std::pair<int, int> positions; /*first: col / second: which position in the col */
std::map<int, positions> pos_record;

//put all the elements above back
void clear(int& x){
    int from_col = pos_record[x].first;
    int pos = pos_record[x].second + 1;

    for (int i = pos; i < blocks[from_col].size(); i++){
        //move
        blocks[blocks[from_col][i]].push_back(blocks[from_col][i]);
        //change the pos_record map
        pos_record[blocks[from_col][i]].first = blocks[from_col][i];
        pos_record[blocks[from_col][i]].second = 0;
    }

    //delete
    blocks[from_col].erase(blocks[from_col].begin() + pos, blocks[from_col].end());
}

void move(int& x, int& y){
    int from_col = pos_record[x].first, to_col = pos_record[y].first;
    int from_pos = pos_record[x].second;

    for (int i = from_pos; i < blocks[from_col].size(); i++){
        //move
        blocks[to_col].push_back(blocks[from_col][i]);
        //change the pos_record map
        pos_record[blocks[from_col][i]].first = to_col;
        pos_record[blocks[from_col][i]].second = blocks[to_col].size() - 1;
    }

    //delete the elements that have already been moved (type: vector<int>)
    blocks[from_col].erase(blocks[from_col].begin() + from_pos, blocks[from_col].end());
}

int main(){
    // N個方塊, M筆操作
    std::cin >> N >> M;

    //initialize blocks and pos_record
    for (int i = 1; i <= N; i++){
        blocks[i].push_back(i);
        pos_record[i] = std::make_pair(i, 0);
    }

    //scan instructions 
    for (int i = 0; i < M; i++){
        std::cin >> str1 >> a >> str2 >> b;

        if (pos_record[a].first != pos_record[b].first){
            if (str1 == "move"){
                clear(a);
            }
            if (str2 == "onto"){
                clear(b);
            }
            move(a, b);
        }     
    }

    //print out 
    for (int i = 1; i <= N; i++){
        std::cout << i << ": ";

        //traverse through elements inside the vector
        for (int j = 0; j < blocks[i].size(); j++){
            std::cout << blocks[i][j] << ' ';
        }

        std::cout << std::endl;
    }
}