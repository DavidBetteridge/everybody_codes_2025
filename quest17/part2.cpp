#include "common.cpp"

int main()
{
    auto lines = readLinesFromFile("input2.txt");
    auto width = lines.size();
    auto height = lines[0].size();

    auto Xv = width/2;
    auto Yv = height/2;
    auto radius = 1;

    auto best = 0;
    auto bestR = 0;
    auto previousTotal = 0;
    while (radius < (width/2) && radius < (height/2))
    {
        auto total = 0;
        for(auto Yc=0;Yc<height;Yc++)
        {
            for(auto Xc=0;Xc<width;Xc++)    
            {
                auto lhs = (Xv - Xc) * (Xv - Xc) + (Yv - Yc) * (Yv - Yc);
                auto rhs = radius * radius;
                if (lhs <= rhs && lhs != 0)
                {
                    auto val = lines[Yc][Xc]-'0';
                    total+=val;
                }
            }
        }

        if ((total - previousTotal) > best) {
            best = total - previousTotal;
            bestR = radius;
        }

        previousTotal = total;
        radius++;
    }
    
    std::cout << best * bestR << std::endl;
}
