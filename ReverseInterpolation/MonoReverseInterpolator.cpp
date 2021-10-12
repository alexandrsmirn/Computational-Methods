#include "MonoReverseInterpolator.h"
#include "NewtonPolynom.h"

void MonotoneReverseInterpolator::invertTable() {
    for (auto & pair : this->interpolationTable) {
        std::swap(pair.first, pair.second);
    }
}

std::vector<double> MonotoneReverseInterpolator::getArguments(double functionValue, int degree) const {
    return std::vector(1, getInterpolatedValue(functionValue, degree));
}