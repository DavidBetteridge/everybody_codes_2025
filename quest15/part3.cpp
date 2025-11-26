#include "common.cpp"
#include <queue>
#include <map>
#include <set>

struct Corrd
{
    long x;
    long y;
};

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto commands = split(lines[0], ",");

    auto currentX = 0;
    auto currentY = 0;
    auto direction = 3;  // 0 = East, 1=South, 2=West. 3=North

    // First pass to find original corrdinates
    std::set<int> xs;
    std::set<int> ys;
    std::vector<Corrd> corrds;
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

        xs.insert(currentX);
        ys.insert(currentY);

        corrds.emplace_back(currentX, currentY);
    }

    // Second pass to compress the corrdinates
    std::map<long,long> xMapping;
    std::map<long,long> yMapping;
    auto index = 0;
    for (const auto &x : xs)
        xMapping[x] = index+=2;

    index = 0;
    for (const auto &y : ys)
        yMapping[y] = index+=2;

    std::vector<Corrd> compressedCorrds;
    for (const auto &corrd : corrds)
        compressedCorrds.emplace_back(xMapping[corrd.x], yMapping[corrd.y]);

    auto width = (xMapping.size()*2);
    auto height = (yMapping.size()*2);

    // Populate the board
    std::vector<bool> board(width * height);
    for(auto r=0;r<width * height;r++) {
        board[r]=false;  
    }

    // Start and end locations
    auto startX = xMapping[0];
    auto startY = yMapping[0];
    auto endX = xMapping[currentX];
    auto endY = yMapping[currentY];

    currentX = startX;
    currentY = startY;
    for (const auto &corrd : compressedCorrds)
    {
        if (currentX < corrd.x)
        {
            for(auto x=currentX;x<corrd.x;x++) {
                currentX++;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentX > corrd.x)
        {
            for(auto x=currentX;x>corrd.x;x--) {
                currentX--;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentY < corrd.y)
        {
            for(auto y=currentY;y<corrd.y;y++) {
                currentY++;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentY > corrd.y)
        {
            for(auto y=currentY;y>corrd.y;y--) {
                currentY--;
                board[(currentY*width)+currentX]=true;
            }
        }
    }

    std::cout << currentX << std::endl;
    std::cout << endX << std::endl;

    std::cout << currentY << std::endl;
    std::cout << endY << std::endl;
 

    // Display the board
    std::ofstream fout("board.txt");
    for(auto r=0;r<height;r++) {
        for(auto c=0;c<width;c++) {
            if (r == startY && c == startX)
                fout<< 'S';
            else if (r == endY && c == endX)
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
    board[(endY*width)+endX]=false;

    std::queue<std::pair<int,int>> queue;  // Position, Distance
    std::map<int, int> checked;

    queue.push(std::make_pair((startY*width)+startX, 0));
    while (!queue.empty())
    {
        auto pos = queue.front();
        queue.pop();

        if (checked.contains(pos.first))
            continue;
        checked[pos.first]=0;

        auto x = pos.first % width;
        auto y = (pos.first - x) / width;

        if (x == endX && y == endY)
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