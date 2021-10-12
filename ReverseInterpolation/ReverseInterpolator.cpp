#include "ReverseInterpolator.h"
#include <functional>

#include "../NonLinearEquations/EquationSolver.h"

std::vector<double> ReverseInterpolator::getArguments(double functionValue, int degree) const {
    auto const function = [degree, functionValue, this](double argument) { return this->getInterpolatedValue(argument, degree) - functionValue; };

    std::vector<Segment> const separatedRoots = getSeparatedRoots(begin, end, splitCount, function);
    std::vector<double> result;

    for (auto const& segment : separatedRoots) {
        double const currentRoot = secantMethod(segment, eps, function);
        result.push_back(currentRoot);
    }

    return result;
}
