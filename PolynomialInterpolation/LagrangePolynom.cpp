#include "LagrangePolynom.h"

double LagrangePolynom::calculateFundamentalPoly(double argument, int pointNumber, Table const& sortedInterpolationTable) const {
    double result = 1;
    double const point = sortedInterpolationTable[pointNumber].first;

    for (auto const& pair : sortedInterpolationTable) {
        if (pair.first != point) {
            result *= (argument - pair.first) / (point - pair.first);
        }
    }
    return result;
}

double LagrangePolynom::getInterpolatedValue(double argument, int degree) const {
    Table const sortedInterpolationTable = createSortedInterpolationTable(argument, degree);

    int pointNumber = 0;
    double result = 0;

    for (auto const& pair : sortedInterpolationTable) {
        result += calculateFundamentalPoly(argument, pointNumber++, sortedInterpolationTable) * pair.second;
    }

    return result;
}
