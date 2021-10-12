#pragma once

class IPolynomCalculator {
public:
    virtual double getInterpolatedValue(double argument, int degree) = 0;
    virtual ~IPolynomCalculator() {};
};