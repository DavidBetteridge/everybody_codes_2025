#include "common.cpp"
#include <map>

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto words = split(lines[0], ",");

    std::map<char, std::string> rules;
    for(auto n=2; n<lines.size(); n++) 
    {
        auto rule = split(lines[n], " > ");
        rules[rule[0][0]] = rule[1];
    }


    auto indice = 0;
    auto total = 0;
    for (const auto &word : words)
    {
        indice++;
        auto ok = true;
        for(auto k=0; k<word.size()-1;k++)
        {
            if (rules.contains(word[k]))
            {
                auto rule = rules[word[k]];
                if (!rule.contains(word[k+1]))
                    ok = false;
            }
            else
                ok = false;

            if (!ok) break;
        }

        if (ok)
        {
            total += indice;
            std::cout << word << std::endl;
        }
    }

    std::cout << total << std::endl;
    return 0;
}