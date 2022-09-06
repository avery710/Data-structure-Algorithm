#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main(){
    int N;
    std::cin >> N;

    std::vector<int> arr;
    int tmp;
    for (int i = 0; i < N; i++){
        std::cin >> tmp;
        arr.push_back(tmp);
    }

    std::vector<int> dp(arr.size(), 0);
    //dp[0] = std::max(0, arr[0]);
    dp[0] = arr[0];

    int maxi_sum = dp[0];
    int start = 0, end = 0;

    for (int i = 1; i < arr.size(); i++){
        dp[i] = std::max(dp[i - 1] + arr[i], arr[i]);

        maxi_sum = std::max(maxi_sum, dp[i]);
        if (maxi_sum == dp[i]){
            end = i;
        }
    }

    start = end;
    while (start >= 1 && dp[start] - arr[start] == dp[start - 1]){
        start--;
    }

    std::cout << maxi_sum << ' ' << start + 1 << ' ' << end + 1;
    return 0;
}