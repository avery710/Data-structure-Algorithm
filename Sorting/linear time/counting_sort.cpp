#include <iostream>
#include <vector>
#include <algorithm> //max_element(), min_element()

void countSort(std::vector<int>& a){
    //range of values in array
    int max = *std::max_element(a.begin(), a.end());
    int min = *std::min_element(a.begin(), a.end());
    int range = max - min + 1; //差要加1才為個數

    std::vector<int> counter(range), output(a.size());

    //start counting
    for (int i = 0; i < a.size(); i++){
        counter[a[i] - min]++;
    }

    //accumulate
    for (int i = 1; i < range; i++){
        counter[i] += counter[i - 1];
    }

    //update in output
    for (int i = a.size() - 1; i >= 0; i--){
        int value = a[i];
        output[counter[value - min] - 1] = value;
        counter[value - min]--;
    }

    //dupicate output to the original array
    for (int i = 0; i < a.size(); i++){
        a[i] = output[i];
    }
}

int main(){
    std::vector<int> arr{ -5, -10, 0, -3, 8, 5, -1, 10 };
    countSort(arr);

    //print array
    for (int i = 0; i < arr.size(); i++){
        printf("%d ", arr[i]);
    }

    return 0;
}