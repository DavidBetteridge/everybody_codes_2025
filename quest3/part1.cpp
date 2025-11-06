#include "common.cpp"
#include <unordered_set>

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto crates = split(lines[0], ",");

    // Deduplicate
    std::unordered_set<int> s;
    for (std::string i : crates)
        s.insert(std::stoi(i));
    
    auto total = std::accumulate(s.begin(), s.end(), 0);
    std::cout << total << std::endl;
}