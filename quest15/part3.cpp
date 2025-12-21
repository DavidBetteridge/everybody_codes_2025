#include "common.cpp"
#include <queue>
#include <map>
#include <set>

struct Corrd
{
    long x;
    long y;

    Corrd(const long x,const long y) : x(x), y(y) {};
};

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto commands = split(lines[0], ",");

    long currentX = 0;
    long currentY = 0;
    auto direction = 3;  // 0 = East, 1=South, 2=West. 3=North

    // First pass to find original coordinates
    std::set<long> xs;
    std::set<long> ys;
    std::vector<Corrd> coordinates;
    for (const auto &command : commands)
    {
        auto dir = command[0];
        long dist = std::stol(command.substr(1,command.size()-1));

        if (dir == 'L')
            direction = mod(direction - 1, 4);
        else
            direction = mod(direction + 1,4);

        if (direction == 0) currentX+=dist; //East
        if (direction == 1) currentY+=dist; //South
        if (direction == 2) currentX-=dist; //West
        if (direction == 3) currentY-=dist; //North

        xs.insert(currentX-1);
        xs.insert(currentX);
        xs.insert(currentX+1);

        ys.insert(currentY-1);
        ys.insert(currentY);
        ys.insert(currentY+1);

        coordinates.emplace_back(currentX, currentY);
    }


    // Second pass to compress the coordinates
    std::map<long,long> x_old_to_new;
    std::map<long,long> y_old_to_new;

    std::map<long,long> x_new_to_old;
    std::map<long,long> y_new_to_old;

    long previous = 0;
    for (const auto &x : xs) {
        x_old_to_new[x] = previous;
        x_new_to_old[previous]=x;
        previous++;
    }
    long width = previous+1;

    previous = 0;
    for (const auto &y : ys) {
        y_old_to_new[y] = previous;
        y_new_to_old[previous]=y;
        previous++;
    }
    long height = previous+1;

    // Populate the board
    std::vector<bool> board(width * height);
    for(long r=0;r<width * height;r++) {
        board[r]=false;  
    }

    // Start and end locations (in compressed form)
    long startX = x_old_to_new[0];
    long startY = y_old_to_new[0];
    long endX = x_old_to_new[currentX];
    long endY = y_old_to_new[currentY];

    // Build the compressed maze
    currentX = startX;
    currentY = startY;
    for (const auto &coordinate : coordinates)
    {
        long c_x = x_old_to_new[coordinate.x];
        long c_y = y_old_to_new[coordinate.y];

        if (currentX < c_x)
        {
            for(auto x=currentX;x<c_x;x++) {
                currentX++;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentX > c_x)
        {
            for(auto x=currentX;x>c_x;x--) {
                currentX--;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentY < c_y)
        {
            for(auto y=currentY;y<c_y;y++) {
                currentY++;
                board[(currentY*width)+currentX]=true;
            }
        }

        if (currentY > c_y)
        {
            for(auto y=currentY;y>c_y;y--) {
                currentY--;
                board[(currentY*width)+currentX]=true;
            }
        }
    }

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

    std::queue<std::pair<long,long>> queue;  // Position, Distance
    std::map<long, int> checked;

    queue.emplace((startY*width)+startX, 0);
    while (!queue.empty())
    {
        auto pos = queue.front();
        queue.pop();

        if (checked.find(pos.first) != checked.end())
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
            if (!board[loc]) {
                auto offset = (x_new_to_old[(x)] - x_new_to_old[x-1]);
                queue.emplace(loc,pos.second+offset);
            }
        }
        // Can we go East?
        if (x < (width-1))
        {
            auto loc = (y*width)+x+1;
            if (!board[loc]) {
                auto offset = (x_new_to_old[x+1] - x_new_to_old[x]);
                queue.emplace(loc,pos.second+offset);
            }
        }

        // Can we go North?
        if (y > 0)
        {
            auto loc = ((y-1)*width)+x;
            if (!board[loc]) {
                auto offset = (y_new_to_old[(y)] - y_new_to_old[y-1]);
                queue.emplace(loc,pos.second+offset);
            }
        }

        // Can we go South?
        if (y < (height-1))
        {
            auto loc = ((y+1)*width)+x;
            if (!board[loc]) {
                auto offset = (y_new_to_old[y+1] - y_new_to_old[y]);
                queue.emplace(loc,pos.second+offset);
            }
        }



    }
    
    std::cout << "No solution" << std::endl;

}