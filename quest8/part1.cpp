#include "common.cpp"
#include <map>

int main()
{
    const int numberOfNails = 32;
    auto lines = readLinesFromFile("input1.txt");
    auto notes = splitToInt(lines[0], ",");

    auto total = 0;
    for(auto n=0; n<notes.size()-1; n++)
    {
        auto diff = abs(notes[n] - notes[n+1]);
        if (diff == (numberOfNails / 2))
            total++;
    }

    std::cout << total << std::endl;
    return total;
}