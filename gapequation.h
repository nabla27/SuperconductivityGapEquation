#ifndef GAPEQUATION_H
#define GAPEQUATION_H

#include <cmath>
#include "integral.h"
#include "solve_self-consistent.h"

class GapEquation
{
public:
    GapEquation() {}
    virtual ~GapEquation() {}

public:
    struct Parameter
    {
        static constexpr double kB = 1; //1.38 * 1e-23; //ボルツマン定数
        static constexpr double hbar = 1; //1.054 * 1e-34; //ディラック定数
        static constexpr double Tc = 1.0; //転移温度
        double omegaCut = kB * Tc / hbar * 300; //カットオフ角周波数
        double gap = 0.0f; //超伝導ギャップ
        double T = 0.0f; //温度
    } param;

    double integrand(const double& x)
    {
        const double factor = std::sqrt(x * x + param.gap * param.gap);
        return std::tanh(factor / (2 * param.kB * param.T)) / factor;
    }

    double gapEquation(const double& gap)
    {
        param.gap = gap;
        double energyCut = 200;
        static constexpr double eularConst = 0.57721;
        const double q = std::log(2 * std::exp(eularConst) * (energyCut / (param.kB * param.Tc)) / 3.14159265);
        return gap / q * Integral<IntegralAlgorithm::Simpson>::integrate(this, &GapEquation::integrand, 0.0, energyCut, 0.0001);
    }
};

#endif // GAPEQUATION_H
