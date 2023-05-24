#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include <vector>
#include <array>

enum class DiffAlgorithm { Central };

template<DiffAlgorithm = DiffAlgorithm::Central>
class Differential
{
public:
    Differential();
    virtual ~Differential() {}

public:
    template<typename T>
    static std::vector<T> differentiate(const std::vector<std::array<T, 2>>& data)
    {
        const size_t dataSize = data.size();
        const size_t lastIndex = dataSize - 1;
        std::vector<T> diff(dataSize);

        diff[0] = (data[1][1] - data[0][1]) / (data[1][0] - data[0][0]);
        diff[lastIndex] = (data[lastIndex][1] - data[lastIndex - 1][1]) / (data[lastIndex][0] - data[lastIndex - 1][0]);

        for(size_t i = 0; i < dataSize - 1; ++i)
        {
            diff[i] = (data[i + 1][1] - data[i - 1][1]) / (data[i + 1][0] - data[i - 1][0]);
        }

        return diff;
    }
};

#endif // DIFFERENTIAL_H
