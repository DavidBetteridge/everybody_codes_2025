#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto wall = splitToInt(lines[0], ",");

    long total = 1;
    std::vector<int> solution;

    for(auto i=0;i<wall.size();i++)
    {
        // If the wall is == 1,  then i+1 must be a solution
        // then move the solution forward

        if (wall[i] == 1)
        {
            solution.push_back(i+1);
            for(auto j=i;j<wall.size();j+=(i+1))
            {
                wall[j]--;
            }
            std::cout << (i+1) << std::endl;
            total *= (i+1);
        }

    }

    std::cout << total << std::endl;
}
