#include "common.cpp"

static std::array<std::pair<int,int>, 4> diagonals = {
    std::pair<int,int>(-1,-1 ),
    std::pair<int,int>(-1,+1 ),
    std::pair<int,int>(+1,-1 ),
    std::pair<int,int>(+1,+1 ),
};

int main()
{

    const int width = 34;
    const int height = 34;
    const long rounds = 1000000000;
    static std::array<std::bitset<34>, 34> board1 = {0}; 
    static std::array<std::bitset<34>, 34> board2 = {0}; 


    static std::array<std::bitset<8>, 8> pattern = {0}; 
    auto lines = readLinesFromFile("input3.txt");
    for(auto row=0;row<8;row++)
    {
        for(auto column=0;column<8;column++)
        {
            pattern[row].set(column, lines[row][column] == '#');
        }
    }

    long total = 0;
    auto previousBoard = &board1;
    auto nextBoard = &board2;

    for(auto round=1000000000-10000;round<=rounds;round++)
    {
        auto activeTiles = 0;
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
                        activeTiles++;
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }
                else
                {
                    if (activeDiagonals % 2 == 0)
                    {
                        (*nextBoard)[row].set(column,true);
                        activeTiles++;
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }
            }
        }

        // Do we have a matching pattern
        auto matches = true;
        for(auto row=0;row<8;row++)
        {
            for(auto column=0;column<8;column++)
            {
                if (!(*nextBoard)[13+row].test(13+column) == pattern[row][column])
                {
                    matches = false;
                    break;
                }
            }
            if (!matches) break;
        }
        if (matches)
        {
            total++;
            std::cout << round << " (" << activeTiles << ") " << std::endl;
        }

        
        std::swap(previousBoard, nextBoard);
       
    }

    std::cout << total << std::endl;
    //1751404572

}