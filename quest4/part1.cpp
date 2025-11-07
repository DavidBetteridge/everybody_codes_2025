#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    std::vector<int> gears;
    std::transform(lines.begin(), lines.end(), std::back_inserter(gears), [](const std::string& str) { return std::stoi(str); });

    auto ratio = gears[0] / static_cast<double>(gears[gears.size()-1]);
    auto total = 2025 * ratio;
    std::cout << total << std::endl;
}