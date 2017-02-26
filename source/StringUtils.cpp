#include "StringUtils.hpp"

std::string stripKnownEndings(
    const std::string& str,
    const std::string& startStrip,
    const std::string& endStrip
)
{
    auto start = 0;
    auto ending = str.length();

    if (str.compare(0, startStrip.size(), startStrip) == 0)
    {
        start = startStrip.length();
    }

    if (str.length() >= endStrip.length()
        && str.compare(
            str.length() - endStrip.length(),
            endStrip.length(),
            endStrip
        ) == 0)
    {
        ending = str.length() - endStrip.length() - 1;
    }

    if (start > ending)
    {
        return std::string();
    }

    return str.substr(start, ending - start + 1);
}

