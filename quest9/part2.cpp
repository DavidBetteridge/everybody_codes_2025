#include "common.cpp"
#include <map>

int similarity(std::vector<std::string>& lines, int child, int parent1, int parent2)
{
    auto parent1Matches = 0;
    auto parent2Matches = 0;
    for(auto s=0; s<lines[0].size(); s++)
    {
        if (lines[child][s] == lines[parent1][s])
            parent1Matches++;
        if (lines[child][s] == lines[parent2][s])
            parent2Matches++;
        if (lines[child][s] != lines[parent1][s] && lines[child][s] != lines[parent2][s])
            return 0;
    }

    return parent1Matches * parent2Matches;
}


int main()
{
    auto lines = readLinesFromFile("input2.txt");
    for(auto c=0; c<lines.size(); c++)
    {
        lines[c] = split(lines[c],":")[1];
    }


    auto total = 0;
    for(auto c=0; c<lines.size(); c++)
    {
        auto parentsFound = false;
        for(auto p1=0; p1<lines.size()-1; p1++)
        { 
            if (c != p1)
            {
                for(auto p2=p1+1; p2<lines.size(); p2++)
                {
                   if (c != p2)
                    {
                        // Can P1 and P2 be parents of C
                        auto score = similarity(lines, c, p1, p2);
                        if (score > 0)
                        {
                            total += score;
                            parentsFound = true;
                            break;
                        }
                    }
                }
            }
            if (parentsFound) break;
        }
    }

    std::cout << total << std::endl;
}