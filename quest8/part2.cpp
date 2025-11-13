#include "common.cpp"
#include <map>

int main()
{
    const int numberOfNails = 256;
    auto lines = readLinesFromFile("input2.txt");
    auto notes = splitToInt(lines[0], ",");

    // Notes into strings
    std::vector<int> stringStart;
    std::vector<int> stringEnd;
    for(auto n=0; n<notes.size()-1; n++)
    {
        stringStart.push_back(notes[n]);
        stringEnd.push_back(notes[n+1]);
    }

    // For each string,  count how many previous strings we crossed
    auto total = 0;
    for(auto n=1; n<stringStart.size(); n++)
    {

        int rotation;
        int aE = 0;
        if (stringStart[n] < stringEnd[n])
        {
            rotation = stringStart[n] - 1;
            aE = stringEnd[n] - rotation;
        }
        else
        {
            rotation = stringEnd[n] - 1;
            aE = stringStart[n] - rotation;
        }

        auto knots = 0;
        for(auto p=0; p<(n-1); p++)
        {
            auto s = stringStart[p];
            auto e = stringEnd[p];

            s-= rotation;
            if (s < 1)
                s+=numberOfNails;

            e-= rotation;
            if (e < 1)
                e+=numberOfNails;

            if (s == 1 || e == 1 || s == aE || e == aE)
                continue;

            if (s < aE && e > aE)
                knots++;
            if (s > aE && e < aE)
                knots++;
        }
        total += knots;
    }    

    std::cout << total << std::endl;
    return total;
}