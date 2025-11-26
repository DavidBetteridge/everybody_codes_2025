#include "common.cpp"
#include <queue>
#include <map>

int main()
{
    auto lines = readLinesFromFile("input2.txt");
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
        auto dist = std::stoi(command.substr(1,command.size()-1));

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
    for(auto r=0;r<width * height;r++) {
        board[r]=false;  
    }

    currentX = -minX;
    currentY = -minY;    
    direction = 3;
    for (const auto &command : commands)
    {
        auto dir = command[0];
        auto dist = std::stoi(command.substr(1,command.size()-1));

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
    std::ofstream fout("board.txt");
    for(auto r=0;r<height;r++) {
        for(auto c=0;c<width;c++) {
            if (r == -minY && c == -minX)
                fout<< 'S';
            else if (r == currentY && c == currentX)
                fout<< 'E';
            else if (board[(r*width)+c])
                fout<< '#';
            else
                fout<< ' ';
        }
        fout<< std::endl;
    }
    fout<< std::endl;

    // Make sure the final position isn't wall
    board[(currentY*width)+currentX]=false;

    // Shortest path from -minX,-minY to currentX, currentY
    std::queue<std::pair<int,int>> queue;  // Position, Distance
    std::map<int, int> checked;

    queue.push(std::make_pair((-minY*width)+-minX,0));
    while (!queue.empty())
    {
        auto pos = queue.front();
        queue.pop();

        if (checked.contains(pos.first))
            continue;
        checked[pos.first]=0;

        auto x = pos.first % width;
        auto y = (pos.first - x) / width;


        if (x == currentX && y == currentY)
        {
            std::cout << pos.second << std::endl;
            return 0;
        }

        // Can we go West?
        if (x > 0)
        {
            auto loc = (y*width)+x-1;
            if (!board[loc])
                queue.push(std::make_pair(loc,pos.second+1));
        }

        // Can we go North?
        if (y > 0)
        {
            auto loc = ((y-1)*width)+x;
            if (!board[loc])
                queue.push(std::make_pair(loc,pos.second+1));
        }

        // Can we go South?
        if (y < (height-1))
        {
            auto loc = ((y+1)*width)+x;
            if (!board[loc])
                queue.push(std::make_pair(loc,pos.second+1));
        }

        // Can we go East?
        if (x < (width-1))
        {
            auto loc = (y*width)+x+1;
            if (!board[loc])
                queue.push(std::make_pair(loc,pos.second+1));
        }

    }
    
    std::cout << "No solution" << std::endl;

}