#include "NumericalDifferentiator.h"
#include <math.h>

void NumericalDifferentiator::createValueTable() {
    valuesTable.clear();

    for (int stepIdx = 0; stepIdx <= stepCount; ++stepIdx) {
        double argument = begin + step * stepIdx;
        valuesTable.push_back(std::make_pair(argument, func(argument)));
    }
}

void NumericalDifferentiator::printTable(std::ostream & output) const {
    std::ios::fmtflags format(output.flags());

    output.setf(std::ios::fixed);
    output.precision(10);
    
    output << "\nArgument\t\tValue\t\t\tFirst derivative\tFirst der error\t\tSecond derivative\tSecond der error\n";

    int pairIndex = 0;
    for (auto const& pair : valuesTable) {
        double firstDerivative = calculateFirstDerivative(pairIndex);
        double firstDerivativeError = abs(firstDerivative - funcFirstDeriv(pair.first));

        double secondDerivative = calculateSecondDerivative(pairIndex);
        double secondDerivativeError = abs(secondDerivative - funcSecondDeriv(pair.first));

        output << pair.first << "\t\t" << pair.second << "\t\t" << firstDerivative << "\t\t"  << firstDerivativeError << "\t\t";
        if (pairIndex == 0 || pairIndex == stepCount) {
            output << "-----------\t\t" << "" "-----------\n";
        } else {
            output << secondDerivative << "\t\t" << secondDerivativeError << '\n';
        }
        ++pairIndex;
    }

    //output << "---------------------------------------------------------------\n";
    output.flags(format);
}

double NumericalDifferentiator::calculateFirstDerivative(int argIndex) const {
    if (argIndex == 0) {
        return (-3*valuesTable[argIndex].second + 4*valuesTable[argIndex + 1].second - valuesTable[argIndex + 2].second)
                / (2 * step);
    } else if (argIndex == stepCount) {
        return ( 3*valuesTable[argIndex].second - 4*valuesTable[argIndex - 1].second + valuesTable[argIndex - 2].second)
                / (2 * step);
    }

    return (valuesTable[argIndex + 1].second - valuesTable[argIndex - 1].second) / (2 * step);
}

double NumericalDifferentiator::calculateSecondDerivative(int argIndex) const {
    return (valuesTable[argIndex + 1].second - 2*valuesTable[argIndex].second + valuesTable[argIndex - 1].second)
            / (step * step);
}

void NumericalDifferentiator::setParams(double begin, double step, unsigned int stepCount) {
    this->begin = begin;
    this->step = step;
    this->stepCount = stepCount;
    createValueTable();
}