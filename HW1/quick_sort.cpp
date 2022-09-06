#include <iostream>
#include <algorithm>

int partition(int a[], int left, int right){
    int pivot = a[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++){
        if (a[j] <= pivot){
            i++;
            std::swap(a[j], a[i]);
        }
    }
    std::swap(a[++i], a[right]);
    return i;
}

void quickSort(int a[], int left, int right){
    if (left < right){
        int pi = partition(a, left, right);

        quickSort(a, left, pi - 1);
        quickSort(a, pi + 1, right);
    }
}

int main(){
    int arr[] = { 9, 3, 4, 2, 1, 8 };
    int n = 6;
 
    quickSort(arr, 0, n - 1);
 
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
 
    return 0;
}