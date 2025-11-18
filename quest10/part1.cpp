#include "common.cpp"
#include <set>

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

static int width;
static int height;


void eatSheep(std::set<std::pair<int,int>>& eaten, const std::__1::vector<std::__1::string>& board, int dragonX, int dragonY, int rounds)
{
    for(auto m=0; m<8; m++)
    {
        auto x = dragonX + moves[m].first;
        auto y = dragonY + moves[m].second;

        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            if (board[y][x] == 'S')
            {
                std::pair<int,int> sheep(x,y);
                eaten.insert(sheep);
            }

            if (rounds > 1)
                eatSheep(eaten, board, x,y, rounds-1);
        }
    }
}

int main()
{
    const int rounds = 4;
    auto board = readLinesFromFile("input1.txt");
    width = board[0].size();
    height = board.size();

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


    std::set<std::pair<int,int>> eaten;
    eatSheep(eaten, board, dragon.first, dragon.second, rounds);

    std::cout << eaten.size() << std::endl;


}