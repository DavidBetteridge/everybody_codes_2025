#include "common.cpp"
#include <map>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>

int count(std::map<char, std::vector<char>>& rules, char letter, int length)
{
    auto total = 0;
    if (length >= 7 && length <= 11)
    {
        total++;
    }

    if (length < 11)
    {
        if (rules.contains(letter))
        {
            auto nextChars = rules[letter];
            for (const auto &next : nextChars)
            {
                total += count(rules, next, length + 1);
            }
        }
    }

    return total;
}

int main()
{
    auto lines = readLinesFromFile("input3.txt");
    auto words = split(lines[0], ",");

    std::sort(words.begin(), words.end(), [] (const std::string& first, const std::string& second){ return first.size() < second.size(); });

    std::map<char, std::vector<char>> rules;
    for(auto n=2; n<lines.size(); n++) 
    {
        auto rule = split(lines[n], " > ");
        auto next = split_to_char(rule[1], ",");
        rules[rule[0][0]] = next;
    }


    auto total = 0;
    std::unordered_set<std::string> seen;
    for (const auto &word : words)
    {
        auto ok = true;

        // Have we already processed a prefix of this work
        for (const auto &prefix : seen)
        {
            if (word.substr(0, prefix.size()) == prefix)
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
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
            seen.insert(word);
        }
        
        if (ok)
        {
            // Prefix is valid
            total += count(rules, word[word.size()-1], word.size());
        }
    }

    //4425012
    std::cout << total << std::endl;
    return 0;
}