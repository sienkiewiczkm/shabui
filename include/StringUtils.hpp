#pragma once
#include <string>

std::string stripKnownEndings(
    const std::string& str,
    const std::string& startStrip,
    const std::string& endStrip
);
