#include "common.cpp"

struct dialRange
{
    int start;
    int finish;

    dialRange(int s, int f) : start(s), finish(f) {}

    int distance()
    {
        return finish - start + 1;
    }
};

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    std::vector<dialRange*> rawRanges(lines.size());
    
    auto i = 0;
    auto totalNumbers = 0;
    for (const auto &line : lines)
    {
        auto parts = splitToInt(line, "-");
        dialRange* r = new dialRange(parts[0], parts[1]);
        rawRanges[i++] = r;
        totalNumbers+=(r->distance());
    }


    long finalPosition = 202520252025 % (totalNumbers + 1);
    
    if (finalPosition == 0)
        return 1;




    auto nextRangeNumber = 0;
    auto increase = 2;
    long target = finalPosition - 1;

    while (true)
    {
    
        std::cout << target << " " << rawRanges[nextRangeNumber]->distance() << " " << std::endl;

        if (rawRanges[nextRangeNumber]->distance() <= target)
        {
            target-=rawRanges[nextRangeNumber]->distance();
            nextRangeNumber+=increase;

            if (nextRangeNumber >= rawRanges.size() )
            {
                increase=-2;
                nextRangeNumber-=1;
            }
        }
        else
        {
            std::cout << target << " " << rawRanges[nextRangeNumber]->start << "-" << rawRanges[nextRangeNumber]->finish  << " " << std::endl;
            if (increase > 0)
                std::cout << rawRanges[nextRangeNumber]->start + target << " " << std::endl;
            else
                std::cout << rawRanges[nextRangeNumber]->finish - target << " " << std::endl;
            break;
        }
        
    }

    return 0;
}