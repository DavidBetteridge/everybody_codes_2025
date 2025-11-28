#include "common.cpp"
#include <regex>

struct branch
{
    bool is_free;
    int parent_number;
    int thickness;    
};

struct plant
{
    int number;
    int thickness;
    std::vector<branch> branches;
};

int calculate_energy(const std::vector<plant>& plants, const plant& current_plant)
{
    auto incoming_energy = 0;
    for(auto branch : current_plant.branches)
    {
        auto branch_energy = 0;
        if (branch.is_free) 
            incoming_energy += branch.thickness;
        else
        {
            auto parent_energy = calculate_energy(plants, plants[branch.parent_number-1]);
            incoming_energy += parent_energy * branch.thickness;
        }
    }

    if (incoming_energy < current_plant.thickness)
        return 0;
    else
        return incoming_energy;
}

int main()
{

    auto lines = readLinesFromFile("input1.txt");

    std::smatch match;
    std::regex plant_regex("Plant (\\d+) with thickness (\\d+):", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex free_branch_regex("- free branch with thickness (\\d+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex branch_regex("- branch to Plant (\\d+) with thickness (\\d+)", std::regex_constants::ECMAScript | std::regex_constants::icase);

    std::vector<plant> plants;

    auto plantNumber = -1;
    for (const auto &line : lines)
    {
        if (std::regex_search(line, match, plant_regex)) {
            plant current_plant;
            current_plant.number = std::stoi(match[1]);
            current_plant.thickness = std::stoi(match[2]);
            plants.push_back(current_plant);
            plantNumber++;
        }

        if (std::regex_search(line, match, free_branch_regex)) {
            branch current_branch;
            current_branch.is_free = true;
            current_branch.thickness = std::stoi(match[1]);
            plants[plantNumber].branches.push_back(current_branch);
        }        

        if (std::regex_search(line, match, branch_regex)) {
            branch current_branch;
            current_branch.is_free = false;
            current_branch.parent_number = std::stoi(match[1]);
            current_branch.thickness = std::stoi(match[2]);
            plants[plantNumber].branches.push_back(current_branch);
        }        
    }

    // We assume for now that the last plant is the output.
    auto total = calculate_energy(plants, plants[plantNumber]);
    std::cout << total << std::endl;

}



