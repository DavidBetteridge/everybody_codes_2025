#include "common.cpp"

struct gap
{
    int y;
    int cost;
};

int main()
{
    auto lines = readLinesFromFile("input1.txt");

    auto layer0x = 0;
    std::vector<gap> layer0;
    layer0.emplace_back(0,0);

    for(const auto &line : lines)
    {
        auto parts = splitToInt(line, ",");
        auto layer1x = parts[0];

        std::vector<gap> layer1;
        for(auto i=0; i< parts[2];i++)
            layer1.emplace_back(parts[1]+i,0);

        auto h_distance = layer1x - layer0x;
        for(auto i=0;i<layer1.size();i++)
        {
            // We want to find the shortest route from layer0[j] to layer[i]
            auto bestTotal = 10000;//std::numeric_limits<int>().max();
            for(auto j=0;j<layer0.size();j++)
            {   
                auto v_distance = layer1[i].y - layer0[j].y;

                // So, ups + downs == h_distance
                // We need to travel from layer0.y to layer1.y

                if ((h_distance % 2) != mod(v_distance,2))
                    // Not solveable
                    continue;

                auto ups = (h_distance / 2.0) + (v_distance / 2.0);
                if (ups < 0 || ups > h_distance)
                    // Not solveable
                    continue;

                auto total = layer0[j].cost + ups;

                if (total < bestTotal)
                    bestTotal = total;
            }
            layer1[i].cost = bestTotal;
        }

        layer0 = layer1;
        layer0x = layer1x;
    }

    auto lowest = 10000;
    for(const auto &layer : layer0)
    {
        if (layer.cost < lowest)
            lowest = layer.cost;
    }

    std::cout << lowest << std::endl;
    return 0;
}