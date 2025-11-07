#include "common.cpp"
#include <iomanip>

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    std::vector<int> gears;
    std::transform(lines.begin(), lines.end(), std::back_inserter(gears), [](const std::string& str) { return std::stoi(str); });

    auto ratio = gears[0] / static_cast<double>(gears[gears.size()-1]);
    auto total = 10000000000000 / ratio;
    std::cout << std::setprecision(17) << ceil(total) << std::endl;

}