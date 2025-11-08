#include <string>
#include <vector>
#include "common.cpp"

struct segment
{
    int left = 0;
    int spine = 0;
    int right = 0;
    segment* next = nullptr;

    void print()
    {
        std::cout << left << '-' << spine << "-" << right << std::endl;
        if (next != nullptr)
        {
            std::cout << "  |  " << std::endl;
            next->print();
        }
    }

    void printSpine()
    {
        std::cout << spine;
        if (next != nullptr)
            next->printSpine();
    }

};

long long score(std::string line)
{
    auto preamble = line.find_first_of(":");
    auto notes = split(line.substr(preamble+1), ",");

    std::vector<int> numbers;
    std::transform(notes.begin(), notes.end(), std::back_inserter(numbers), [](const std::string& str) { return std::stoi(str); });

    long long quality = 0;
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
                quality = number;
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
                quality = (quality * 10) + number;
            }
            else
            {
                toCheck = toCheck->next;
            }
        }
    }

    return quality;
}

int main()
{
    auto lines = readLinesFromFile("input2.txt");

    long long max_quality = 0;
    long long min_quality = LLONG_MAX;
    for (const auto &line : lines)
    {
        auto quality = score(line);

        if (quality > max_quality)
            max_quality = quality;

        if (quality < min_quality)
            min_quality = quality;
    }

    std::cout << max_quality - min_quality << std::endl;

    return 0;
}