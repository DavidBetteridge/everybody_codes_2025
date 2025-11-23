/*

    Put corrds of top left on the stack.  (could be a simple int x + height * width)
    while stack is not empty
        pop top
        barrels++
        if n < X push n
        if n < X push n
        if n < X push n
        if n < X push n
*/

#include "common.cpp"
#include <queue>
#include <map>
#include <unordered_set>

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto width = lines[0].size();
    auto height = lines.size();
    std::string barrels;
    for (const auto &line : lines)
        barrels+=line;

    std::unordered_set<int> seen;
    std::queue<int> q;
    q.push(0);

    auto total = 0;
    while (!q.empty())
    {
        int top = q.front();
        q.pop();

        if (seen.contains(top))
            continue;

        seen.insert(top);
        total++;

        auto x = top % width;
        auto y = (top - x) / width;

        if (y > 0)
        {
            auto n = ((y -1) * width)+x;
            if (barrels[n] <= barrels[top])
                q.push(n);
        }

        if (y < (height-1))
        {
            auto s = ((y +1) * width)+x;
            if (barrels[s] <= barrels[top])
                q.push(s);
        }

        if (x > 0)
        {
            auto w = (y * width)+x-1;
            if (barrels[w] <= barrels[top])
                q.push(w);
        }

        if (x < (width-1))
        {
            auto e = (y * width)+x+1;
            if (barrels[e] <= barrels[top])
                q.push(e);
        }

    }

    std::cout << total << std::endl;
}