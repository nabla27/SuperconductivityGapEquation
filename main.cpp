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

void createHeatCapacityData(const std::string& filePath,
                            const std::vector<double>& gap,
                            const std::vector<double>& temp)
{
    HeatCapacity heatCapacity(gap, temp);

    std::ofstream fout(filePath);

    const size_t dataSize = gap.size();
    for(size_t i = 0; i < dataSize; ++i)
    {
        const double T = temp[i];
        const double C = heatCapacity.calHeatCapacity(i);

        static constexpr double gamma = 520.174;
        std::cout << T << " : " << C << " : " << C / T << std::endl;
        fout << T << ", " << C << ", " << C / T / gamma << "\n";
    }
}

std::string replaceStr(const std::string& str, const char& before, const char& after)
{
    std::string replaced = "";
    const size_t strSize = str.size();
    replaced.reserve(strSize);

    for(const char& c : str)
    {
        if(c == before)
            replaced.push_back(after);
        else
            replaced.push_back(c);
    }

    return replaced;
}

void createHeatCapacityAlphaData(const std::string& folderPath,
                                 const std::vector<double>& gap,
                                 const std::vector<double>& temp,
                                 const std::vector<double>& alphaList)
{
    static constexpr double alphaBCS = 1.76;

    for(const double& alpha : alphaList)
    {
        const std::string alphaStr = replaceStr(std::to_string(alpha), '.', 'p');
        const std::string path = folderPath + "heatCapacity_" + alphaStr + ".csv";
        createHeatCapacityData(path, gap * (alpha / alphaBCS), temp);
    }
}

int main()
{
    //createGapData("E:/repos/SuperconductivityGapEquation/gnuplot/gap.csv");

    std::vector<std::vector<double> > gapData = LoadVector::load<double, 2>("E:/repos/SuperconductivityGapEquation/gnuplot/gap.csv");

    const std::vector<double> alphaList = { 2.1, 1.76, 1.2, 0.7 };
    createHeatCapacityAlphaData("E:/repos/SuperconductivityGapEquation/gnuplot/", gapData[1], gapData[0], alphaList);

    return 0;
}
