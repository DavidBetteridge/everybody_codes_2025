#include "common.cpp"

static std::array<std::pair<int,int>, 4> diagonals = {
    std::pair<int,int>(-1,-1 ),
    std::pair<int,int>(-1,+1 ),
    std::pair<int,int>(+1,-1 ),
    std::pair<int,int>(+1,+1 ),
};

// 13 8 13

int main()
{
    auto lines = readLinesFromFile("sample3.txt");
    // auto width = lines[0].size();
    // auto height = lines.size();
    // std::string tiles;
    // for (const auto &line : lines)
    //     tiles+=line;

    const int size = 34 * 34;
    static std::array<bool, 34*34> board = {0}; 

    auto total = 0;
    for(auto round=0;round<1000000000;round++)
    {
        static std::array<bool, 34*34> nextBoard = {0}; 

        for(auto i=0;i<size;i++)
        {
            auto x = i % 34;
            auto y = (i - x) / 34;

            auto activeDiagonals = 0;
            for (const auto &diagonal : diagonals)
            {
                auto newX = x + diagonal.first;
                auto newY = y + diagonal.second;
                if (newX >= 0 && newY >= 0 && newX < 34 && newY < 34 )
                {
                    auto index = (newY * 34) + newX;
                    if (board[index])
                        activeDiagonals++;                    
                }
            }
            if (board[i])
            {
                if (activeDiagonals % 2 == 1)
                {
                    nextBoard[i] = true;
                    total++;
                }
                else
                    nextBoard[i] = false;
            }
            else
            {
                if (activeDiagonals % 2 == 0)
                {
                    nextBoard[i] = true;
                    total++;
                }
                else
                    nextBoard[i] = false;
            }
        }

        board = nextBoard;
        
    }

    std::cout << total << std::endl;

}