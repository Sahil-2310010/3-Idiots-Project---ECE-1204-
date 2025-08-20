#include <iostream>
using namespace std;


template <typename T>
int findMaxIndex(T arr[], int size) {
    if (size <= 0) return -1;
    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int main() {
    int intArr[] = {10, 50, 20, 70, 90};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Max index in intArr: " << findMaxIndex(intArr, intSize) << endl;

    double doubleArr[] = {2.5, 3.5, 8.9, 6.4};
    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
    cout << "Max index in doubleArr: " << findMaxIndex(doubleArr, doubleSize) << endl;

    char charArr[] = {'A', 'B', 'C', 'D'};
    int charSize = sizeof(charArr) / sizeof(charArr[0]);
    cout << "Max index in charArr: " << findMaxIndex(charArr, charSize) << endl;

    string strArr[] = {"apple", "mango", "banana", "cherry"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    cout << "Max index in strArr: " << findMaxIndex(strArr, strSize) << endl;

    return 0;
}
