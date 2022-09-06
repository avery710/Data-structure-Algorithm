#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

int select(std::vector<int>& a, int k){ //第k大的數
    int n = a.size();

    // recursion boundary condition
    if (n == 1){
        return a[0];
    }

    // Step 1. separate into several piles (5 int/pile)
    int piles = (int)ceil((double)a.size()/5);
    std::vector<int> aa[piles];

    int pile_count = 0, count = 0, j = n;
    while (count < n){
        if (j / 5 > 0){
            for (int i = 0; i < 5; i++){
                aa[pile_count].push_back(a[count++]);
            }
            j -= 5;
        }
        else {
            while (j > 0){
                aa[pile_count].push_back(a[count++]);
                j--;
            }
        }

        std::sort(aa[pile_count].begin(), aa[pile_count].end());
        pile_count++;
    }

    // Step 2. pick out medians
    std::vector<int> medians;
    for (int i = 0; i < piles; i++){
        int middle_idx = (int)ceil((double)aa[i].size()/2) - 1;
        medians.push_back(aa[i][middle_idx]);
    }

    // Step 3. select median of medians
    int pivot = select(medians, (int)ceil((double)medians.size()/2));
    std::cout << "pivot: " << pivot << std::endl;

    // Step 4. use pivot partition
    std::vector<int> small, big;
    for (int i = 0; i < n; i++){
        if (a[i] < pivot){
            small.push_back(a[i]);
        }
        else if (a[i] > pivot){
            big.push_back(a[i]);
        }
    }

    // Step 5. use small & big call recursion
    if (k <= small.size()){
        return select(small, k);
    }
    else if (k > n - big.size()){
        return select(big, k - n + big.size());
    }
    else {
        return pivot;
    }
}


int main(){
    int n;
    std::cin >> n;

    std::vector<int> arr;
    int tmp;
    for (int i = 1; i <= n; i++){
        std::cin >> tmp;
        arr.push_back(tmp);
    }

    int middle_idx = (int)ceil((double)arr.size()/2);
    int ans = select(arr, middle_idx);
    std::cout << "answer: " << ans << std::endl;
    
    return 0;
}