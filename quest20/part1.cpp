#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto width = lines[0].size();

    auto total = 0;
    for(auto line_number=0;line_number<lines.size();line_number++)
    {
        for(auto col_number=line_number;col_number<(width-line_number);col_number++)
        {
            if (lines[line_number][col_number] == 'T')
            {
                if (col_number<(width-1) && lines[line_number][col_number+1] == 'T')
                    total++;

                if (line_number > 0 && (line_number % 2 == col_number % 2))
                {
                    // Check previous line
                    if (lines[line_number-1][col_number] == 'T')
                        total++;
                }
            }
        }     

        
    }
    std::cout << total << std::endl;

}