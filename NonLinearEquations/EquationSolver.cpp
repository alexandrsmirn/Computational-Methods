#include "EquationSolver.h"

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <math.h>

using Function = std::function<double(double)>;

void printResult(Segment const& segment, int numIterations, double result, Function function) {
    std::cout << "Raw approximaton: (" << segment.begin << ", " << segment.end << ")\n";
    std::cout << "Number of iterations: " << numIterations << "\n";
    std::cout << "Approximate solution: " << result << "\n";
    std::cout << "Solution residual: " << abs(function(result)) << "\n";
}

std::vector<Segment> getSeparatedRoots(int A, int B, int splitCount, Function function) {
    std::vector<Segment> segments;

    double splitLength = (double) (B - A) / splitCount;
 
    double position = A + splitLength;
    double previousResult = function(A);

    while (position <= B) {
        double result = function(position);

        if (result * previousResult <= 0) {
            segments.emplace_back(position - splitLength, position);
        }
    
        previousResult = result;
        position += splitLength;
    }

    return segments;
}

double bisectionMethod(Segment const& segment, double eps, Function function) {
    double currBegin = segment.begin;
    double currEnd = segment.end;

    int numIterations = 0;

    while (currEnd - currBegin > eps) {
        double currMiddle = currBegin + (currEnd - currBegin) / 2;
        if (function(currBegin) * function(currMiddle) <= 0) {
            currEnd = currMiddle;
        } else {
            currBegin = currMiddle;
        }

        numIterations++;
    }

    //printResult(segment, numIterations, currBegin + (currEnd - currBegin) / 2);
    //std::cout << "Length of final approximation: " << currEnd - currBegin << "\n";
    return currBegin + (currEnd - currBegin) / 2;
}

double newtonMethod(Segment const& segment, double eps, Function function, Function functionFirstDerivative) {
    double prevApproximation = segment.begin;
    double currentApproximation = 
            prevApproximation - function(prevApproximation) / functionFirstDerivative(prevApproximation);
    
    int numIterations = 0;
    while (abs(prevApproximation - currentApproximation) > eps) {
        prevApproximation = currentApproximation;
        currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(prevApproximation);
        numIterations++;
    }

    //printResult(segment, numIterations, currentApproximation);
    return currentApproximation;
}

double modifiedNewtonMethod(Segment const& segment, double eps, Function function, Function functionFirstDerivative) {
    double prevApproximation = segment.begin;
    double currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(segment.begin);

    int numIterations = 0;
    while (abs(prevApproximation - currentApproximation) > eps) {
        prevApproximation = currentApproximation;
        currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(segment.begin);
        numIterations++;
    }
    
    //printResult(segment, numIterations, currentApproximation);
    return currentApproximation;
}

double secantMethod(Segment const& segment, double eps, Function function) {
    double prePrevApproximation = segment.begin;
    double prevApproximation = segment.end;

    double currentApproximation = prevApproximation - function(prevApproximation) / (function(prevApproximation) - function(prePrevApproximation)) * (prevApproximation - prePrevApproximation);

    int numIterations = 0;
    while (abs(prevApproximation - currentApproximation) > eps) {
        prePrevApproximation = prevApproximation;
        prevApproximation = currentApproximation;
        currentApproximation = prevApproximation - function(prevApproximation) / (function(prevApproximation) - function(prePrevApproximation)) * (prevApproximation - prePrevApproximation);
        numIterations++;
    }

    //printResult(segment, numIterations, currentApproximation);
    return currentApproximation;
}

void clarifyRoots(std::vector<Segment> const& segments, AlgorithmMethod method, double eps, Function function, Function functionFirstDerivative) {
    int solutionCounter = 1;
    for (auto const& segment : segments) {
        std::cout << "\nSolution №" << solutionCounter << '\n';
        std::cout << "----------------------------------------\n";
        switch (method) {
        case AlgorithmMethod::bisection:
            std::cout << "\nBisection method\n";
            bisectionMethod(segment, eps, function);
            break;
        case AlgorithmMethod::newton:
            std::cout << "\nNewton method\n";
            newtonMethod(segment, eps, function, functionFirstDerivative);
            break;
        case AlgorithmMethod::modifiedNewton:
            std::cout << "\nModified Newton method\n";
            modifiedNewtonMethod(segment, eps, function, functionFirstDerivative);
            break;
        case AlgorithmMethod::secant:
            std::cout << "\nSecant method\n";
            secantMethod(segment, eps, function);
            break;
        }
        std::cout << "----------------------------------------\n";
        solutionCounter++;
    }
}