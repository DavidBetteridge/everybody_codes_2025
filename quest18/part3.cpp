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

struct result
{
    long min = 0;
    long max = 0;
};

result calculate_incoming_energy(const std::vector<plant>& plants, const plant& current_plant)
{
    result totals;
    for(auto branch : current_plant.branches)
    {
        if (branch.is_free)
        {
            totals.max += branch.thickness;
        }
        else
        {
            auto parent_energy = calculate_incoming_energy(plants, plants[branch.parent_number-1]);
            auto incoming_energy_min = parent_energy.min * branch.thickness;
            auto incoming_energy_max = parent_energy.max * branch.thickness;
            
            if (incoming_energy_min < incoming_energy_max)
            {
                totals.min += incoming_energy_min;
                totals.max += incoming_energy_max;
            }
            else
            {
                totals.min += incoming_energy_max;
                totals.max += incoming_energy_min;
            }            
        }
    }

    if (totals.min < current_plant.thickness)
        totals.min = 0;

    if (totals.max < current_plant.thickness)
        totals.max = 0;

    return totals;
}

int main()
{

    auto lines = readLinesFromFile("input3.txt");

    std::smatch match;
    std::regex plant_regex("Plant (\\d+) with thickness (-?\\d+):", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex free_branch_regex("- free branch with thickness (-?\\d+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex branch_regex("- branch to Plant (\\d+) with thickness (-?\\d+)", std::regex_constants::ECMAScript | std::regex_constants::icase);

    std::vector<plant> plants;
    std::vector<std::string> test_cases;

  //  std::cout << "graph TD;" << std::endl;

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

         //   std::cout << "    " << current_branch.parent_number << "-->" << (plantNumber+1) << ';' << std::endl;
        }     
        
        if (line.starts_with('0') || line.starts_with('1'))
            test_cases.push_back(line);
    }

    for (const auto &plant : plants)
    {
        std::cout << plant.number << std::endl;

        for (const auto &child : plants)
        {
            for (const auto &branch : child.branches)
            {
                if (branch.parent_number == plant.number)
                {
                    std::cout << child.number << "  Thickness: " << branch.thickness << std::endl;
                }
            }
        }

        std::cout << std::endl;
    }

    // We assume for now that the last plant is the output.
    auto total = calculate_incoming_energy(plants, plants[plantNumber]);

    std::cout << total.min << ' ' << total.max << std::endl;

}



//4054945833095
//405494584647