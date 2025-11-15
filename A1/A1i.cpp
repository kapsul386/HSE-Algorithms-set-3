/*
#include <bits/stdc++.h>
using namespace std;

bool inside(double cx, double cy, double r, double x, double y) {
    double dx = x - cx;
    double dy = y - cy;
    return dx * dx + dy * dy <= r * r;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double x1, y1, r1;
    double x2, y2, r2;
    double x3, y3, r3;

    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;
    std::cin >> x3 >> y3 >> r3;

    double xmin = std::min({x1 - r1, x2 - r2, x3 - r3});
    double xmax = std::max({x1 + r1, x2 + r2, x3 + r3});
    double ymin = std::min({y1 - r1, y2 - r2, y3 - r3});
    double ymax = std::max({y1 + r1, y2 + r2, y3 + r3});

    double width = xmax - xmin;
    double height = ymax - ymin;
    double areaRect = width * height;

    const int SAMPLES = 4000000;

    mt19937 rng(123456);

    int hits = 0;
    for (int i = 0; i < SAMPLES; i++) {
        double rx = (double)rng() / static_cast<double>(std::mt19937::max());
        double ry = (double)rng() / static_cast<double>(std::mt19937::max());

        double x = xmin + rx * width;
        double y = ymin + ry * height;

        if (inside(x1, y1, r1, x, y) && inside(x2, y2, r2, x, y) && inside(x3, y3, r3, x, y)) {
            hits++;
            }
    }

    double result = (double)hits / SAMPLES * areaRect;

    std::cout << result;

    return 0;
}
*/
