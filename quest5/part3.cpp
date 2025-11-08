#include <string>
#include <vector>
#include "common.cpp"
#include <algorithm>

struct segment
{
    int identifier = 0;  //Only set at the top level
    unsigned long quality = 0;  //Only set at the top level
    int left = 0;
    int spine = 0;
    int right = 0;
    std::unique_ptr<segment> next = nullptr;

    void print()
    {
        std::cout << left << '-' << spine << "-" << right << std::endl;
        if (next)
        {
            std::cout << "  |  " << std::endl;
            next->print();
        }
    }
};

segment* createSword(std::string line)
{
    auto preamble = line.find_first_of(":");
    auto notes = split(line.substr(preamble+1), ",");
    auto l = line.substr(0,preamble);
    auto identifier = std::stoi(l);
    std::vector<int> numbers;
    std::transform(notes.begin(), notes.end(), std::back_inserter(numbers), [](const std::string& str) { return std::stoi(str); });

    unsigned long quality = 0;
    segment* top = new segment(); 
    for (const auto &number : numbers)
    {
        
        bool allocated = false;
        segment* toCheck = top;
        while (!allocated)
        {
            if (toCheck-> spine == 0)
            {
                toCheck->spine = number;
                toCheck->identifier = identifier;
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
            else if (!toCheck->next)
            {
                toCheck->next = std::make_unique<segment>();
                toCheck->next->spine = number;
                allocated = true;
                quality = (quality * 10) + number;
            }
            else
            {
                toCheck = toCheck->next.get();
            }
        }
    }
    top->quality = quality;
    return top;
}

struct compare_swords
{
    inline bool operator() (const segment* sword1, const segment* sword2)
    {
        // Return True if sword1 is better than sword2

        if (sword1->quality != sword2->quality)
            return (sword1->quality > sword2->quality);

        // Compare row by row
        auto lhs = sword1;
        auto rhs = sword2;
        while (lhs)
        {
            long l = lhs->left;
            if (lhs->spine != 0)
                l = (l*10)+lhs->spine;
            if (lhs->right != 0)
                l = (l*10)+lhs->right;

           long r = rhs->left;
            if (rhs->spine != 0)
                r = (r*10)+rhs->spine;
            if (rhs->right != 0)
                r = (r*10)+rhs->right;

            if (l != r)
                return (l > r);

            lhs = lhs->next.get();
            rhs = rhs->next.get();
        }


        return (sword1->identifier > sword2->identifier);
    }
};


int main()
{
    auto lines = readLinesFromFile("input3.txt");

    std::vector<segment*> swords;
    for (const auto &line : lines)
    {
        swords.insert(swords.begin(), createSword(line));
    }

    std::sort(swords.begin(), swords.end(), compare_swords());

    unsigned long checksum = 0;
    auto position = 0;
    for (const auto &sword : swords)
    {
        checksum += (++position * sword->identifier);
        

        if (sword->identifier == 314 || sword->identifier == 347)
        {
            std::cout << sword->identifier << std::endl;
            sword->print();
        }

    }

    std::cout << checksum << std::endl;

    return 0;
}