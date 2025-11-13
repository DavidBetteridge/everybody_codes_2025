#include "common.cpp"
#include <map>

int main()
{
    const int numberOfNails = 256;
    auto lines = readLinesFromFile("input3.txt");
    auto notes = splitToInt(lines[0], ",");

    // Notes into strings
    std::vector<int> stringStart;
    std::vector<int> stringEnd;
    for(auto n=0; n<notes.size()-1; n++)
    {
        stringStart.push_back(notes[n]);
        stringEnd.push_back(notes[n+1]);
    }

    auto total = 0;
    for(auto from=1; from<numberOfNails; from++)
    {
        auto rotation = from - 1;
        for(auto to=(from+1); to<=numberOfNails; to++)
        {
            auto aE = to - rotation;

            auto knots = 0;
            for(auto p=0; p<stringStart.size(); p++)
            {
                auto s = stringStart[p];
                auto e = stringEnd[p];

                s-= rotation;
                if (s < 1)
                    s+=numberOfNails;

                e-= rotation;
                if (e < 1)
                    e+=numberOfNails;

                if (s == 1 && e == aE)
                {
                    knots++;
                    continue;
                }

                if (e == 1 && s == aE)
                {
                    knots++;
                    continue;
                }

                if (s == 1 || e == 1 || s == aE || e == aE)
                    continue;

                if (s < aE && e > aE)
                    knots++;
                if (s > aE && e < aE)
                    knots++;
            }
            if (knots > total)
                total = knots;

        }        
    }

    std::cout << total << std::endl;
    return total;
}