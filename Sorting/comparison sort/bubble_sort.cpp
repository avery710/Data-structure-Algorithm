#include <iostream>

void swap(int& a, int& b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

//optimization: add a bool into bubble sort!
void bubble_sort(int a[], int n){
    bool swapped;

    for (int i = 0; i < n - 1; i++){
        swapped = false;

        for (int j = 0; j < n - 1 - i; j++){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false){
            break;
        }
    }
}

int main(){
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(int);
    bubble_sort(arr, n);

    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}