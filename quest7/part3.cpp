#include "common.cpp"
#include <map>
#include <unordered_map>
#include <vector>

int count(std::map<char, std::vector<char>>& rules, std::string word, std::unordered_map<std::string, int>& seen)
{
    auto total = 0;
    auto length = word.size();
    auto letter = word[length-1];

    if (seen.contains(word)) return 0;

    if (length >= 7 && length <= 11)
    {
        total++;
        seen[word]=0;
    }

    if (length < 11)
    {
        if (rules.contains(letter))
        {
            auto nextChars = rules[letter];
            for (const auto &next : nextChars)
            {
                total += count(rules, word + next, seen);
            }
        }
    }

    return total;
}

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto words = split(lines[0], ",");

    std::map<char, std::vector<char>> rules;
    for(auto n=2; n<lines.size(); n++) 
    {
        auto rule = split(lines[n], " > ");
        auto next = split_to_char(rule[1], ",");
        rules[rule[0][0]] = next;
    }


    auto indice = 0;
    auto total = 0;
    std::unordered_map<std::string, int> seen;
    for (const auto &word : words)
    {
        indice++;
        auto ok = true;
        for(auto k=0; k<word.size()-1;k++)
        {
            if (rules.contains(word[k]))
            {
                auto rule = rules[word[k]];

                if(std::find(rule.begin(), rule.end(), word[k+1]) == rule.end())
                    ok = false;
            }
            else
                ok = false;

            if (!ok) break;
        }

        if (ok)
        {
            // Prefix is valid
            total += count(rules, word, seen);
        }
    }

    //4425012
    std::cout << total << std::endl;
    return 0;
}