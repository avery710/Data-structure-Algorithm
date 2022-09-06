#include <iostream>

//swap function
void swap(int& a, int& b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void selectionSort(int a[], int n){
    int tmp_pos = -1, min_index;

    for (int i = 0; i < n - 1; i++){
        min_index = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[min_index]){
                tmp_pos = j;
            }
        }
        if (tmp_pos >= 0){
            swap(a[i], a[tmp_pos]);
        }
    }
}

int main(){
    int arr[] = {64, 25, 12, 22, 11}; 
    int n = sizeof(arr)/ sizeof(int);
    selectionSort(arr, n);

    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}