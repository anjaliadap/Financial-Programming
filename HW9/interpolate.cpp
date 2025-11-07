#include "interpolate.h"
#include <stdexcept>
#include <algorithm>

// Helper: find first index lb s.t. x <= xs[lb]
static size_t lower_bound_index(double x, const std::vector<double>& xs) {
    if (x > xs.back()) return xs.size();
    for (size_t i = 0; i < xs.size(); ++i) {
        if (x <= xs[i]) return i;
    }
    return xs.size(); // just in case
}

// Helper: given lower bound index, interpolate y(x)
static double interpolate_lb(double x, size_t lb,
                             const std::vector<double>& xs,
                             const std::vector<double>& ys) {
    if (lb == 0) return ys.front();
    if (lb >= ys.size()) return ys.back();

    double x0 = xs[lb - 1];
    double x1 = xs[lb];
    double y0 = ys[lb - 1];
    double y1 = ys[lb];

    double slope = (y1 - y0) / (x1 - x0);
    return y0 + slope * (x - x0);
}

double interpolate(double x, const std::vector<double>& xs, const std::vector<double>& ys) {
    if (xs.empty()) throw std::invalid_argument("xs cannot be empty");
    if (xs.size() != ys.size()) throw std::invalid_argument("xs and ys must have same size");
    // assume xs is sorted
    size_t lb = lower_bound_index(x, xs);
    return interpolate_lb(x, lb, xs, ys);
}
