#ifndef MVECTOR_H
#define MVECTOR_H

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <assert.h>

template<typename T>
std::vector<T> operator*(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();
    assert(vecSize == v2.size());

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] *= v2[i];

    return ans;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& v1, const T& val)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] *= val;

    return ans;
}

template<typename T>
std::vector<T> operator*(const T& val, const std::vector<T>& v1)
{
    return v1 * val;
}

template<typename T>
std::vector<T> operator/(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();
    assert(vecSize == v2.size());

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] /= v2[i];

    return ans;
}

template<typename T>
std::vector<T> operator/(const std::vector<T>& v1, const T& val)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] /= val;

    return ans;
}

template<typename T>
std::vector<T> operator/(const T& val, const std::vector<T>& v1)
{
    return v1 / val;
}

template<typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();
    assert(vecSize == v2.size());

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] += v2[i];

    return ans;
}

template<typename T>
std::vector<T> operator-(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> ans = v1;

    const size_t vecSize = v1.size();
    assert(vecSize == v2.size());

    for(size_t i = 0; i < vecSize; ++i)
        ans[i] -= v2[i];

    return ans;
}

template<typename T>
void assignmentStdVec(std::vector<T>& v1, const std::vector<T>& v2)
{
    size_t vecSize = v1.size();
    assert(vecSize == v2.size());

    for(size_t i = 0; i < vecSize; ++i)
        v1[i] = v2[i];
}








class LoadVector
{
public:
    LoadVector() {}
    LoadVector(const std::string& path, const char& separator = ',')
        : _path(path)
        , _separator(separator) {}
    virtual ~LoadVector() {}

private:
    template<typename T, typename U>
    static void setDataFromStr(T& array, const U& index, const std::string& str)
    {
        if constexpr(std::is_same_v<T, double>)
            array[index] = std::stod(str);
        else if constexpr(std::is_same_v<T, float>)
            array[index] = std::stof(str);
        else if constexpr(std::is_same_v<T, int>)
            array[index] = std::stoi(str);
        else if constexpr(std::is_same_v<T, std::string>)
            array[index] = str;
        else
            return;
    }

public:
    template<typename T, size_t N>
    static std::vector<std::array<T, N>> load(const std::string& path, const char& separator = ',')
    {
        std::vector<std::array<T, N>> data(0);

        std::ifstream fin(path);
        if(fin.fail()) return data;

        std::string str = "";
        std::string stack = "";
        std::array<T, N> line({});

        while(std::getline(fin, str))
        {
            size_t col = 0;

            for(const char& c : str)
            {
                if(c == separator)
                {
                    setDataFromStr(line, col, stack);

                    col += 1;

                    stack.clear();
                }
                else if(c == ' ')
                {
                    continue;
                }
                else
                {
                    stack += c;
                }
            }

            if(stack.size() > 0)
            {
                setDataFromStr(line, col, stack);
                stack.clear();
            }

            data.push_back(line);
        }

        return data;
    }

    template<typename T, size_t N>
    std::vector<std::array<T, N>> load()
    {
        return LoadVector::load<T, N>(_path, separator);
    }

    void setPath(const std::string& path) { _path = path; }
    void setSeparator(const char& separator) { _separator = separator; }
    std::string path() const noexcept { return _path; }
    char separator() const noexcept { return _separator; }

private:
    std::string _path;
    char _separator;
};

#endif // MVECTOR_H
