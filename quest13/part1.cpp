/*

0 a0
n-1 b0
1 a1
n-2 b1
2 a2
n-3 b2

Take numbers with index % 2 == 1,  those form the first n/2 numbers
Take remaining numbers (index % 2 == 0) and reverse them.  They form the remaining n/2 numbers

*/
#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    std::vector<int> numbers(lines.size());
    auto i = 0;
    for (const auto &line : lines)
        numbers[i++]=std::stoi(line);

    auto dialSize = 1 + lines.size();
    auto finalDial = 2025 % dialSize;

    if (finalDial == 0)
    {
        std::cout << 1 << std::endl;
    }
    else if (finalDial == (dialSize/2)) 
    {
        // Final digit   
        std::cout << lines[lines.size()-1] << std::endl;
    }

    else if (finalDial < (dialSize/2))
    {
        auto index = (finalDial-1) * 2;
        std::cout << lines[index] << std::endl;
    }
    else
    {
        auto index = (finalDial-1) / 2;
        auto p = ( lines.size() - 1 ) / 2;
        auto i = ( p - index);
        i *=2;
        i++;
        std::cout << lines[i] << std::endl;
    }


    //196
    // 329
}