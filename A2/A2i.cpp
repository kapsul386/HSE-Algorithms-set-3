/*
#include <bits/stdc++.h>
using namespace std;


void insertionSort(vector<int>& arr, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > left && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

void merge(vector<int>& arr, size_t left, size_t mid, size_t right) {
    vector<int> tmp;
    tmp.reserve(right - left + 1);

    size_t i = left;
    size_t j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            tmp.push_back(arr[i++]);
        else
            tmp.push_back(arr[j++]);
    }

    while (i <= mid)  tmp.push_back(arr[i++]);
    while (j <= right) tmp.push_back(arr[j++]);

    for (size_t k = 0; k < tmp.size(); ++k)
        arr[left + k] = tmp[k];
}

void hybridMergeSort(vector<int>& arr, size_t left, size_t right) {
    if (right <= left) {
        return;
    }

    if (right - left + 1 <= 15) {
        insertionSort(arr, left, right);
        return;
    }

    size_t mid = left + (right - left) / 2;

    hybridMergeSort(arr, left, mid);
    hybridMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n > 0)
        hybridMergeSort(a, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }

    return 0;
}
*/
