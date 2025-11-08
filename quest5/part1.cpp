#include <string>
#include <vector>
#include "common.cpp"

struct segment
{
    int left = 0;
    int spine = 0;
    int right = 0;
    segment* next = nullptr;
};

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto preamble = lines[0].find_first_of(":");
    auto notes = split(lines[0].substr(preamble+1), ",");

    std::vector<int> numbers;
    std::transform(notes.begin(), notes.end(), std::back_inserter(numbers), [](const std::string& str) { return std::stoi(str); });

    segment top;
    for (const auto &number : numbers)
    {
        
        bool allocated = false;
        segment* toCheck = &top;
        while (!allocated)
        {
            if (toCheck-> spine == 0)
            {
                toCheck->spine = number;
                allocated = true;
                std::cout << number;
            }
            else if (number < toCheck->spine && toCheck->left == 0)
            {
                toCheck->left = number;
                allocated = true;
            }
            else if (number > toCheck->spine && toCheck->right == 0)
            {
                toCheck->right = number;
                allocated = true;
            }
            else if (toCheck->next == nullptr)
            {
                segment* newSegment = new segment(); 
                newSegment->next = nullptr;
                newSegment->spine = number;
                toCheck->next = newSegment;
                allocated = true;
                std::cout << number;
            }
            else
            {
                toCheck = toCheck->next;
            }
        }
    }

    std::cout << std::endl;
    segment* walk = &top;
    while (walk != nullptr)
    {
        std::cout << walk->left << '-' << walk->spine << "-" << walk->right << std::endl;
        std::cout << "  |  " << std::endl;
        if (walk != &top)
            delete walk;
        walk = walk->next;
    }

}