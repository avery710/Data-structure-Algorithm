#include <iostream>

void countSort(int a[], int n, int exp){
    int output[n];
    int counter[10] = {0};

    for (int i = 0; i < n; i++){
        counter[(a[i] / exp) % 10]++;
    }

    //accumulate ++ in counter
    for (int i = 1; i < 10; i++){
        counter[i] += counter[i - 1];
    }

    for (int i = n - 1; i >= 0; i--){
        output[counter[(a[i] / exp) % 10] - 1] = a[i];
        counter[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++){
        a[i] = output[i];
    }
}

void radixSort(int a[], int n){
    //find max num
    int max = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > max){
            max = a[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10){
        countSort(a, n, exp);
    }
}

int main(){
    int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);

    radixSort(arr, n);

    //print the array
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}