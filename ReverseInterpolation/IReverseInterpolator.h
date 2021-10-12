#pragma once

#include<vector>

class IReverseInterpolator {
public:
    virtual std::vector<double> getArguments(double functionValue, int degree) const = 0;
    virtual ~IReverseInterpolator() {};
};
