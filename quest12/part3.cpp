#include "common.cpp"
#include <queue>
#include <map>
#include <unordered_set>


long scoreAttempt(int width, int height, const std::string& barrels, int startPosition, std::unordered_set<int>& seen, std::unordered_set<int>& destroyed, bool destroyBarrel)
{
    std::queue<int> q;
    std::unordered_set<int> path;
    q.push(startPosition);

    auto total = 0;
    while (!q.empty())
    {
        int top = q.front();
        q.pop();

        if (path.contains(top) || destroyed.contains(top))
            continue;

        if (destroyBarrel)
            destroyed.insert(top);
        seen.insert(top);
        path.insert(top);
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

    return total;
}

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto width = lines[0].size();
    auto height = lines.size();
    std::string barrels;
    for (const auto &line : lines)
        barrels+=line;


    std::unordered_set<int> destroyed;


    long total= 0;

    std::unordered_set<int> skip;

    for(auto n=0; n<3;n++)
    {
        skip.clear();        
        long bestScore = 0;
        long bestBarrel = 0;

        for(auto p=0; p<barrels.size();p++)
        {
            if (!skip.contains(p))
            {
                auto score = scoreAttempt(width, height, barrels, p, skip, destroyed, false);
                if (score>bestScore)
                {
                    bestScore=score;
                    bestBarrel=p;
                }
            }
        }
        
        skip.clear();
        total += scoreAttempt(width, height, barrels, bestBarrel, skip, destroyed, true);
    }

    std::cout << total << std::endl;

}