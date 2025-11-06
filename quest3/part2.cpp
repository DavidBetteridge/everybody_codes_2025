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

    // Grab the 20 smallest...
    std::vector<int> smallest(s.size());
    std::copy_n(s.begin(), 20, smallest.begin());

    // ...and sum
    auto total = std::accumulate(smallest.begin(), smallest.end(), 0);
    std::cout << total << std::endl;
}