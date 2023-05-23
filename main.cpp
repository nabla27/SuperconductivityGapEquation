#include "solve_self-consistent.h"
#include "integral.h"
#include "gapequation.h"
#include <math.h>
#include <iostream>
#include <fstream>

int main()
{
    GapEquation gapEquation;

#if 1
    std::ofstream fout("E:/test.csv");

    for(double T = 0.005; T < 2.0; T += 0.005)
    {
        gapEquation.param.T = T;
        const double value = SolveSelfConsistent<SolveSCAlgorithm::Steffensen>::solve(&gapEquation, &GapEquation::gapEquation, 1.5, 1e-4);
        std::cout << T << " : " << value << std::endl;
        fout << T << ", " << value << "\n";
    }
#else

    gapEquation.param.T = 0.3;
    std::cout << gapEquation.param.hbar * gapEquation.param.omegaCut / (gapEquation.param.kB * gapEquation.param.Tc) << std::endl;
    const double delta = SolveSelfConsistent<SolveSCAlgorithm::Steffensen>::solve(&gapEquation, &GapEquation::gapEquation, 1.5, 1e-4);
    const double Delta = delta * gapEquation.param.kB * gapEquation.param.Tc;
    std::cout << gapEquation.param.T << " : " << delta << " : " << Delta << std::endl;

#endif

    return 0;
}
