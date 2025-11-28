#include "common.cpp"
#include "queue"
#include "map"

// Draw volcano at r=1
// From S - storest path to each of the left-hand-size of @
// From each of those find shortest paths to bottom of @
// From each of those find shortest paths to right of @
// From each of those find shortest paths back to S
// Is the shortest path,  short enough?
// Yes solution,  No increase r

typedef struct vertex
{
    int index;
    int cost;
};

int main()
{
    auto lines = readLinesFromFile("sample3a.txt");
    auto height = lines.size();
    auto width = lines[0].size();
    
    auto start_index = 0;
    
    auto Xv = width/2;
    auto Yv = height/2;
    
    // Build vector of times
    std::vector<int> times;
    for(auto y=0;y<height;y++)
    {
        for(auto x=0;x<width;x++)    
        {
            if (lines[y][x] == 'S')
            {
                start_index = (y*width)+x;                
                times.push_back(0);
            }
            else if (lines[y][x] == '@')
            {
                //Volcano   
                Xv = x;
                Yv = y;       
                times.push_back(9999);   
            }
            else
                times.push_back(lines[y][x] - '0');   
        }
    }

    // Label all points with the minimum distance the radius needs to be to destroy that point.
    std::vector<int> destroyed_at;
    for(auto i=0;i<width*height;i++)
        destroyed_at.push_back(9999);

    auto radius = 1;
    while (radius <= (width/2) && radius <= (height/2))
    {
        auto total = 0;
        for(auto Yc=0;Yc<height;Yc++)
        {
            for(auto Xc=0;Xc<width;Xc++)    
            {
                auto index = (width * Yc) + Xc;
                if (destroyed_at[index] == 9999)
                {
                    auto lhs = (Xv - Xc) * (Xv - Xc) + (Yv - Yc) * (Yv - Yc);
                    auto rhs = radius * radius;
                    if (lhs <= rhs && lhs != 0)
                        destroyed_at[index] = radius;
                }
            }
        }
        radius++;
    }
    destroyed_at[start_index] = 0;


    radius = 1;
    while (radius <= width/2)
    {
        // All routes from S to underneath the volcano

        const int UNDEFINED_DIST = -1;
        const int INFINITY_COST = 100000; //std::numeric_limits<int>().max();
        auto cmp = [](vertex left, vertex right) { return (left.cost) > (right.cost); };


        //side=0 means lhs,   side=1 means rhs
        std::vector<int> lhs;
        std::vector<int> rhs;
        for(auto side=0;side<=1;side++)
        {
            std::priority_queue<vertex, std::vector<vertex>, decltype(cmp)> Q(cmp);
            std::vector<int> prev;
            std::vector<int> dist;
            
            for(auto v=0;v<width*height;v++)
            {
                dist.push_back(INFINITY_COST);
                prev.push_back(UNDEFINED_DIST);            
                if (v != start_index)
                    Q.emplace(v,INFINITY_COST);
            }

            Q.emplace(start_index,0);


            dist[start_index] = 0;

            while (!Q.empty())
            {
                auto u = Q.top();
                Q.pop();

                auto index = u.index;
                auto x = index % width;
                auto y = (index - x) / width;
                
                //Up
                auto v = index-width;
                if (y>0 && (destroyed_at[v] > radius) )
                {
                    auto alt = dist[u.index] + times[v];
                    if (alt < dist[v])
                    {
                        prev[v] = u.index;
                        dist[v] = alt;
                        Q.emplace(v,alt); //Q.decrease_priority(v, alt)
                    }
                }

                //Down
                v = index+width;
                if (y<(height-1) && (destroyed_at[v] > radius) )
                {
                    auto alt = dist[u.index] + times[v];
                    if (alt < dist[v])
                    {
                        prev[v] = u.index;
                        dist[v] = alt;
                        Q.emplace(v,alt); //Q.decrease_priority(v, alt)
                    }
                }

                //Left
                v = index-1;

                auto ok = ((side == 0) && (x>0)) 
                  //     || ((side == 1) && (y != Yv) && (x>=Xv - 1))
                       || ((side == 1) && (x>=Xv));

                if (x>0 && (destroyed_at[v] > radius) )
                {
                    auto alt = dist[u.index] + times[v];
                    if (alt < dist[v])
                    {
                        prev[v] = u.index;
                        dist[v] = alt;
                        Q.emplace(v,alt); //Q.decrease_priority(v, alt)
                    }
                }

                //Right
                v = index+1;
                ok = ((side == 0) && (x<Xv)) 
                    //   || ((side == 0) && (y != Yv) && (x < Xv + 1))
                       || ((side == 1) && (x<(width-1)));
                if (ok && (destroyed_at[v] > radius) )
                {
                    auto alt = dist[u.index] + times[v];
                    if (alt < dist[v])
                    {
                        prev[v] = u.index;
                        dist[v] = alt;
                        Q.emplace(v,alt); //Q.decrease_priority(v, alt)
                    }
                }
            }
            
            for(auto targetY=Yv+1;targetY<=height;targetY++)
            {
                auto time = dist[(targetY*width)+Xv];
                if (destroyed_at[(targetY*width)+Xv] <= radius)
                    time = -2;

                if (side == 0)
                    lhs.push_back(time);
                else
                    rhs.push_back(time);                

                // auto caption = side == 0 ? "LHS " : "RHS ";
                // std::cout << caption << radius << ' ' << targetY << " (" << times[(targetY*width)+Xv] << ") " << dist[(targetY*width)+Xv] << std::endl;
            }
        }

        auto j = 0;
        for(auto targetY=Yv+1;targetY<=height;targetY++)
        {
            if (destroyed_at[(targetY*width)+Xv] > radius)
            {
                auto total = lhs[j] + rhs[j] - times[(targetY*width)+Xv];
                auto seconds = total / 30;
                if (seconds <= radius)
                {
                    //44270
                    //44118
                    std::cout << total * seconds << std::endl;
                    return -1;
                }
            }
            j++;
        }

        radius++;
    }
}
