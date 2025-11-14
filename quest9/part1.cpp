#include "common.cpp"
#include <map>

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    for(auto c=0; c<lines.size(); c++)
    {
        lines[c] = split(lines[c],":")[1];
    }

    // Which line is the child?
    auto childLine = -1;
    for(auto c=0; c<lines.size(); c++)
    {
        //p is the line we are currently testing

        auto ok = true;
        for(auto s=0; s<lines[0].size(); s++)
        {
            // s is the symbol
            auto inheritted = false;
            for(auto p=0; p<lines.size(); p++)
            {       
                if (p != c)
                {
                    if (lines[c][s] == lines[p][s]) {
                        inheritted = true;
                        break;
                    }
                }
            }
            if (!inheritted)
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            // We have found the child
            childLine = c;
            break;
        }
    }

    auto total = 1;
    for(auto p=0; p<lines.size(); p++)
    { 
        if (p != childLine)
        {
            auto parentMatches = 0;
            for(auto s=0; s<lines[0].size(); s++)
            {
                if (lines[childLine][s] == lines[p][s]) {
                    parentMatches++;
                }
            }
            total *= parentMatches;
        }
    }

    std::cout << total << std::endl;
}