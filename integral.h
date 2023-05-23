#ifndef INTEGRAL_H
#define INTEGRAL_H

enum class IntegralAlgorithm { Trapezoid, Simpson };

template<IntegralAlgorithm>
class Integral
{
public:
    Integral() {}
    virtual ~Integral() {}

public:
    template<typename T, typename U>
    static U integrate(T*const& instance,
                       double(T::*func)(const U&),
                       const U& min,
                       const U& max,
                       const U& step);
};

template<>
template<typename T, typename U>
U Integral<IntegralAlgorithm::Trapezoid>::integrate(T*const& instance,
                                                    double(T::*func)(const U&),
                                                    const U& min,
                                                    const U& max,
                                                    const U& step)
{
    U val = step * 0.5 * ((instance->*func)(min) + (instance->*func)(max));

    for(U x = min + step; x < max; x += step)
    {
        val += step * (instance->*func)(x);
    }

    return val;
}

template<>
template<typename T, typename U>
U Integral<IntegralAlgorithm::Simpson>::integrate(T*const& instance,
                                                  double(T::*func)(const U&),
                                                  const U& min,
                                                  const U& max,
                                                  const U& step)
{
    U val = step / 3.0 * ((instance->*func)(min) + (instance->*func)(max));
    U loopStep = step * 2;

    for(U x = min + step; x < max; x += loopStep)
    {
        val += step / 3.0 * (4.0 * (instance->*func)(x) + 2.0 * (instance->*func)(x + step));
    }

    return val;
}

#endif // INTEGRAL_H
