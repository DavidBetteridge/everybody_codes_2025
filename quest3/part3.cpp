#include "common.cpp"
#include <map>

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto crates = split(lines[0], ",");

    // Count how many of each size we have
    auto lists = 0;
    std::map<int, int> quantities;
    for (std::string i : crates)
    {
        quantities[std::stoi(i)] = quantities[std::stoi(i)] + 1;
        if (quantities[std::stoi(i)] > lists)
            lists = quantities[std::stoi(i)];
    }

    std::cout << lists << std::endl;

}