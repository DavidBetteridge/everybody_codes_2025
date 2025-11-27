#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input1.txt");
    auto width = lines.size();
    auto height = lines[0].size();

    auto Xv = width/2;
    auto Yv = height/2;

    auto total = 0;
    for(auto Yc=0;Yc<height;Yc++)
    {
        for(auto Xc=0;Xc<width;Xc++)    
        {
            auto lhs = (Xv - Xc) * (Xv - Xc) + (Yv - Yc) * (Yv - Yc);
            auto rhs = 10 * 10;
            if (lhs <= rhs && lhs != 0)
            {
                auto val = lines[Yc][Xc]-'0';
                total+=val;
                std::cout << val;
                
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }


    std::cout << total;
}
