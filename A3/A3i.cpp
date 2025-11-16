/*
#include <bits/stdc++.h>
using namespace std;


void insertionSort(long long A[], int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        long long key = A[i];
        int j = i - 1;
        while (j >= left && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

void heapify(long long A[], int heapN, int i) {
    int largest = i;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heapN && A[l] > A[largest]) largest = l;
        if (r < heapN && A[r] > A[largest]) largest = r;

        if (largest == i) break;
        swap(A[i], A[largest]);
        i = largest;
    }
}

void buildMaxHeap(long long A[], int heapN) {
    for (int i = heapN / 2 - 1; i >= 0; --i)
        heapify(A, heapN, i);
}

void heapSort(long long A[], int heapN) {
    buildMaxHeap(A, heapN);
    for (int end = heapN - 1; end > 0; --end) {
        swap(A[0], A[end]);
        heapify(A, end, 0);
    }
}

void heapSortSegment(long long A[], int left, int right) {
    int len = right - left + 1;
    heapSort(A + left, len);
}

void hybridQuick(long long A[], int left, int right, int depthLimit) {
    while (left < right) {
        int len = right - left + 1;

        if (len < 16) {
            insertionSort(A, left, right);
            return;
        }
        if (depthLimit == 0) {
            heapSortSegment(A, left, right);
            return;
        }
        --depthLimit;
        int i = left;
        int j = right;
        long long pivot = A[(right + left) / 2];

        while (i <= j) {
            while (A[i] < pivot) ++i;
            while (A[j] > pivot) --j;
            if (i <= j) {
                swap(A[i], A[j]);
                ++i;
                --j;
            }
        }

        if (j - left < right - i) {
            if (left < j) {
                hybridQuick(A, left, j, depthLimit);
            }
            left = i;
        } else {
            if (i < right) {
                hybridQuick(A, i, right, depthLimit);
            }
            right = j;
        }
    }
}

int main() {
    int n = 0;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int depthLimit = 2 * static_cast<int>(log2(n));
    hybridQuick(a.data(), 0, n - 1, depthLimit);

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
*/
