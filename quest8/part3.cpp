#include "common.cpp"
#include <map>

int main()
{
    const int numberOfNails = 256;
    auto lines = readLinesFromFile("input3.txt");
    auto notes = splitToInt(lines[0], ",");

    auto total = 0;
    for(auto from=1; from<numberOfNails; from++)
    {
        auto rotation = from - 1;
        for(auto to=(from+1); to<=numberOfNails; to++)
        {
            auto aE = to - rotation;

            auto knots = 0;
            for(auto p=0; p<notes.size()-1; p++)
            {
                auto s = notes[p];
                auto e = notes[p+1];

                s-= rotation;
                if (s < 1)
                    s+=numberOfNails;

                e-= rotation;
                if (e < 1)
                    e+=numberOfNails;

                // Same line
                if (s == 1 && e == aE)
                {
                    knots++;
                    continue;
                }

                // Same line
                if (e == 1 && s == aE)
                {
                    knots++;
                    continue;
                }

                // Same start or finish (but not both - from above)
                if (s == 1 || e == 1 || s == aE || e == aE)
                    continue;

                // Crosses
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