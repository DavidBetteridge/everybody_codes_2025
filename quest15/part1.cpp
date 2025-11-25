#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto commands = split(lines[0], ",");


    auto currentX = 0;
    auto currentY = 0;
    auto direction = 3;  // 0 = East, 1=South, 2=West. 3=North

    // First pass to find out the size of the world
    auto maxX = 0;
    auto maxY = 0;
    auto minX = 0;
    auto minY = 0;
    for (const auto &command : commands)
    {
        auto dir = command[0];
        auto dist = std::stoi(command.substr(1,1));

        if (dir == 'L')
            direction = mod(direction - 1, 4);
        else
            direction = mod(direction + 1,4);

        if (direction == 0) currentX+=dist; //East
        if (direction == 1) currentY+=dist; //South
        if (direction == 2) currentX-=dist; //West
        if (direction == 3) currentY-=dist; //North

        if (currentX < minX) minX = currentX;
        if (currentY < minY) minY = currentY;
        if (currentX > maxX) maxX = currentX;
        if (currentY > maxY) maxY = currentY;
    }
    auto width = maxX - minX + 1;
    auto height = maxY - minY + 1;

    // Populate the board
    std::vector<bool> board(width * height);
    currentX = -minX;
    currentY = -minY;    
    direction = 3;
    for (const auto &command : commands)
    {
        auto dir = command[0];
        auto dist = std::stoi(command.substr(1,1));

        if (dir == 'L')
            direction = mod(direction - 1, 4);
        else
            direction = mod(direction + 1,4);

        //East
        if (direction == 0) 
        {
            for(auto i=0;i<dist;i++) {
                currentX++;
                board[(currentY*width)+currentX]=true;
            }
        }
        
        //South
        if (direction == 1) 
        {
            for(auto i=0;i<dist;i++) {
                currentY++;
                board[(currentY*width)+currentX]=true;
            }
        }

        //West
        if (direction == 2) 
        {
            for(auto i=0;i<dist;i++) {
                currentX--;
                board[(currentY*width)+currentX]=true;
            }
        }

        //North
        if (direction == 3) 
        {
            for(auto i=0;i<dist;i++) {
                currentY--;
                board[(currentY*width)+currentX]=true;
            }
        }

    }

    // Display the board
    for(auto r=0;r<height;r++) {
        for(auto c=0;c<width;c++) {
            if (r == -minY && c == -minX)
                std::cout << 'S';
            else if (r == currentY && c == currentX)
                std::cout << 'E';
            else if (board[(r*width)+c])
                std::cout << '#';
            else
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}