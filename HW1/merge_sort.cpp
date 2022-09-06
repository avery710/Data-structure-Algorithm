#include <iostream>

int tmp[1000];

void mergeSort(int a[], int tmp[], int left, int mid, int right);

//use recursion to divide index
void divide(int a[], int left, int right){
    if (right > left){
        int mid = (left + right) / 2;

        divide(a, left, mid);
        divide(a, mid + 1, right);

        mergeSort(a, tmp, left, mid, right);
    }
}

void mergeSort(int a[], int tmp[], int left, int mid, int right){
    int i = left;
    int j = (left + right) / 2 + 1;
    int k = left;

    while (i <= mid && j <= right){
        if (a[i] <= a[j]){
            tmp[k++] = a[i++];
        }
        //a[i] > a[j]
        else {
            tmp[k++] = a[j++];
        }
    }

    //dupicate the rest of left or right part
    while (i <= mid){
        tmp[k++] = a[i++];
    }
    while (j <= right){
        tmp[k++] = a[j++];
    }

    for (int x = left; x <= right; x++){
        a[x] = tmp[x];
    }
}

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    divide(arr, 0, arr_size - 1);
  
    std::cout << "\nSorted array is \n";
    for (int i = 0; i < arr_size; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}