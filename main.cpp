#include "solve_self-consistent.h"
#include "integral.h"
#include "gapequation.h"
#include <math.h>
#include <iostream>
#include <fstream>

int main()
{
    GapEquation gapEquation;

    std::ofstream fout("E:/repos/SuperconductivityGapEquation/gap.csv");

    for(double T = 0.005; T < 2.0; T += 0.005)
    {
        gapEquation.param.T = T;
        const double value = SolveSelfConsistent<SolveSCAlgorithm::Steffensen>::solve(&gapEquation, &GapEquation::gapEquation, 1.5, 1e-4);
        std::cout << T << " : " << value << std::endl;
        fout << T << ", " << value << "\n";
    }

    return 0;
}
