#include <iostream>
#include <string>
#include <vector>

int partition(std::vector<double>& v, int left, int right){
    //find the middle of the three values
    double a = v[left];
    double b = v[(left + right) / 2];
    double c = v[right];
    double pivot = c;

    //ans: a 
    if (c > a && a > b || b > a && a > c){
        pivot = a;
        std::swap(v[left], v[right]);
    }
    //ans: b
    else if (a > b && b > c || c > b && b > a){
        pivot = b;
        std::swap(v[(left + right) / 2], v[right]);
    }

    int i = left - 1;
    for (int j = left; j <= right - 1; j++){
        if (v[j] > pivot){
            i++;
            std::swap(v[j], v[i]);
        }
    }
    std::swap(v[++i], v[right]);
    return i;
}

int quickSelect(std::vector<double>& v, int left, int right, int target){
    if (left == right){
        return left;
    }

    //pick a random pivot
    int cur_pivot = partition(v, left, right);

    int pivot_rank = cur_pivot - left + 1;

    if (pivot_rank == target){
        return cur_pivot;
    }
    else if (pivot_rank < target){
        //return right part
        return quickSelect(v, cur_pivot + 1, right, target - pivot_rank);
    }
    else {
        //return left part
        return quickSelect(v, left, cur_pivot - 1, target);
    }
}

int main(){
    int N, K; // 共N杯調酒，濃度第K高
    std::cin >> N >> K;

    int lime, syrup, liquor;
    std::string name;

    //for storing datas
    std::vector<std::pair<double, std::string>> list;
    //for sorting (use index & concentation only)
    std::vector<double> v;

    for (int i = 0; i < N; i++){
        std::cin >> lime >> syrup >> liquor >> name;
        double concentration = (double)liquor / (double)(lime + syrup + liquor);

        list.push_back(std::make_pair(concentration, name));
        v.push_back(concentration);
    }

    int index = quickSelect(v, 0, N - 1, K);

    for (int i = 0; i < N; i++){
        if (v[index] == list[i].first){
            std::cout << list[i].second;
            break;
        }
    }

    return 0;
}