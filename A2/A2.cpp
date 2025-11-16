#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

void insertionSort(vector<int> &arr, size_t left, size_t right) {
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

void merge(vector<int> &arr, size_t left, size_t mid, size_t right) {
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
    while (i <= mid) tmp.push_back(arr[i++]);
    while (j <= right) tmp.push_back(arr[j++]);

    for (size_t k = 0; k < tmp.size(); ++k)
        arr[left + k] = tmp[k];
}

void mergeSort(vector<int> &arr, size_t left, size_t right) {
    if (left >= right) return;
    size_t mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void hybridMergeSort(vector<int> &arr, size_t left, size_t right) {
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


class ArrayGenerator {
public:
    ArrayGenerator(size_t maxN, int maxVal)
        : maxN_(maxN),
          rnd_(maxN),
          rng_(123456) {
        uniform_int_distribution<int> dist(0, maxVal);

        for (size_t i = 0; i < maxN_; ++i) {
            rnd_[i] = dist(rng_);
        }

        rev_ = rnd_;
        sort(rev_.begin(), rev_.end(), greater<int>());

        almost_ = rnd_;
        sort(almost_.begin(), almost_.end());
        size_t swaps = maxN_ / 100;
        if (swaps < 1) swaps = 1;
        if (swaps > 1000) swaps = 1000;
        uniform_int_distribution<size_t> pos(0, maxN_ - 1);
        for (size_t i = 0; i < swaps; ++i) {
            size_t i1 = pos(rng_);
            size_t i2 = pos(rng_);
            swap(almost_[i1], almost_[i2]);
        }
    }

    vector<int> getRandomPrefix(size_t n) const {
        return vector<int>(rnd_.begin(), rnd_.begin() + n);
    }

    vector<int> getReversedPrefix(size_t n) const {
        return vector<int>(rev_.begin(), rev_.begin() + n);
    }

    vector<int> getAlmostPrefix(size_t n) const {
        return vector<int>(almost_.begin(), almost_.begin() + n);
    }

private:
    size_t maxN_;
    vector<int> rnd_;
    vector<int> rev_;
    vector<int> almost_;
    mt19937 rng_;
};


class SortTester {
public:
    explicit SortTester(int runs) : runs_(runs) {
    }

    long long measureMerge(const vector<int> &base) const {
        size_t n = base.size();
        long long total = 0;

        for (int r = 0; r < runs_; ++r) {
            vector<int> a = base;
            auto t1 = high_resolution_clock::now();
            mergeSort(a, 0, n - 1);
            auto t2 = high_resolution_clock::now();
            total += duration_cast<microseconds>(t2 - t1).count();
        }
        return total / runs_;
    }

    long long measureHybrid(const vector<int> &base) const {
        size_t n = base.size();
        long long total = 0;

        for (int r = 0; r < runs_; ++r) {
            vector<int> a = base;
            auto t1 = high_resolution_clock::now();
            hybridMergeSort(a, 0, n - 1);
            auto t2 = high_resolution_clock::now();
            total += duration_cast<microseconds>(t2 - t1).count();
        }
        return total / runs_;
    }

private:
    int runs_;
};


int main() {
    const size_t MAXN = 100000;
    const size_t MINN = 500;
    const size_t STEP = 100;
    const int MAXVAL = 6000;
    const int RUNS = 5;

    ArrayGenerator gen(MAXN, MAXVAL);
    SortTester tester(RUNS);

    ofstream fileRandom("random_arrays.csv");
    ofstream fileReversed("reversed_arrays.csv");
    ofstream fileAlmost("almost_sorted_arrays.csv");

    auto write_header = [](ofstream &f) {
        f << "n,merge_us,hybrid_us\n";
    };

    write_header(fileRandom);
    write_header(fileReversed);
    write_header(fileAlmost);

    for (size_t n = MINN; n <= MAXN; n += STEP) {
        vector<int> arrR = gen.getRandomPrefix(n);
        vector<int> arrRev = gen.getReversedPrefix(n);
        vector<int> arrAlm = gen.getAlmostPrefix(n);

        long long tMergeR = tester.measureMerge(arrR);
        long long tHybridR = tester.measureHybrid(arrR);
        long long tMergeRev = tester.measureMerge(arrRev);
        long long tHybridRev = tester.measureHybrid(arrRev);
        long long tMergeAlm = tester.measureMerge(arrAlm);
        long long tHybridAlm = tester.measureHybrid(arrAlm);

        fileRandom << n << "," << tMergeR << "," << tHybridR << "\n";
        fileReversed << n << "," << tMergeRev << "," << tHybridRev << "\n";
        fileAlmost << n << "," << tMergeAlm << "," << tHybridAlm << "\n";
    }

    return 0;
}
