#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto hops = splitToInt(lines[0], ",");
    const int length = 90;

    auto total = 0;
    for (const auto &hop : hops)
    {
        total += (length / hop);
    }

    std::cout << total << std::endl;
}
