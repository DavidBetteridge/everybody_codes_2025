#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    std::vector<int> columns(lines.size());
    auto i = 0;
    auto totalDucks = 0;
    for (const auto &line : lines)
    {
        columns[i++]=std::stoi(line);
        totalDucks+=std::stoi(line);
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

    // Phase 2
    keepGoing = true;
    while (keepGoing)
    {
        round++;
        keepGoing = false;

        for(auto c=0; c<columns.size()-1;c++)
        {
            if (columns[c] < columns[c+1])
            {
                columns[c]++;
                columns[c+1]--;
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
}