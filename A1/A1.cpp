#include <bits/stdc++.h>
using namespace std;

bool inside(double cx, double cy, double r, double x, double y) {
    double dx = x - cx;
    double dy = y - cy;
    return dx * dx + dy * dy <= r * r;
}

int main() {
    double x1 = 1.0,   y1 = 1.0,   r1 = 1.0;
    double x2 = 1.5,   y2 = 2.0,   r2 = std::sqrt(5.0) / 2.0;
    double x3 = 2.0,   y3 = 1.5,   r3 = std::sqrt(5.0) / 2.0;

    double S_exact = 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;

    double xmin = std::min({x1 - r1, x2 - r2, x3 - r3});
    double xmax = std::max({x1 + r1, x2 + r2, x3 + r3});
    double ymin = std::min({y1 - r1, y2 - r2, y3 - r3});
    double ymax = std::max({y1 + r1, y2 + r2, y3 + r3});

    double wxmin = xmin;
    double wxmax = xmax;
    double wymin = ymin;
    double wymax = ymax;

    double nxmin = 0.8;
    double nxmax = 2.2;
    double nymin = 0.8;
    double nymax = 2.2;

    mt19937 rng(123456);
    std::ofstream fAreas("areas.csv");
    std::ofstream fErrors("relative_errors.csv");

    fAreas << "N,area_wide,area_narrow\n";
    fErrors << "N,rel_error_wide,rel_error_narrow\n";

    fAreas << std::fixed << std::setprecision(10);
    fErrors << std::fixed << std::setprecision(10);

    for (int N = 100; N <= 100000; N += 500) {
        int hits_wide = 0;
        for (int i = 0; i < N; i++) {
            double rx = (double)rng() / (double)mt19937::max();
            double ry = (double)rng() / (double)mt19937::max();

            double x = wxmin + rx * (wxmax - wxmin);
            double y = wymin + ry * (wymax - wymin);

            if (inside(x1, y1, r1, x, y) &&
                inside(x2, y2, r2, x, y) &&
                inside(x3, y3, r3, x, y)) {
                hits_wide++;
            }
        }
        double areaRectWide = (wxmax - wxmin) * (wymax - wymin);
        double area_wide = (double)hits_wide / N * areaRectWide;

        int hits_narrow = 0;
        for (int i = 0; i < N; i++) {
            double rx = (double)rng() / (double)mt19937::max();
            double ry = (double)rng() / (double)mt19937::max();

            double x = nxmin + rx * (nxmax - nxmin);
            double y = nymin + ry * (nymax - nymin);

            if (inside(x1, y1, r1, x, y) &&
                inside(x2, y2, r2, x, y) &&
                inside(x3, y3, r3, x, y)) {
                hits_narrow++;
            }
        }
        double areaRectNarrow = (nxmax - nxmin) * (nymax - nymin);
        double area_narrow = (double)hits_narrow / N * areaRectNarrow;

        double err_wide = std::fabs(area_wide - S_exact) / S_exact;
        double err_narrow = std::fabs(area_narrow - S_exact) / S_exact;

        fAreas  << N << "," << area_wide  << "," << area_narrow  << "\n";
        fErrors << N << "," << err_wide   << "," << err_narrow   << "\n";
    }

    return 0;
}
