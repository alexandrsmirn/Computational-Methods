#include <iostream>
#include <cmath>
#include <vector>
#include <string>

struct Segment {
    double begin;
    double end;

    Segment(double begin, double end)
        : begin(begin), end(end) {};
};

enum class AlgorithmMethod{
    bisection,
    newton,
    modifiedNewton,
    secant
};

double function(double x) {
    return 1.2*pow(x, 4) + 2*pow(x, 3) - 13*pow(x, 2) - 14.2*x - 24.1;
}

double functionFirstDerivative(double x) {
    return 4.8*pow(x,3) + 6*pow(x, 2) - 26*x -14.2; 
}

double abs(double x) {
    return x >= 0 ? x : -1*x;
}

void printResult(Segment const& segment, int numIterations, double result) {
    std::cout << "Raw approximaton: (" << segment.begin << ", " << segment.end << ")\n";
    std::cout << "Number of iterations: " << numIterations << "\n";
    std::cout << "Approximate solution: " << result << "\n";
    std::cout << "Solution residual: " << abs(function(result)) << "\n";
}

std::vector<Segment> getSeparatedRoots(int A, int B, int splitCount) {
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

void bisectionMethod(Segment const& segment, double eps) {
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

    printResult(segment, numIterations, currBegin + (currEnd - currBegin) / 2);
    std::cout << "Length of final approximation: " << currEnd - currBegin << "\n";
}

void newtonMethod(Segment const& segment, double eps) {
    double prevApproximation = segment.begin;
    double currentApproximation = 
            prevApproximation - function(prevApproximation) / functionFirstDerivative(prevApproximation);
    
    int numIterations = 0;
    while (abs(prevApproximation - currentApproximation) > eps) {
        prevApproximation = currentApproximation;
        currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(prevApproximation);
        numIterations++;
    }

    printResult(segment, numIterations, currentApproximation);
}

void modifiedNewtonMethod(Segment const& segment, double eps) {
    double prevApproximation = segment.begin;
    double currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(segment.begin);

    int numIterations = 0;
    while (abs(prevApproximation - currentApproximation) > eps) {
        prevApproximation = currentApproximation;
        currentApproximation = prevApproximation - function(prevApproximation) / functionFirstDerivative(segment.begin);
        numIterations++;
    }
    
    printResult(segment, numIterations, currentApproximation);
}

void secantMethod(Segment const& segment, double eps) {
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

    printResult(segment, numIterations, currentApproximation);
}

void clarifyRoots(std::vector<Segment> const& segments, AlgorithmMethod method, double eps) {
    int solutionCounter = 1;
    for (auto const& segment : segments) {
        std::cout << "\nSolution №" << solutionCounter << '\n';
        std::cout << "----------------------------------------\n";
        switch (method) {
        case AlgorithmMethod::bisection:
            std::cout << "\nBisection method\n";
            bisectionMethod(segment, eps);
            break;
        case AlgorithmMethod::newton:
            std::cout << "\nNewton method\n";
            newtonMethod(segment, eps);
            break;
        case AlgorithmMethod::modifiedNewton:
            std::cout << "\nModified Newton method\n";
            modifiedNewtonMethod(segment, eps);
            break;
        case AlgorithmMethod::secant:
            std::cout << "\nSecant method\n";
            secantMethod(segment, eps);
            break;
        }
        std::cout << "----------------------------------------\n";
        solutionCounter++;
    }
}

int main() {
    int const A = -5;
    int const B =  5;
    double const eps = 1e-6;

    //std::cout.setf(std::ios::fixed);
    std::cout.precision(15);

    int splitCount;
    std::cout << "Enter split number\n-> ";
    std::cin >> splitCount;

    std::vector<Segment> separatedRoots = getSeparatedRoots(A, B, splitCount);

    std::cout << "Here is the list of the separated roots:\n";
    for (Segment const& segment : separatedRoots) {
        std::cout << "(" << segment.begin << ", " << segment.end << ")\n";
    }

    clarifyRoots(separatedRoots, AlgorithmMethod::newton, eps);

    return 0;
}