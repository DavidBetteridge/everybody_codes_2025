#include <iostream>
#include <fstream>
#include <numeric>
#include <ranges>
#include <vector>
#include <stdexcept>


std::vector<std::string> split(std::string text, std::string sep)
{
    std::vector<std::string> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        list.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    return list;
}


int main()
{
    std::ifstream file("input1.txt");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        return 0;
    }

    std::string wordsLine;
    std::string temp;
    std::string instructionsLine;
    std::getline(file, wordsLine);
    std::getline(file, temp);
    std::getline(file, instructionsLine);

    auto words = split(wordsLine, ",");
    auto instructions = split(instructionsLine, ",");

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