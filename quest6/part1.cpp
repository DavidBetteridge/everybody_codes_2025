#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto line = lines[0];

    auto mentors = 0;
    auto pairs = 0;
    for(auto i=0; i<line.size(); i++)
    {
        if (line[i] == 'A')
            mentors++;
        else if (line[i] == 'a')
        {
            pairs += mentors;
        }

    }
    std::cout << pairs << std::endl;
    return 0;

}