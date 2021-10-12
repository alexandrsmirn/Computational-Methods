#include "NewtonPolynom.h"

NewtonPolynom::DiffTable NewtonPolynom::createDividedDiffTable(Table const& sortedInterpolationTable) const {
    DiffTable dividedDiffTable;
    int const degree = sortedInterpolationTable.size();

    std::vector<double> zeroLevel;
    for (auto const& row : sortedInterpolationTable) {
        zeroLevel.push_back(row.second);
    }
    dividedDiffTable.push_back(std::move(zeroLevel));

    for (int levelNum = 1; levelNum < degree; ++levelNum) {
        std::vector<double> level; 
        for (int i = 0; i < degree - levelNum; ++i) {
            auto const& previousLevel = dividedDiffTable[levelNum - 1];
            double dividedDiffValue = (previousLevel[i + 1] - previousLevel[i])
                                    / (sortedInterpolationTable[i + levelNum].first - sortedInterpolationTable[i].first);
            level.push_back(dividedDiffValue);
        }
        dividedDiffTable.push_back(std::move(level));
    }

    return dividedDiffTable;
}

double NewtonPolynom::getInterpolatedValue(double argument, int degree) const {
    Table const sortedInterpolationTable = createSortedInterpolationTable(argument, degree);
    DiffTable const dividedDiffTable = createDividedDiffTable(sortedInterpolationTable);

    double result = 0;
    double parenthesesComposition = 1;
    for (int numLevel = 0; numLevel < degree; ++numLevel) {
        result += dividedDiffTable[numLevel][0] * parenthesesComposition;
        parenthesesComposition *= (argument - sortedInterpolationTable[numLevel].first);
    }
    return result;
}
