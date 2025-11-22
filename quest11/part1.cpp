#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    std::vector<int> columns(lines.size());
    auto i = 0;
    for (const auto &line : lines)
        columns[i++]=std::stoi(line);


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


        if (round == 10)
        {
            auto total = 0;
            for(auto c=0; c<lines.size();c++)
                total += ((c+1) * columns[c]);
            std::cout << total << std::endl;
            return total;
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

        if (round == 10)
        {
            auto total = 0;
            for(auto c=0; c<lines.size();c++)
                total += ((c+1) * columns[c]);
            std::cout << total << std::endl;
            return total;
        }
    }    
}