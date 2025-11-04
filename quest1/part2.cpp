#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto words = split(lines[0], ",");
    auto instructions = split(lines[2], ",");

    auto wordIndex = 0;
    for (const auto &instruction : instructions)
    {
        auto direction = instruction.substr(0,1);
        auto distance =  std::stoi(instruction.substr(1));

        if (direction == "L") 
        {
            wordIndex = mod(wordIndex - distance, words.size());
        }
        else
        {
            wordIndex = (wordIndex + distance) % words.size();
        }
    }

    std::cout << words[wordIndex] << std::endl;
    return 0;
}