#pragma once

#include <vector>
#include <ostream>
#include <functional>

class NumericalDifferentiator {
private:
    using Table = std::vector<std::pair<double, double>>;
    using Function = std::function<double(double)>;

    double begin;
    double step;
    unsigned int stepCount;
    Function func;
    Function funcFirstDeriv;
    Function funcSecondDeriv;

    Table valuesTable;

    void createValueTable();
    double calculateFirstDerivative(int argumentIndex) const;
    double calculateSecondDerivative(int argumentIndex) const;
public:
    NumericalDifferentiator(double begin, double step, unsigned int stepCount, Function func, Function funcFirstDeriv, Function funcSecondDeriv)
            : begin(begin), step(step), stepCount(stepCount), func(func), funcFirstDeriv(funcFirstDeriv), funcSecondDeriv(funcSecondDeriv) {
        createValueTable();
    }

    void printTable(std::ostream & output) const;
    void setParams(double begin, double step, unsigned int stepCount);
};