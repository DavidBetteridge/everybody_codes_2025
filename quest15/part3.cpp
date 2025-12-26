#include <cassert>

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

struct vertex
{
    long index;
    long cost;

    vertex(const long index,const long cost) : index(index), cost(cost) {};
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
    auto command_count = 0;
    xs.insert(0);
    ys.insert(0);
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

        command_count++;

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
    long width = previous-1;

    previous = 0;
    for (const auto &y : ys) {
        y_old_to_new[y] = previous;
        y_new_to_old[previous]=y;
        previous++;
    }
    long height = previous-1;

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

    // Make sure the final position isn't wall
    auto end_index = (endY*width)+endX;
    board[end_index]=false;



    const long UNDEFINED_DIST = -1;
    const long INFINITY_COST = 1000000000;
    auto cmp = [](const vertex left, const vertex right) { return (left.cost) > (right.cost); };
    std::priority_queue<vertex, std::vector<vertex>, decltype(cmp)> Q(cmp);
    std::vector<long> prev;
    std::vector<long> dist;

    auto start_index = (startY*width)+startX;
    // std::vector<bool> visited(width * height, false);
    for(long v=0;v<width*height;v++)
    {
        dist.push_back(INFINITY_COST);
        prev.push_back(UNDEFINED_DIST);
        // if (v != start_index)
        //     Q.emplace(v,INFINITY_COST);
    }

    Q.emplace(start_index,0);

    dist[start_index] = 0;

    while (!Q.empty()) {
        auto u = Q.top();
        Q.pop();

        if (u.cost != dist[u.index])
            continue;

        // if (visited[u.index]) continue;
        // visited[u.index] = true;

        auto index = u.index;
        auto x = index % width;
        auto y = (index - x) / width;

        // Can we go North?
        auto v = index-width;
        if (y>0 && !board[v])
        {
            long cost = (y_new_to_old[(y)] - y_new_to_old[y-1]);
            if (cost < 0) {
                std::cout << y_new_to_old[(y)] - y_new_to_old[y-1] << std::endl;
                assert(false);
            }
            long  alt = dist[u.index] + cost;
            if (alt < dist[v])
            {
                prev[v] = u.index;
                dist[v] = alt;
                Q.emplace(v,alt); //Q.decrease_priority(v, alt)
            }
        }

        //Down
        v = index+width;
        if (y<(height-1) && !board[v])
        {
            long  cost = (y_new_to_old[y+1] - y_new_to_old[y]);
            assert(cost > 0);
            long  alt = dist[u.index] + cost;
            if (alt < dist[v])
            {
                prev[v] = u.index;
                dist[v] = alt;
                Q.emplace(v,alt); //Q.decrease_priority(v, alt)
            }
        }

        //Left
        v = index-1;
        if ((x>0) && !board[v] )
        {
            long  cost = (x_new_to_old[(x)] - x_new_to_old[x-1]);
            assert(cost > 0);
            long  alt = dist[u.index] + cost;
            if (alt < dist[v])
            {
                prev[v] = u.index;
                dist[v] = alt;
                Q.emplace(v,alt); //Q.decrease_priority(v, alt)
            }
        }

        //Right
        v = index+1;
        if ((x<(width-1)) && !board[v])
        {
            long  cost = (x_new_to_old[x+1] - x_new_to_old[x]);
            assert(cost > 0);
            long  alt = dist[u.index] + cost;
            if (alt < dist[v])
            {
                prev[v] = u.index;
                dist[v] = alt;
                Q.emplace(v,alt); //Q.decrease_priority(v, alt)
            }
        }
    }

    if (dist[end_index] == INFINITY_COST) {
        std::cout << "No path to end\n";
        return 0;
    }

    // Display the path to the end point
    auto location = end_index;
    std::set<long> path;
    while (location != start_index) {
        path.insert(location);
        location = prev[location];
    }

    // Display the board
    std::ofstream fout2("board2txt");
    for(auto r=0;r<height;r++) {
        for(auto c=0;c<width;c++) {
            long loc = (r*width)+c;
            if (path.find(loc) != path.end() )
                fout2<< 'X';
            else if (r == startY && c == startX)
                fout2<< 'S';
            else if (r == endY && c == endX)
                fout2<< 'E';
            else if (board[(r*width)+c])
                fout2<< '#';
            else
                fout2<< ' ';
        }
        fout2<< std::endl;
    }

    std::cout << dist[end_index] << std::endl;
}