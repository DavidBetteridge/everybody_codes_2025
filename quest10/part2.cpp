#include "common.cpp"
#include <set>
#include <algorithm>

static int width;
static int height;
static std::__1::vector<std::__1::string> board;

bool canBeEaten(int dragonX, int dragonY,int c, int r, int moves)
{
    // Can the dragon get here in round knights moves?
    auto dx = abs(dragonX - c);
    auto dy = abs(dragonY - r);
    if (dx < dy) std::swap(dx,dy);

    auto d_min = -1;
    if (dx == 0 && dy == 0) d_min=0;
    else if (dx == 1 && dy == 0) d_min=3;
    else if (dx == 2 && dy == 2) d_min=4;
    else
    {
        int a = (dx + 1) / 2;          // ceil(dx/2)
        int b = (dx + dy + 2) / 3;     // ceil((dx+dy)/3)
        int d = std::max(a, b);
        if (d % 2 != (dx+dy) % 2)
            d_min = d +1;
        else
            d_min = d;
    }

    return (moves >= d_min) &&  ((moves - d_min) % 2) == 0;    
}

int main()
{
    const int rounds = 20;
    board = readLinesFromFile("input2.txt");
    width = board[0].size();
    height = board.size();

    // Find the dragons starting postion
    std::pair<int,int> dragon(-1,-1);
    for(auto r=0; r<height; r++)
    {
        for(auto c=0; c<width; c++)
        {
            if (board[r][c] == 'D')
            {
                dragon.first = c;
                dragon.second = r;
                break;
            }
        }        
        if (dragon.first != -1) break;
    }


    // Check each sheep in turn to see if it's eaten or escapes
    auto escaped = 0;
    std::set<std::pair<int,int>> eaten;

    for(auto round=0; round<rounds; round++)
    {
        for(auto r=0; r<height; r++)
        {
            for(auto c=0; c<width; c++)
            {
                if (board[r][c] == 'S')
                {
                    auto newR = r + round;
                    if (newR > height)
                    {
                        //Escaped
                        continue;
                    }

                    // Dragon already moved - so round+1
                    auto reachable = canBeEaten(dragon.first, dragon.second, c, newR, round+1);
                    if (reachable)
                    {
                        if (board[newR][c] == '#')
                        {
                            continue;
                        }
                        else
                        {
                            eaten.insert(std::make_pair(r,c));
                            continue;
                        }                        
                    }

                    // Dragon already moved - so round+1
                    reachable = canBeEaten(dragon.first, dragon.second, c, newR+1, round+1);
                    if (reachable)
                    {
                        if (board[newR+1][c] == '#')
                        {
                            continue;
                        }
                        else
                        {
                            eaten.insert(std::make_pair(r,c));
                            continue;
                        }                        
                    }

                }
            }
        }    
    }

    std::cout << eaten.size() << std::endl;
}