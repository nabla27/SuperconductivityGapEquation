#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include <vector>
#include <array>
#include <assert.h>

enum class DiffAlgorithm { Central };

template<DiffAlgorithm = DiffAlgorithm::Central>
class Differential
{
public:
    Differential();
    virtual ~Differential() {}

public:
    template<typename T>
    static std::vector<T> differentiate(const std::vector<T>& y,
                                        const std::vector<T>& x)
    {
        const size_t dataSize = y.size();
        assert(dataSize == x.size());

        const size_t lastIndex = dataSize - 1;
        std::vector<T> diff(dataSize);

        diff[0] = (y[1] - y[0]) / (x[1] - x[0]);
        diff[lastIndex] = (y[lastIndex] - y[lastIndex - 1]) / (x[lastIndex] - x[lastIndex - 1]);

        for(size_t i = 0; i < dataSize - 1; ++i)
        {
            diff[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
        }

        return diff;
    }
};

#endif // DIFFERENTIAL_H
