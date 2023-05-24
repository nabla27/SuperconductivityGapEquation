#include "solve_self-consistent.h"
#include "gapequation.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

//debug
#include "mvector.h"
#include "differential.h"

void createGapData(const std::string& filePath)
{
    GapEquation gapEquation;

    std::ofstream fout(filePath);

    static constexpr size_t dataPoints = 1200;
    static constexpr double init = 1.5;
    static constexpr double eps = 1e-4;

    for(size_t i = 1; i < dataPoints + 1; ++i)
    {
        double T = static_cast<double>(i) / 1000.0;

        gapEquation.param.T = T;
        const double gap = SolveSelfConsistent<SolveSCAlgorithm::Steffensen>::solve(&gapEquation, &GapEquation::gapEquation, init, eps);

        std::cout << T << " : " << gap << std::endl;
        fout << T << ", " << gap << "\n";
    }
}

int main()
{
    //createGapData("E:/repos/SuperconductivityGapEquation/gnuplot/gap.csv");

    std::vector<std::array<double, 2> > data;
    data = LoadVector::load<double, 2>("E:/repos/SuperconductivityGapEquation/gnuplot/gap.csv");

    std::vector<double> diffGap = Differential<DiffAlgorithm::Central>::differentiate(data);

    assignmentStdVec(diffGap, diffGap * 2.0 / 3.2 * diffGap);

    return 0;
}
