#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>

namespace Utils
{
    inline
    std::vector<std::string> split(
        const std::string &str,
        char delimiter,
        size_t from = 0)
    {
        std::vector<std::string> result;
        std::istringstream iss(str);
        std::string token;

        size_t curr = 0;
        while (std::getline(iss, token, delimiter)) {
            if (++curr > from) {
                result.push_back(token);
            }
        }

        return result;
    }

    template <class From, class To>
    struct Converter;

    template <class To>
    struct Converter<std::string, To>
    {
        static To convert(const std::string &str)
        {
            std::istringstream iss(str);
            To value;
            iss >> value;
            return value;
        }
    };

    template <class From, class To>
    inline
    std::vector<To> map(const std::vector<From> &data)
    {
        std::vector<To> out;
        std::transform(data.cbegin(), data.cend(),
            std::back_inserter(out), Converter<From, To>::convert);
        return out;
    }
}

#endif // UTILS_H
