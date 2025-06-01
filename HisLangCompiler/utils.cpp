// utils.cpp
#include "utils.hpp"
#include <algorithm>
#include <sstream>


std::string trim(const std::string& s) {
    if (s.empty()) return "";

    size_t start = 0;
    size_t end = s.size() - 1;

    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    while (end >= start && std::isspace(static_cast<unsigned char>(s[end]))) {
        --end;
    }

    return s.substr(start, end - start + 1);
}


std::vector<std::string> split_lines(const std::string& text) {
    std::vector<std::string> lines;
    std::istringstream iss(text);
    std::string line;
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
    return lines;
}