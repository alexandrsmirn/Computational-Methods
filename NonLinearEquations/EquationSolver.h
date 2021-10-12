#include <vector>
#include <functional>

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

//using Function = std::function<double(double)>;

void printResult(Segment const& segment, int numIterations, double result, std::function<double(double)> function);

std::vector<Segment> getSeparatedRoots(int A, int B, int splitCount, std::function<double(double)> function);

double bisectionMethod(Segment const& segment, double eps, std::function<double(double)> function);

double newtonMethod(Segment const& segment, double eps, std::function<double(double)> function, std::function<double(double)> functionFirstDerivative);

double modifiedNewtonMethod(Segment const& segment, double eps, std::function<double(double)> function, std::function<double(double)> functionFirstDerivative);

double secantMethod(Segment const& segment, double eps, std::function<double(double)> function);

void clarifyRoots(std::vector<Segment> const& segments, AlgorithmMethod method, double eps, std::function<double(double)> function, std::function<double(double)> functionFirstDerivative);