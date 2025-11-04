#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto words = split(lines[0], ",");
    auto instructions = split(lines[2], ",");

    for (const auto &instruction : instructions)
    {
        auto direction = instruction.substr(0,1);
        auto distance =  std::stoi(instruction.substr(1));

        if (direction == "L") 
        {
            auto wordIndex = mod(-distance, words.size());
            auto temp = words[0];
            words[0] = words[wordIndex];
            words[wordIndex] = temp;
        }
        else
        {
            auto wordIndex = distance % words.size();
            auto temp = words[0];
            words[0] = words[wordIndex];
            words[wordIndex] = temp;            
        }
    }

    std::cout << words[0] << std::endl;
    return 0;
}