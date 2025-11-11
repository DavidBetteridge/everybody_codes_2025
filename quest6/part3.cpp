#include "common.cpp"

int countMentors(std::string line, char mentor, int lhs, int rhs)
{
    auto pairs = 0;
    for(auto i=lhs; i<=rhs; i++)
    {
        if (line[i] == mentor)
            pairs++;
    }
    return pairs;
}

int main()
{
    const int distance = 10;
    auto lines = readLinesFromFile("sample3.txt");
    auto line = lines[0];

    auto pairs = 0;

    // Segment 0
    for(auto i=0; i<line.size(); i++)
    {
        if (line[i] == 'a')
            pairs += countMentors(line, 'A', std::max(0, i - distance), i + distance);

        if (line[i] == 'b')
            pairs += countMentors(line, 'B', std::max(0, i - distance), i + distance);

        if (line[i] == 'c')
            pairs += countMentors(line, 'C', std::max(0, i - distance), i + distance);            

    }
    
    std::cout << pairs << std::endl;
    return 0;

}