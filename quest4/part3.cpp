#include "common.cpp"
#include <iomanip>

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    

    double ratio = 1;
    auto previous = std::stoi(lines[0]);
    for(auto i=1; i < lines.size(); i++)
    {
        auto wheels = split(lines[i], "|");
        auto lhs = std::stoi(wheels[0]);
        ratio = ratio * previous / static_cast<double>(lhs);

        if (wheels.size() > 1)
            previous = std::stoi(wheels[1]);
    }
    auto total = 100 * ratio;
    std::cout << std::setprecision(17) << total << std::endl;
    //190804377600
}