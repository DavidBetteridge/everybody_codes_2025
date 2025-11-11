#include "common.cpp"

int countMentors(std::string line, char mentor, int lhs, int rhs)
{
    auto pairs = 0;
    int segmentLength = line.size();
    for(auto i=lhs; i<=rhs; i++)
    {
        if (line[mod(i, segmentLength)] == mentor)
            pairs++;
    }
    return pairs;
}

int main()
{
    const int distance = 1000;
    const int repeats = 1000;
    auto lines = readLinesFromFile("input3.txt");
    auto line = lines[0];
    int segmentLength = line.size();
    auto pairs = 0;

    // Segments 1 ---> 999
    for(auto i=0; i<line.size(); i++)
    {
        if (line[i] == 'a')
            pairs += countMentors(line, 'A', i - distance, i + distance);

        if (line[i] == 'b')
            pairs += countMentors(line, 'B', i - distance, i + distance);

        if (line[i] == 'c')
            pairs += countMentors(line, 'C', i - distance, i + distance);            
    }
    pairs *= (repeats - 2);

    // Segment 0
    for(auto i=0; i<segmentLength; i++)
    {
        if (line[i] == 'a')
            pairs += countMentors(line, 'A', std::max(0, i - distance), i + distance);

        if (line[i] == 'b')
            pairs += countMentors(line, 'B', std::max(0, i - distance), i + distance);

        if (line[i] == 'c')
            pairs += countMentors(line, 'C', std::max(0, i - distance), i + distance);            
    }

    // Segment n
    for(auto i=0; i<segmentLength; i++)
    {
        if (line[i] == 'a')
            pairs += countMentors(line, 'A', i - distance, std::min(segmentLength-1, i + distance));

        if (line[i] == 'b')
            pairs += countMentors(line, 'B', i - distance, std::min(segmentLength-1, i + distance));

        if (line[i] == 'c')
            pairs += countMentors(line, 'C', i - distance, std::min(segmentLength-1, i + distance));            
    }

    //1666695604
    std::cout << pairs << std::endl;
    return 0;

}