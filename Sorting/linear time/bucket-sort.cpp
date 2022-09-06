#include <iostream>
#include <vector>
#include <algorithm>

void bucketSort(float a[], int n){
    // 1) Create n empty buckets
    std::vector<float> bucket[n];

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++){
				// 總個數 * a[i] : 因為a[i]每個都是0~1的數，可以解讀為比例，並將n等分
        int bi = n * a[i]; 
        bucket[bi].push_back(a[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++){
        std::sort(bucket[i].begin(), bucket[i].end());
    }

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < bucket[i].size(); j++){
            a[index++] = bucket[i][j];
        }
    }
}

int main(){
    float arr[] = { 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 };
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n);
 
    std::cout << "Sorted array is \n";
    for (int i = 0; i < n; i++){
        std::cout << arr[i] << " ";
    }

    return 0;
}