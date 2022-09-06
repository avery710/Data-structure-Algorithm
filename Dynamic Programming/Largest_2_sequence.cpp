#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main(){
    int n;
    std::cin >> n;

    int tmp;
    std::vector<int> arr;
    for (int i = 0; i < n; i++){
        std::cin >> tmp;
        arr.push_back(tmp);
    }

    // dp1 start from left, dp2 from right
    std::vector<int> dp1(n, 0), dp2(n, 0);
    dp1[0] = arr[0];
    dp2[n - 1] = arr[n - 1];

    for (int i = 1; i < n; i++){
        dp1[i] = std::max(dp1[i - 1] + arr[i], arr[i]);
        dp2[n - 1 - i] = std::max(dp2[n - i] + arr[n - 1 - i], arr[n - 1 - i]);
    }

    for (int i = n - 2; i >= 0; i--){
        dp2[i] = std::max(dp2[i], dp2[i + 1]);
    }

    int maxi_l = INT_MIN, ans = INT_MIN, maxi_r;
    for (int i = 0; i < n - 1; i++){
        maxi_l = std::max(maxi_l, dp1[i]);
        maxi_r = dp2[i + 1];

        ans = std::max(ans, maxi_l + maxi_r);
    }

    std::cout << ans;
    return 0;
}