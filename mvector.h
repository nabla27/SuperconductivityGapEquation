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
    template<typename T>
    static void appendDataFromStr(std::vector<T>& array, const std::string& str)
    {
        if constexpr(std::is_same_v<T, double>)
            array.push_back(std::stod(str));
        else if constexpr(std::is_same_v<T, float>)
            array.push_back(std::stof(str));
        else if constexpr(std::is_same_v<T, int>)
            array.push_back(std::stoi(str));
        else if constexpr(std::is_same_v<T, std::string>)
            array.push_back(str);
    }

public:
    template<typename T, size_t N>
    static std::vector<std::vector<T>> load(const std::string& path, const char& separator = ',')
    {
        std::vector<std::vector<T>> data(N, std::vector<T>({}));

        std::ifstream fin(path);
        if(fin.fail()) return data;

        std::string str = "";
        std::string stack = "";

        while(std::getline(fin, str))
        {
            size_t col = 0;

            for(const char& c : str)
            {
                if(c == separator)
                {
                    if(col < N)
                        appendDataFromStr(data[col], stack);

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

            if(stack.size() > 0 && col < N)
            {
                appendDataFromStr(data[col], stack);
                stack.clear();
            }
        }

        return data;
    }

    template<typename T, size_t N>
    std::vector<std::vector<T>> load()
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
