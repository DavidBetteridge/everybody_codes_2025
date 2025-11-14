#include "common.cpp"
#include <map>

bool isChild(std::vector<std::string>& lines, int child, int parent1, int parent2)
{
    auto parent1Matches = 0;
    auto parent2Matches = 0;
    for(auto s=0; s<lines[0].size(); s++)
    {
        if (lines[child][s] != lines[parent1][s] && lines[child][s] != lines[parent2][s])
            return false;
    }

    return true;
}

int createFamily(std::vector<std::vector<int>>& families, int duck1, int duck2, int duck3)
{
    std::vector<int> newFamily({duck1, duck2, duck3});
    families.push_back(newFamily);
    return families.size() - 1;
}

void addToFamily(std::vector<std::vector<int>>& families, int familyId, int duck)
{
    families[familyId].push_back(duck);
}

int familyContaining(std::vector<std::vector<int>>& families, int duck)
{
    for(auto c=0; c<families.size(); c++)
    {
        auto family = families[c];
        if(std::find(family.begin(), family.end(), duck) != family.end()) {
            return c;
        }
    }
    return -1;
}


void mergeFamilies(std::vector<std::vector<int>>& families, int familyId1, int familyId2)
{
    // Add all entries from family2 into family1,  and remove family2
    auto source = families[familyId2];
    for(auto c=0; c<source.size(); c++)
        families[familyId1].push_back(source[c]);
    families[familyId2].clear();
}

int main()
{
    std::vector<std::vector<int>> families;

    auto lines = readLinesFromFile("input3.txt");
    for(auto c=0; c<lines.size(); c++)
    {
        lines[c] = split(lines[c],":")[1];
    }

    for(auto c=0; c<lines.size(); c++)
    {
        auto parentsFound = false;
        for(auto p1=0; p1<lines.size()-1; p1++)
        { 
            if (c != p1)
            {
                for(auto p2=p1+1; p2<lines.size(); p2++)
                {
                   if (c != p2)
                    {
                        // Can P1 and P2 be parents of C
                        if (isChild(lines, c, p1, p2))
                        {
                            // c, p1, and p2 now all belong to the same family.
                            auto baseFamily = familyContaining(families, c);
                            if (baseFamily == -1)
                                baseFamily = familyContaining(families, p1);
                            if (baseFamily == -1)
                                baseFamily = familyContaining(families, p2);
                            if (baseFamily == -1)
                                baseFamily = createFamily(families, c, p1, p2);


                            auto cFamily = familyContaining(families, c);
                            if (cFamily == -1)
                                addToFamily(families, baseFamily, c);
                            else if (cFamily != baseFamily)
                                mergeFamilies(families, baseFamily, cFamily);
                            
                            auto p1Family = familyContaining(families, p1);
                            if (p1Family == -1)
                                addToFamily(families, baseFamily, p1);
                            else if (p1Family != baseFamily)
                                mergeFamilies(families, baseFamily, p1Family);


                            auto p2Family = familyContaining(families, p2);
                            if (p2Family == -1)
                                addToFamily(families, baseFamily, p2);
                            else if (p2Family != baseFamily)
                                mergeFamilies(families, baseFamily, p2Family);

                            parentsFound = true;
                            break;
                        }
                    }
                }
            }
            if (parentsFound) break;
        }
    }

    auto largestFamily = 0;
    for(auto c=0; c<families.size(); c++)
    {
        if (families[c].size() > families[largestFamily].size())
            largestFamily = c;
    }

    long total = 0;
    for(auto c=0; c<families[largestFamily].size(); c++)
        total += families[largestFamily][c] + 1;

    std::cout << total << std::endl;

}