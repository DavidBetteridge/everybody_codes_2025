#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto wall = splitToInt(lines[0], ",");

    // First we find the spell
    std::vector<int> spell;
    for(auto i=0;i<wall.size();i++)
    {
        if (wall[i] == 1)
        {
            spell.push_back(i+1);
            for(auto j=i;j<wall.size();j+=(i+1))
                wall[j]--;
        }
    }

    // Then we do a binary search 
    const long target = 202520252025000;
    long lhs = 0;
    long rhs = 202520252025000;
    long wall_length = (rhs - lhs) / 2;

    auto rounds = 0;
    while (lhs < rhs && (rounds++)<100)
    {
        long blocks_used = 0;
        for (const auto &hop : spell)
            blocks_used += wall_length / hop;

        std::cout << blocks_used << ',' << wall_length << ',' << lhs << ',' << rhs << std::endl;
        if (blocks_used == target)
        {
            std::cout << wall_length << std::endl;
            return 0;
        }

        if (blocks_used < target)
            lhs = wall_length+1;
        else
            rhs = wall_length - 1;

        wall_length = lhs + floor((rhs - lhs) / 2);
    }
}   