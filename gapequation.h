#ifndef GAPEQUATION_H
#define GAPEQUATION_H

#include <cmath>
#include <vector>
#include "integral.h"
#include "solve_self-consistent.h"
#include "differential.h"
#include "mvector.h"

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






class HeatCapacity
{
public:
    HeatCapacity(const std::vector<double>& gap, const std::vector<double>& temp)
        : _gap(gap)
        , _temp(temp)
    {
        setGapDiff();
    }
    virtual ~HeatCapacity() {}

public:
    struct Parameter
    {
        size_t index = 0;
        double cutOff = 500;
        double kB = 1.0;
        double Ef = 100000;
    } param;

public:
    double integrand(const double& x)
    {
        const double T = _temp[param.index];
        const double gap = _gap[param.index];
        //const double energy = std::sqrt(x * x + gap * gap);
        //const double coshFactor = std::cosh(energy * 0.5 / (param.kB * T));

        //return (energy * energy - T * 0.5 * _gapDiff[param.index]) / (coshFactor * coshFactor);

        const double energy = std::sqrt((x * x - param.Ef) * (x * x - param.Ef) + gap * gap);
        const double eexp = std::exp(- energy / T);

        return x * x * (energy * energy - T * 0.5 * _gapDiff[param.index]) * (eexp / T) / ((eexp + 1.0) * (eexp + 1.0));
    }

    double calHeatCapacity(const size_t& index)
    {
        param.index = index;
        const double T = _temp[param.index];
        const double upperLim = std::sqrt(param.Ef + param.cutOff);
        const double lowerLim = std::sqrt(param.Ef - param.cutOff);
        return (1.0/T) * Integral<IntegralAlgorithm::Simpson>::integrate(this, &HeatCapacity::integrand, lowerLim, upperLim, 1e-3);
    }

private:
    void setGapDiff()
    {
        _gapDiff = Differential<DiffAlgorithm::Central>::differentiate(_gap * _gap, _temp);
    }

private:
    std::vector<double> _gap;
    std::vector<double> _temp;
    std::vector<double> _gapDiff;
};







#endif // GAPEQUATION_H
