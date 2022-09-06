#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n;
    std::cin >> n;

    std::vector<int> a(n, 0);
    for (int i = 0; i < n; i++){
        std::cin >> a[i];
    }

    // i: pivot num
    std::vector<int> dp1(n, 1);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < i; ++j){
            if (a[i] > a[j] && dp1[i] < dp1[j] + 1){
                dp1[i] = dp1[j] + 1;
            } 
        }
    }

    std::vector<int> dp2(n, 1);
    for (int i = n - 1; i >= 0; i--){
        for (int j = n - 1; j > i; j--){
            if (a[i] > a[j] && dp2[i] < dp2[j] + 1){
                dp2[i] = dp2[j] + 1;
            }
        }
    }

    int ans = 1;
    for (int i = 0; i < n; i++){
        ans = std::max(ans, dp1[i] + dp2[i]);
    }
    
    std::cout << n - (ans - 1);
    return 0;
}