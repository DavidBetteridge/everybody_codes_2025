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


inline int mod(int a, int b) {
    int ret = a % b;
    return ret >= 0 ? ret : ret + b;
}


int main()
{
    std::ifstream file("input3.txt");
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