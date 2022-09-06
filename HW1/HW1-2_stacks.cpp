#include <algorithm> //std::set_union, std::set_intersection, std::sort
#include <iostream> //std::cin >>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>

std::vector<std::set<int> > vec;
std::map<std::set<int>, int> map;
std::stack<int> stk;
std::string str;
int N;

inline int get_id(std::set<int> s){
    //if set s has already been stored in the map & vec, return the "id"
    //use map to search, cuz the key(string) is unique
    if (map.find(s) != map.end()){
        return map[s];
    }

    //else add in map & vec
    //first add in vec, cuz the id in vector is unique
    vec.push_back(s);
    return (map[s] = vec.size() - 1);
}

int main(){
    std::cin >> N;
    for (int i = 0; i < N; i++){
        std::cin >> str;

        if (str == "PUSH"){
            //push an empty set into it
            int id = get_id(std::set<int>());
            stk.push(id);
        }
        else if (str == "DUP"){
            stk.push(stk.top());

        }

        else {
            std::set<int> tmp, x, y;
            x = vec[stk.top()];
            stk.pop();
            y = vec[stk.top()];
            stk.pop();

            if (str == "UNION"){
                set_union(x.begin(), x.end(), y.begin(), y.end(), inserter(tmp, tmp.begin()));
            }
            else if (str == "INTERSECT"){
                set_intersection(x.begin(), x.end(), y.begin(), y.end(), inserter(tmp, tmp.begin()));
            }
            else if (str == "ADD"){
                tmp = y;
                tmp.insert(map[x]); //type of map[x] : int
            }
            //push the new element into the stack: get_id first!
            stk.push(get_id(tmp));
        }
        printf("%d\n", (int)vec[stk.top()].size()); //type of vec[].size() : set<int>
    }
}