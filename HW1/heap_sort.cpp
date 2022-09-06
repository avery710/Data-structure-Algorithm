#include <iostream>

void heapify(int a[], int n, int parent_idx){
    int lchild_idx = parent_idx * 2 + 1;
    int rchild_idx = parent_idx * 2 + 2;
    int largest_idx = parent_idx;

    //check whether the index is valid
    if (lchild_idx < n && a[lchild_idx] > a[largest_idx]){
        largest_idx = lchild_idx;
    }

    if (rchild_idx < n && a[rchild_idx] > a[largest_idx]){
        largest_idx = rchild_idx;
    }

    //if the largest index has changed, meaning that the value needs to be swapped
    if (largest_idx != parent_idx){
        std::swap(a[parent_idx], a[largest_idx]);
        
        heapify(a, n, largest_idx);
    }
}

void heapSort(int a[], int n){
    //build max heap
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }

    //pop out the max num, and fill the blank with the last node
    for (int i = n - 1; i > 0; i--){
        std::swap(a[0], a[i]);
        heapify(a, i, 0);
    }

}

int main(){
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    heapSort(arr, n);
 
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}