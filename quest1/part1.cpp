#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto words = split(lines[0], ",");
    auto instructions = split(lines[2], ",");

    auto wordIndex = 0;
    for (const auto &instruction : instructions)
    {
        auto direction = instruction.substr(0,1);
        auto distance =  std::stoi(instruction.substr(1));

        if (direction == "L") 
        {
            wordIndex -= distance;
            if (wordIndex < 0) wordIndex = 0;
        }
        else
        {
            wordIndex += distance;
            if (wordIndex >= words.size()) wordIndex = words.size() - 1;
        }
    }

    std::cout << words[wordIndex] << std::endl;
    return 0;
}