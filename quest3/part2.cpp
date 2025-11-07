#include "common.cpp"
#include <set>

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto crates = split(lines[0], ",");

    // Deduplicate and sort
    std::set<int> s;
    for (std::string i : crates)
        s.insert(std::stoi(i));

    auto total2 = std::accumulate(s.begin(), std::next(s.begin(), 20), 0);    
    std::cout << total2 << std::endl;
   
}