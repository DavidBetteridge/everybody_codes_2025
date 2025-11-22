#include "common.cpp"
#include <set>
#include <algorithm>

long moveDragon(const std::vector<int>& heights, std::vector<int>& sheep, int dragonX, int dragonY, std::string movesList);

static int width;
static int height;
static std::__1::vector<std::__1::string> board;

static std::array<std::pair<int,int>, 8> moves = {
    std::pair<int,int>(-2,-1 ),
    std::pair<int,int>(-2,+1 ),
    std::pair<int,int>(+2,-1 ),
    std::pair<int,int>(+2,+1 ),
    std::pair<int,int>(-1,-2 ),
    std::pair<int,int>(-1,+2 ),
    std::pair<int,int>(+1,-2 ),
    std::pair<int,int>(+1,+2 ),
};


static std::array<char, 8> letters = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'
};


long moveSheep(const std::vector<int>& heights, std::vector<int>& sheep, int dragonX, int dragonY, std::string movesList)

{
    long solutions = 0;

    // Sheep moves first.
    auto dragonMoved = false;
    auto allSheepDeadOrHiding = true;
    for(auto c=0; c<width; c++)
    {
        if (sheep[c] < -1)
        {
            std::cout << "oh" << std::endl;
        }

        if (sheep[c] == -1) continue;  // No sheep in column
        
        sheep[c]++;
        
        if (sheep[c] == heights[c])
        {
            // Sheep has escaped,  this isn't a valid solution
            sheep[c]--;
            continue;
        }

        if (sheep[c] == dragonY && c == dragonX && board[sheep[c]][c] != '#')
        {
            // Sheep has walked onto the dragon (and there isn't a hiding place)
            sheep[c]--;
            continue;            
        }

        allSheepDeadOrHiding = false;
        if (sheep[c] <= 0)
        {
            std::cout << "oh" << std::endl;
        }
        movesList = std::format("{0} S>{1}{2}", movesList, letters[c], (sheep[c]+1));

        solutions += moveDragon(heights, sheep, dragonX, dragonY, movesList);
        sheep[c]--;
        dragonMoved = true;
    }

    // Dragon always moves
    if (!dragonMoved && !allSheepDeadOrHiding)
        solutions += moveDragon(heights, sheep, dragonX, dragonY, movesList);

    return solutions;
}

long moveDragon(const std::vector<int>& heights, std::vector<int>& sheep, int dragonX, int dragonY, std::string movesList)
{
    long total = 0;
    for(auto m=0; m<8; m++)
    {
        auto x = dragonX + moves[m].first;
        auto y = dragonY + moves[m].second;

        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            movesList = std::format("{0} D>{1}{2}", movesList, letters[x], (y+1));
            auto originalSheepPosition = sheep[x];
            if (sheep[x] == y && board[y][x] != '#')
            {
                // We have eaten a sheep
                sheep[x] = -1;

                // If all the sheep have been eaten, then we have a solution
                bool sheepFound = false;
                for(auto c=0; c<width; c++)
                {
                    if (sheep[c] != -1)
                    {
                        sheepFound = true;
                        break;
                    }
                }

                if (!sheepFound)
                {
                    total++;
                    std::cout << movesList << std::endl;
                    continue;
                }
            }

            total += moveSheep(heights, sheep, x, y, movesList);

            sheep[x] = originalSheepPosition;
        }
    }

    return total;
}

int main()
{
    board = readLinesFromFile("sample3a.txt");
    width = board[0].size();
    height = board.size();

    // Find the dragon and sheep starting postion
    std::pair<int,int> dragon(-1,-1);
    std::vector<int> sheep(width);
    for(auto c=0; c<width; c++)
        sheep[c]=-1;

    for(auto r=0; r<height; r++)
    {
        for(auto c=0; c<width; c++)
        {
            if (board[r][c] == 'D')
            {
                dragon.first = c;
                dragon.second = r;
            }

            if (board[r][c] == 'S')
            {
                sheep[c] = r;
            }            
        }        
    }

    // Work out the heights of the columns by working up from the bottom,
    // we stop as soon as we reach a cell which isn't a hideout
    std::vector<int> heights(width);
    for(auto c=0; c<width; c++)
    {
        heights[c] = height;
        for(auto r=height-1; r>0; r--)
        {
            if (board[r][c] != '#')
                break;
            heights[c] = r;
        }
    }

    auto total = 0;
    total = moveSheep(heights, sheep, dragon.first, dragon.second, "");
    std::cout << total << std::endl;
}