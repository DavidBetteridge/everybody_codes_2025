#include "common.cpp"

static std::array<std::pair<int,int>, 4> diagonals = {
    std::pair<int,int>(-1,-1 ),
    std::pair<int,int>(-1,+1 ),
    std::pair<int,int>(+1,-1 ),
    std::pair<int,int>(+1,+1 ),
};

int main()
{
    static std::array<std::bitset<34>, 34> board1 = {0}; 
    static std::array<std::bitset<34>, 34> board2 = {0}; 
    const int width = 34;
    const int height = 34;

    auto lines = readLinesFromFile("input2.txt");
    const long rounds = 2025;
    for(auto row=0;row<height;row++)
    {
        for(auto column=0;column<width;column++)
        {
            board1[row].set(column, lines[row][column] == '#');
        }
    }

    long total = 0;
    auto previousBoard = &board1;
    auto nextBoard = &board2;

    for(auto round=0;round<rounds;round++)
    {
        for(auto row=0;row<height;row++)
        {
            for(auto column=0;column<width;column++)
            {

                // Count active diagonals 
                auto activeDiagonals = 0;
                for (const auto &diagonal : diagonals)
                {
                    auto newX = column + diagonal.first;
                    auto newY = row + diagonal.second;
                    if (newX >= 0 && newY >= 0 && newX < width && newY < height )
                    {
                        if ((*previousBoard)[newY].test(newX))
                            activeDiagonals++;                    
                    }
                }

                if ((*previousBoard)[row].test(column))
                {
                    if (activeDiagonals % 2 == 1)
                    {
                        (*nextBoard)[row].set(column,true);
                        total++;
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }
                else
                {
                    if (activeDiagonals % 2 == 0)
                    {
                        (*nextBoard)[row].set(column,true);
                        total++;
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }
            }
        }

        std::cout << total << std::endl;
        std::swap(previousBoard, nextBoard);
       
    }

    std::cout << total << std::endl;

}