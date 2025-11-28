#include "common.cpp"

static int start_index;
static int width;
static int height;
static int Xv;
static int Yv;
static std::vector<int> destroyed_at;
static std::vector<int> times;
static int printCount = 0;

std::vector<int> get_available_moves(int current_index)
{
    std::vector<int> moves;

    auto x = current_index % width;
    auto y = (current_index - x) / width;

    auto down = false;
    auto up = false;
    auto left = false;
    auto right = false;

    if (x <= Xv && y <= Yv)
    {
        down=true;
        left=true;
    }

    if (x <= Xv && y > Yv)
    {
        down=true;
        right=true;
    }

    if (x > Xv && y >= Yv)
    {
        up=true;
        right=true;
    }
    
    if (x > Xv && y < Yv)
    {
        up=true;
        left=true;
    }

    //Down
    if (down && (y < (height-1)))
        moves.push_back(current_index + width);

    //Up
    if (up && (y > 0))
        moves.push_back(current_index - width);

    //Left
    if (left && (x > 0) )
        moves.push_back(current_index - 1);

    //Right
    if (right && (x < (width - 1)))
        moves.push_back(current_index + 1);

    return moves;
}

int check(int min_surviable_distance, int current_index, int time_to_date)
{
    if (current_index == start_index && time_to_date > 0)
    {
        // We have returned to the start!
        std::cout << "Solution " << time_to_date << std::endl;
        return time_to_date;
    }

    // Include this cell in our route
    if (destroyed_at[current_index] < min_surviable_distance)
        min_surviable_distance = destroyed_at[current_index];
    time_to_date += times[current_index];
    auto radius = floor(time_to_date / 30);

    // auto x = current_index % width;
    // auto y = (current_index - x) / width;
    // std::cout << "min_surviable_distance=" << min_surviable_distance << " x=" << x << " y=" << y << " (" <<  times[current_index] << ")" << " time_to_date=" << time_to_date << std::endl;
    // printCount++;
    // if (printCount>20) exit(0);


    // Has the volcano destroyed our path?
    if (radius >= min_surviable_distance)
    {
        // std::cout << "Destroyed " << time_to_date << std::endl;
        return -1;
    }


    auto possible_routes = get_available_moves(current_index);
    auto best_score = -1;
    for (const auto &possible_route : possible_routes)
    {
        auto score = check(min_surviable_distance, possible_route, time_to_date);
        if (score != -1 && score < best_score)
        {
            best_score = score;
            std::cout << "New best " << best_score << std::endl;
        }
    }

    return best_score;
}

int main()
{
    auto lines = readLinesFromFile("sample3a.txt");
    width = lines.size();
    height = lines[0].size();

    Xv = width/2;
    Yv = height/2;

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


    // First we label all points with the minimum distance the 
    // radius needs to be to destroy that point.
    for(auto i=0;i<width*height;i++)
        destroyed_at.push_back(0);


    auto radius = 1;
    while (radius <= (width/2) && radius <= (height/2))
    {
        auto total = 0;
        for(auto Yc=0;Yc<height;Yc++)
        {
            for(auto Xc=0;Xc<width;Xc++)    
            {
                auto index = (width * Yc) + Xc;
                if (destroyed_at[index] == 0)
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

    // Display destroyed_at
    // for(auto Yc=0;Yc<height;Yc++)
    // {
    //     for(auto Xc=0;Xc<width;Xc++)    
    //     {
    //         auto index = (width * Yc) + Xc;
    //         std::cout << destroyed_at[index];
    //     }
    //     std::cout << std::endl;
    // }
    auto score = check(width, start_index, 0);
    std::cout << score << std::endl;
}
