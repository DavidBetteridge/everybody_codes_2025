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

    
    static std::array<std::bitset<34>, 34> board1 = {0}; 
    static std::array<std::bitset<34>, 34> board2 = {0}; 

    auto total = 0;
    auto previousBoard = &board1;
    auto nextBoard = &board2;

    for(auto round=0;round<1000000000;round++)
    {
        for(auto row=0;row<34;row++)
        {
            for(auto column=0;column<34;column++)
            {

                // Count active diagonals 
                auto activeDiagonals = 0;
                for (const auto &diagonal : diagonals)
                {
                    auto newX = column + diagonal.first;
                    auto newY = row + diagonal.second;
                    if (newX >= 0 && newY >= 0 && newX < 34 && newY < 34 )
                    {
                        auto index = (newY * 34) + newX;
                        if ((*previousBoard)[newY].test(newX))
                            activeDiagonals++;                    
                    }
                }

                if ((*previousBoard)[row].test(column))
                {
                    if (activeDiagonals % 2 == 1)
                    {
                        (*nextBoard)[row].set(column,true);
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }
                else
                {
                    if (activeDiagonals % 2 == 0)
                    {
                        (*nextBoard)[row].set(column,true);
                    }
                    else
                        (*nextBoard)[row].set(column,false);
                }


            }
        }
        std::swap(previousBoard, nextBoard);
       
    }

    std::cout << total << std::endl;

}