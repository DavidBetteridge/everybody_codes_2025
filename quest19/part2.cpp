#include "common.cpp"

struct gap
{
    int y;
    int cost;
};

struct layer
{
    int x_position;
    std::vector<gap> gaps;
};

int main()
{
    auto lines = readLinesFromFile("input3.txt");

    std::vector<layer> layers;

    layer layer0;
    layer0.x_position = 0;
    layer0.gaps.emplace_back(0,0);
    layers.push_back(layer0);

    for(const auto &line : lines)
    {
        auto parts = splitToInt(line, ",");

        if (layers[layers.size()-1].x_position == parts[0])
        {
            // Continue bulding layer
            for(auto i=0; i< parts[2];i++)
                layers[layers.size()-1].gaps.emplace_back(parts[1]+i,0);
        }
        else
        {
            //New layer
            layer layer;
            layer.x_position = parts[0];
            for(auto i=0; i< parts[2];i++)
                layer.gaps.emplace_back(parts[1]+i,0);

            layers.push_back(layer);
        }
    }


    for(auto layer_number=1;layer_number<layers.size();layer_number++)
    {
        // Going between layers[layer_number-1] and layers[layer_number]
        auto layer0x = layers[layer_number-1].x_position;
        auto layer1x = layers[layer_number].x_position;
        auto h_distance = layer1x - layer0x;
        for(auto i=0;i<layers[layer_number].gaps.size();i++)
        {
            // We want to find the shortest route from layer0[j] to layer[i]
            long bestTotal = 10000000;//std::numeric_limits<int>().max();
            for(auto j=0;j<layers[layer_number-1].gaps.size();j++)
            {   
                if (layers[layer_number-1].gaps[j].cost >= 10000000) continue;
                auto v_distance = layers[layer_number].gaps[i].y - layers[layer_number-1].gaps[j].y;

                // So, ups + downs == h_distance
                // We need to travel from layer0.y to layer1.y

                if ((h_distance % 2) != mod(v_distance,2))
                    // Not solveable
                    continue;

                auto ups = (h_distance / 2.0) + (v_distance / 2.0);
                if (ups < 0 || ups > h_distance)
                    // Not solveable
                    continue;

                long total = layers[layer_number-1].gaps[j].cost + ups;

                if (total < bestTotal)
                    bestTotal = total;
            }
            layers[layer_number].gaps[i].cost = bestTotal;
        }
    }

    auto lowest = 10000000;
    for(const auto &layer : layers[layers.size()-1].gaps)
    {
        if (layer.cost < lowest)
            lowest = layer.cost;
    }

    std::cout << lowest << std::endl;
    return 0;
}