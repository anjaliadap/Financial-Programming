#pragma once
#include <vector>

/**
 * @brief Linearly interpolates y(x) for a given x, based on tabulated (xs, ys).
 *
 * The function assumes:
 *  - xs.size() > 0  (cannot be empty)
 *  - xs and ys have the same size
 *  - xs is strictly increasing (sorted ascending)
 *
 * If x is less than xs.front(), returns ys.front().
 * If x is greater than xs.back(), returns ys.back().
 * Otherwise, performs linear interpolation between neighboring points.
 *
 * @param x   Query x value.
 * @param xs  Vector of x-coordinates (must be ordered).
 * @param ys  Vector of y-coordinates (same size as xs).
 * @return Interpolated y value at x.
 */

double interpolate(double x, const std::vector<double>& xs, const std::vector<double>& ys);
