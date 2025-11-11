#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto line = lines[0];

    auto mentorsA = 0;
    auto mentorsB = 0;
    auto mentorsC = 0;
    auto pairs = 0;
    for(auto i=0; i<line.size(); i++)
    {
        if (line[i] == 'A')
            mentorsA++;
        if (line[i] == 'B')
            mentorsB++;
        if (line[i] == 'C')
            mentorsC++;            
        if (line[i] == 'a')
            pairs += mentorsA;
        if (line[i] == 'b')
            pairs += mentorsB;
        if (line[i] == 'c')
            pairs += mentorsC;                        

    }
    std::cout << pairs << std::endl;
    return 0;

}