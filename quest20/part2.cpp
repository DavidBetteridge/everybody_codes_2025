#include "queue"
#include "unordered_set"
#include "common.cpp"

struct pos
{
    int x;
    int y;
    int cost;
};

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto width = lines[0].size();
    auto height = lines.size();

    // Find the start and finish
    auto start_x = -1;
    auto start_y = -1;
    auto end_x = -1;
    auto end_y = -1;

    std::vector<bool> pixels;
    for(auto line_number=0;line_number<height;line_number++)
    {
        for(auto col_number=0;col_number<width;col_number++)
        {
            auto index = (line_number * width) + col_number;

            if (lines[line_number][col_number] == 'S')
            {
                start_x = col_number;
                start_y = line_number;
                pixels.push_back(true);
            }
            else if (lines[line_number][col_number] == 'E')
            {
                end_x = col_number;
                end_y = line_number;
                pixels.push_back(true);
            }    
            else
            {
                pixels.push_back(lines[line_number][col_number] == 'T');
            }        
        }
    }

    std::queue<pos> Q;
    std::unordered_set<int> seen;
    Q.emplace(start_x, start_y, 0); // Cost to get there.

    while (!Q.empty())
    {
        // Grab the top position from the stack and make sure we haven't already seen it.
        auto top = Q.front();
        Q.pop();

        auto index = (top.y * width) + top.x;
        if (seen.contains(index)) continue;;
        seen.insert(index);

        // Have we reached the end?
        if (top.x == end_x && top.y == end_y)
        {
            std::cout << top.cost << std::endl;
            return -1;
        }

        // Left
        if (top.x > 0 && pixels[index-1])
            Q.emplace(top.x-1, top.y, top.cost + 1);

        //Right
        if (top.x < (width-1) && pixels[index+1])
            Q.emplace(top.x+1, top.y, top.cost + 1);

        //Up
        if (top.y > 0 && (top.y % 2 == top.x % 2) && pixels[index-width])
            Q.emplace(top.x, top.y-1, top.cost + 1);

        //Down
        if (top.y < (height-1) && (top.y % 2 != top.x % 2) && pixels[index+width])
            Q.emplace(top.x, top.y+1, top.cost + 1);

    }
    
    std::cout << -1 << std::endl;
}