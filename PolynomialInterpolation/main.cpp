#include <iostream>
#include <vector>
#include <math.h>
#include <functional>

double f(double x) {
    return cos(x) + 2 * x;
}

class PolynomCalculator {
protected:
    using Table = std::vector<std::pair<double, double>>;

    double begin;
    double end;
    int numPoints;

    std::vector<std::pair<double, double>> interpolationTable;
    std::function<double(double)> func;

    void createInterpolationTable(int newNumber) {
        numPoints = newNumber;
        double step = (end - begin) / numPoints;
        interpolationTable.clear();

        for (int i = 0; i < numPoints - 1; i++) {
            double x = begin + i * step;
            interpolationTable.push_back(std::make_pair(x, func(x)));
        }
        interpolationTable.push_back(std::make_pair(end, func(end)));
    }

    Table createSortedInterpolationTable(double argument, int degree) {
        Table sortedInterpolationTable = interpolationTable;

        std::sort(sortedInterpolationTable.begin(), sortedInterpolationTable.end(),
                    [argument](std::pair<double, double> pair1, std::pair<double, double> pair2) {
                        return abs(pair1.first - argument) < abs(pair2.first - argument);
                    } );

        sortedInterpolationTable.resize(degree);
        return sortedInterpolationTable;
    }
    
public:
    PolynomCalculator(double begin, double end, int numPoints, std::function<double(double)> func)
            : begin(begin), end(end), func(func) {
        createInterpolationTable(numPoints);
    };

    void printTable() {
        std::cout << "Point\t|Value\n";
        for (auto const& pair : interpolationTable) {
            std::cout << pair.first << "\t| " << pair.second << '\n';
        }
    }

    virtual double getInterpolatedValue(double point, int degree) = 0;
};

class NewtonPolynom : public PolynomCalculator {
private:
    std::vector<std::vector<double>> dividedDiffTable;

    void createDividedDiffTable(Table const& sortedInterpolationTable) {
        dividedDiffTable.clear();
        int degree = sortedInterpolationTable.size();

        std::vector<double> zeroLevel;
        for (auto const& row : sortedInterpolationTable) {
            zeroLevel.push_back(row.second);
        }
        dividedDiffTable.push_back(std::move(zeroLevel));

        for (int levelNum = 1; levelNum < degree; ++levelNum) {
            std::vector<double> level; 
            for (int i = 0; i < degree - levelNum; ++i) {
                auto const& previousLevel = dividedDiffTable[levelNum - 1];
                double val = (previousLevel[i + 1] - previousLevel[i]) / (sortedInterpolationTable[i + levelNum].first - sortedInterpolationTable[i].first);
                level.push_back(val);
            }
            dividedDiffTable.push_back(std::move(level));
        }
    }

public:
    NewtonPolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : PolynomCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override {
        Table sortedInterpolationTable = createSortedInterpolationTable(argument, degree);
        createDividedDiffTable(sortedInterpolationTable);

        double result = 0;
        double parenthesesComposition = 1;
        for (int numLevel = 0; numLevel < degree; ++numLevel) {
            result += dividedDiffTable[numLevel][0] * parenthesesComposition;
            parenthesesComposition *= (argument - sortedInterpolationTable[numLevel].first);
        }
        return result;
    }
};

class LagrangePolynom : public PolynomCalculator {
private:  
    double calculateFundamentalPoly(double argument, int pointNumber, Table const& sortedInterpolationTable) {
        double result = 1;
        double point = sortedInterpolationTable[pointNumber].first;

        for (auto const& pair : sortedInterpolationTable) {
            if (pair.first != point) {
                result *= (argument - pair.first) / (point - pair.first);
            }
        }
        return result;
    }

public:
    LagrangePolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : PolynomCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override {
        Table sortedInterpolationTable = createSortedInterpolationTable(argument, degree);

        int pointNumber = 0;
        double result = 0;

        for (auto const& pair : sortedInterpolationTable) {
            result += calculateFundamentalPoly(argument, pointNumber++, sortedInterpolationTable) * pair.second;
        }

        return result;
    }
};

int main() {
    using std::cin, std::cout, std::endl;
    cout.precision(18);
    cout.setf(std::ios::fixed);

    double begin;
    double end;
    int numPoints;
    double argument;
    int degree;

    cout << "Enter begin and end" << endl;
    std::cin >> begin >> end;
    cout << "Enter number of points -> ";
    std::cin >> numPoints;

    auto lagrangeCalculator = LagrangePolynom(begin, end, numPoints, f);
    auto   newtonCalculator = NewtonPolynom  (begin, end, numPoints, f);

    std::cout << "\nInterpolation table:\n";
    lagrangeCalculator.printTable();
    std::cout << "\n---------------------------------------------------------------\n";

    while (true) {
        cout << "Enter argument to calculate function -> ";
        std::cin >> argument;

        std::cout << "Enter polynom degree -> ";
        std::cin >> degree;

        if (degree > numPoints) {
            std::cout << "Degree must not be greater than " << numPoints << '\n';
            std::cout << "---------------------------------------------------------------\n";
            continue;
        }

        double exactValue = f(argument);
        double lagrangePolyniminalValue = lagrangeCalculator.getInterpolatedValue(argument, degree);
        double newtonPolyniminalValue   = newtonCalculator  .getInterpolatedValue(argument, degree);

        std::cout << "\nExact function value:                   " << exactValue << '\n';
        std::cout << "--------\n";
        std::cout << "Approximate Lagrange value:             " << lagrangePolyniminalValue << '\n';
        std::cout << "Lagrange error:                         " << abs(lagrangePolyniminalValue - exactValue) << '\n';
        std::cout << "--------\n";
        std::cout << "Approximate Newton value: " << newtonPolyniminalValue << '\n';
        std::cout << "Newton error:                           " << abs(newtonPolyniminalValue - exactValue) << '\n';
        std::cout << "---------------------------------------------------------------\n";
    }
}