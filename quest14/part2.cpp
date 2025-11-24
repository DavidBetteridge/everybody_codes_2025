#include "common.cpp"

static std::array<std::pair<int,int>, 4> diagonals = {
    std::pair<int,int>(-1,-1 ),
    std::pair<int,int>(-1,+1 ),
    std::pair<int,int>(+1,-1 ),
    std::pair<int,int>(+1,+1 ),
};

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto width = lines[0].size();
    auto height = lines.size();
    std::string tiles;
    for (const auto &line : lines)
        tiles+=line;

    auto total = 0;
    for(auto round=0;round<2025;round++)
    {
        std::string nextTiles;

        for(auto i=0;i<tiles.size();i++)
        {
            auto x = i % width;
            auto y = (i - x) / width;

            auto activeDiagonals = 0;
            for (const auto &diagonal : diagonals)
            {
                auto newX = x + diagonal.first;
                auto newY = y + diagonal.second;
                if (newX >= 0 && newY >= 0 && newX < width && newY < height )
                {
                    auto index = (newY * width) + newX;
                    if (tiles[index] == '#')
                        activeDiagonals++;                    
                }
            }
            if (tiles[i] == '#')
            {
                if (activeDiagonals % 2 == 1)
                {
                    nextTiles+='#';
                    total++;
                }
                else
                    nextTiles+='.';
            }
            else
            {
                if (activeDiagonals % 2 == 0)
                {
                    nextTiles+='#';
                    total++;
                }
                else
                    nextTiles+='.';
            }
        }

        tiles = nextTiles;
        
    }

    std::cout << total << std::endl;

}