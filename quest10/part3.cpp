#include "common.cpp"
#include <set>

long moveDragon(int dragonX, int dragonY, int living_sheep);

static size_t width;
static size_t height;
static std::vector<bool> hide_outs;
static std::vector<size_t> heights;
static std::vector<int> sheep;

static std::array<int, 8> moves_x = {
    -1,
    -2,
    +2,
    +2,
    -1,
    +1,
    +1,
    -2,
};

static std::array<int, 8> moves_y = {
    +2,
    +1,
    -1,
    +1,
    -2,
    -2,
    +2,
    -1,
};

long moveSheep(const  int dragonX,const  int dragonY, const int living_sheep)
{
    long solutions = 0;

    // Sheep moves first.
    auto dragonMoved = false;
    auto at_least_one_sheep_is_blocked = false;
    auto at_least_one_sheep_has_won = false;
    for(auto c=0; c<width; c++)
    {
        if (sheep[c] == -1) continue;  // No sheep in column

        const auto originalSheepPosition = sheep[c];

        sheep[c]++;

        if (sheep[c] == heights[c])
        {
            // Sheep has escaped,  this isn't a valid solution as the dragon cannot win
            sheep[c]=originalSheepPosition;
            at_least_one_sheep_has_won = true;
            continue;
        }

        if (sheep[c] == dragonY && c == dragonX && !hide_outs[(width * sheep[c]) + c])
        {
            // Sheep has walked onto the dragon (and there isn't a hiding place)
            at_least_one_sheep_is_blocked = true;
            sheep[c]=originalSheepPosition;
            continue;
        }

        solutions += moveDragon(dragonX, dragonY, living_sheep);
        sheep[c]=originalSheepPosition;
        dragonMoved = true;
    }

    // Dragon always moves
    if (!dragonMoved && at_least_one_sheep_is_blocked && !at_least_one_sheep_has_won)
        solutions += moveDragon(dragonX, dragonY, living_sheep);

    return solutions;
}

long moveDragon(const int dragonX, const int dragonY, const int living_sheep)
{
    long total = 0;
    for(auto m=0; m<8; m++)
    {
        const auto x = dragonX + moves_x[m];
        const auto y = dragonY + moves_y[m];

        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            if (sheep[x] == y && !hide_outs[(width * y) + x])
            {
                // We have eaten a sheep
                if (living_sheep == 1)
                {
                    // No sheep left
                    total++;
                    continue;
                }

                const auto originalSheepPosition = sheep[x];
                sheep[x] = -1;
                total += moveSheep(x, y, living_sheep-1);
                sheep[x] = originalSheepPosition;
            }
            else
                total += moveSheep(x, y, living_sheep);
        }
    }

    return total;
}

int main()
{
    const auto board = readLinesFromFile("sample3d.txt");
    width = board[0].size();
    height = board.size();

    // Find the dragon and sheep starting position
    std::pair<int,int> dragon(-1,-1);
    sheep.resize(width);
    for(auto c=0; c<width; c++)
        sheep[c]=-1;

    int living_sheep = 0;
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
                living_sheep++;
            }
            hide_outs.push_back(board[r][c] == '#');
        }        
    }

    // Work out the heights of the columns by working up from the bottom,
    // we stop as soon as we reach a cell which isn't a hideout
    heights.resize(width);
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

    long total = 0;
    total = moveSheep(dragon.first, dragon.second, living_sheep);
    std::cout << total << std::endl;
}