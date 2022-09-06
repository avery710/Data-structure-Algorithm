#include <iostream>
#include <vector>
#include <string>
#include <map>

std::vector<int> pos_record_chart;
std::map<int, std::vector<int> > map_blocks;

using iterator = std::vector<int>::iterator;

// find a or b
iterator find_an_element(int &target)
{
    int pos = pos_record_chart[target];

    for (iterator it = map_blocks[pos].begin(); it != map_blocks[pos].end(); it++)
    {
        if (target == (*it))
        {
            return it;
        }
    }
}

// put back all the blocks above
void move_onto(iterator start, int &key)
{
    int temp;
    for (std::vector<int>::iterator it = map_blocks[key].end(); it != start; it--)
    {
        temp = map_blocks[key].back();
        map_blocks[temp].push_back(temp);
        pos_record_chart[temp] = temp;
        map_blocks[key].pop_back();
    }
}

// move the stacks together
void pile_over(iterator start, int &from_pos, int &to_pos)
{
    int temp;
    for (std::vector<int>::iterator it = map_blocks[from_pos].end(); it != start; it--)
    {
        temp = map_blocks[from_pos].back();
        map_blocks[to_pos].push_back(temp);
        pos_record_chart[temp] = to_pos;

        map_blocks[from_pos].pop_back();
    }
}

int main()
{
    // N個方塊, M筆操作
    int N, M;
    std::cin >> N >> M;

    int from, to;
    std::string first_action, second_action;

    // Initialize arraylist
    pos_record_chart.reserve(N + 1);

    // assign values to map and vector
    for (int i = 1; i <= N; i++)
    {
        pos_record_chart[i] = i; // can I write this in constructor??

        map_blocks[i].reserve(N);
        map_blocks[i].push_back(i);
    }

    for (int i = 0; i < M; i++)
    {
        std::cin >> first_action >> from >> second_action >> to;

        if (first_action == "move")
        {
            iterator a = find_an_element(from);
            move_onto(a, pos_record_chart[from]);

            // move a onto b
            if (second_action == "onto")
            {
                iterator b = find_an_element(to);
                move_onto(b, pos_record_chart[to]);
                pile_over(a, pos_record_chart[from], pos_record_chart[to]);
            }
            else
            {
                // move a over b
                pile_over(a, pos_record_chart[from], pos_record_chart[to]);
            }
        }
        // pile
        else
        {
            iterator a = find_an_element(from);
            // pile a over b
            if (second_action == "over")
            {
                pile_over(a, pos_record_chart[from], pos_record_chart[to]);
            }
            // pile a onto b
            else
            {
                iterator b = find_an_element(to);
                move_onto(b, pos_record_chart[to]);
                pile_over(a, pos_record_chart[from], pos_record_chart[to]);
            }
        }
    }

    // print out
    for (int i = 1; i <= N; i++)
    {
        std::cout << i << ": ";

        // use iterator inside to loop
        iterator it_inner;
        for (it_inner = map_blocks[i].begin(); it_inner != map_blocks[i].end(); ++it_inner)
        {
            std::cout << *it_inner << ' ';
        }

        std::cout << std::endl;
    }
}