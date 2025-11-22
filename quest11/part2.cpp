#include "common.cpp"
#include <algorithm>
int main()
{
    auto lines = readLinesFromFile("input3.txt");
    std::vector<long> columns(lines.size());
    auto i = 0;
    long totalDucks = 0;
    for (const auto &line : lines)
    {
        columns[i++]=std::stol(line);
        totalDucks+=std::stol(line);
    }


    // Phase 1
    bool keepGoing = true;
    auto round = -1;
    while (keepGoing)
    {
        round++;
        keepGoing = false;

        for(auto c=0; c<lines.size()-1;c++)
        {
            if (columns[c] > columns[c+1])
            {
                columns[c]--;
                columns[c+1]++;
                keepGoing = true;
            }
        }


        auto isBalanced = true;
        for(auto c=0; c<lines.size();c++)
        {
            if (columns[c] != totalDucks / columns.size())
            {
                isBalanced=false;
                break;
            }
        }

        if (isBalanced)
        {
            std::cout << round << std::endl;
            return round;
        }
    }

    long target = totalDucks / columns.size();  
    long max = 0;
    for(auto c=0; c<lines.size();c++)
    {
        auto distance = columns[c] - target;
        if (distance > 0)
            max+=distance;
    }
    std::cout << round + max << std::endl;

    // // Phase 2
    // keepGoing = true;
    // while (keepGoing)
    // {
    //     round++;
    //     keepGoing = false;

    //     for(auto c=0; c<columns.size()-1;c++)
    //     {
    //         if (columns[c] < columns[c+1])
    //         {
    //             columns[c]++;
    //             columns[c+1]--;
    //             keepGoing = true;
    //         }
    //     }

    //     auto isBalanced = true;
    //     for(auto c=0; c<lines.size();c++)
    //     {
    //         if (columns[c] != totalDucks / columns.size())
    //         {
    //             isBalanced=false;
    //             break;
    //         }
    //     }

    //     if (isBalanced)
    //     {
    //         std::cout << round << std::endl;
    //         return round;
    //     }
    // }    
}