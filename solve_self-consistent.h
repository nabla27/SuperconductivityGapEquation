#ifndef SOLVE_SELF_CONSISTENT_H
#define SOLVE_SELF_CONSISTENT_H
#include <cmath>
#include <iostream>

enum class SolveSCAlgorithm { Iterative, Steffensen };

template<SolveSCAlgorithm = SolveSCAlgorithm::Steffensen>
class SolveSelfConsistent
{
public:
    SolveSelfConsistent() {}
    virtual ~SolveSelfConsistent() {}

public:
    template<typename T, typename U>
    static U solve(T *const& instance,
                   double(T::*func)(const U&),
                   const U& init,
                   const U& eps,
                   const size_t& count = 1000);
};

template<>
template<typename T, typename U>
U SolveSelfConsistent<SolveSCAlgorithm::Iterative>::solve(T *const& instance,
                                                          double(T::*func)(const U&),
                                                          const U& init,
                                                          const U& eps,
                                                          const size_t& count)
{
    U val = init, next;
    for(size_t i = 0; i < count; ++i)
    {
        next = (instance->*func)(val);

        if(std::abs(next - val) < eps) break;

        val = next;
    }

    return val;
}

template<>
template<typename T, typename U>
U SolveSelfConsistent<SolveSCAlgorithm::Steffensen>::solve(T *const& instance,
                                                           double(T::*func)(const U&),
                                                           const U& init,
                                                           const U& eps,
                                                           const size_t& count)
{
    U x0 = init, next = init, x1, x2;

    size_t i = 0;
    for(i = 0; i < count; ++i)
    {
        x1 = (instance->*func)(x0);
        x2 = (instance->*func)(x1);
        next -= ((x1 - x0) * (x1 - x0)) / (x0 - 2 * x1 + x2);

        if(std::abs(next - x0) < eps) break;

        x0 = next;
    }

    if(i == count) std::cout << "did not converge" << std::endl;

    return x0;
}


#endif // SOLVE_SELF_CONSISTENT_H
