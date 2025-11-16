#include <bits/stdc++.h>
using namespace std;
using namespace chrono;


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


void quickSortStandard(long long A[], int left, int right, mt19937 &rng) {
    while (left < right) {
        int i = left;
        int j = right;
        uniform_int_distribution<int> dist(left, right);
        long long pivot = A[dist(rng)];

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
                quickSortStandard(A, left, j, rng);
            }
            left = i;
        } else {
            if (i < right) {
                quickSortStandard(A, i, right, rng);
            }
            right = j;
        }
    }
}


class ArrayGenerator {
public:
    ArrayGenerator(size_t maxN, int maxVal)
        : maxN_(maxN),
          random_(maxN),
          rng_(123456) {
        uniform_int_distribution<int> dist(0, maxVal);

        for (size_t i = 0; i < maxN_; ++i) {
            random_[i] = dist(rng_);
        }

        reversed_ = random_;
        sort(reversed_.begin(), reversed_.end(), greater<long long>());

        almost_ = random_;
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

    vector<long long> getRandom(size_t n) const {
        return vector<long long>(random_.begin(), random_.begin() + n);
    }

    vector<long long> getReversed(size_t n) const {
        return vector<long long>(reversed_.begin(), reversed_.begin() + n);
    }

    vector<long long> getAlmost(size_t n) const {
        return vector<long long>(almost_.begin(), almost_.begin() + n);
    }

private:
    size_t maxN_;
    vector<long long> random_;
    vector<long long> reversed_;
    vector<long long> almost_;
    mt19937 rng_;
};

class SortTester {
public:
    explicit SortTester(int runs) : runs_(runs) {}

    long long measureQuick(const vector<long long> &base) const {
        size_t n = base.size();
        long long total = 0;

        mt19937 rng(123456);

        for (int r = 0; r < runs_; ++r) {
            vector<long long> a = base;
            auto t1 = high_resolution_clock::now();
            quickSortStandard(a.data(), 0, (int)n - 1, rng);
            auto t2 = high_resolution_clock::now();
            total += duration_cast<microseconds>(t2 - t1).count();
        }

        return total / runs_;
    }

    long long measureHybrid(const vector<long long> &base) const {
        size_t n = base.size();
        long long total = 0;

        for (int r = 0; r < runs_; ++r) {
            vector<long long> a = base;
            int depthLimit = 2 * static_cast<int>(log2(max<size_t>(n, 1)));
            auto t1 = high_resolution_clock::now();
            hybridQuick(a.data(), 0, (int)n - 1, depthLimit);
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

    ofstream fRandom("quick_random.csv");
    ofstream fReversed("quick_reversed.csv");
    ofstream fAlmost("quick_almost.csv");

    auto header = [](ofstream &f) {
        f << "n,quick_us,hybrid_us\n";
    };

    header(fRandom);
    header(fReversed);
    header(fAlmost);

    for (size_t n = MINN; n <= MAXN; n += STEP) {
        auto arrR = gen.getRandom(n);
        auto arrRev = gen.getReversed(n);
        auto arrAlm = gen.getAlmost(n);

        long long qR = tester.measureQuick(arrR);
        long long hR = tester.measureHybrid(arrR);

        long long qRev = tester.measureQuick(arrRev);
        long long hRev = tester.measureHybrid(arrRev);

        long long qAlm = tester.measureQuick(arrAlm);
        long long hAlm = tester.measureHybrid(arrAlm);

        fRandom << n << "," << qR << "," << hR << "\n";
        fReversed << n << "," << qRev << "," << hRev << "\n";
        fAlmost << n << "," << qAlm << "," << hAlm << "\n";
    }

    return 0;
}
