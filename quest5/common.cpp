#include <iostream>
#include <fstream>
#include <numeric>
#include <ranges>
#include <vector>
#include <stdexcept>


std::vector<std::string> split(std::string text, std::string sep)
{
    std::vector<std::string> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        list.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    return list;
}

std::vector<std::string> readLinesFromFile(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file.is_open())
    { 
        std::cerr << "Error: Could not open file. " << filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

inline int mod(int a, int b) {
    int ret = a % b;
    return ret >= 0 ? ret : ret + b;
}