#include <iostream>
#include <ostream>

class Complex
{
private:
    long _x;
    long _y;

public:

    Complex(long x, long y) : _x(x), _y(y)
    {
    }   

    // [X1,Y1] + [X2,Y2] = [X1 + X2, Y1 + Y2]
    Complex operator+(const Complex& n) const
    {
        auto lhs = n._x + _x;
        auto rhs = n._y + _y;
        return Complex(lhs, rhs );
    }

    long X()
    {
        return _x;
    }

    long Y()
    {
        return _y;
    }

    // [X1,Y1] * [X2,Y2] = [X1 * X2 - Y1 * Y2, X1 * Y2 + Y1 * X2]
    Complex operator*(const Complex& n) const
    {
        auto X1 = _x;
        auto Y1 = _y;
        auto X2 = n._x;
        auto Y2 = n._y;

        auto lhs = X1 * X2 - Y1 * Y2;
        auto rhs = X1 * Y2 + Y1 * X2;

        return Complex(lhs, rhs );
    }

    // [X1,Y1] / [X2,Y2] = [X1 / X2, Y1 / Y2]
    Complex operator/(const Complex& n) const
    {
        auto lhs = std::floor(_x / n._x);
        auto rhs = std::floor(_y / n._y);
        return Complex(lhs, rhs );
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);

};

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    os << '[' <<  complex._x << ','  << complex._y  << ']';
    return os;
}


int main()
{
    Complex A(35300,-64910); // A=[-79097,-15068]
    Complex Size(1000,1000);
    Complex DivideBy(100000,100000);

    Complex BottonRight = A + Size;

    auto total = 0;
    for(auto x = 0; x < 101; x++)
    {
        auto col = A.X() + (x * 10);
        for(auto y = 0; y < 101; y++)
        {
            auto row = A.Y() + (y * 10);

            Complex P(col,row);
            Complex R(0,0);

            auto engrave = true;
            for(auto round=0; round<100; round++)
            {
                R = R * R;
                R = R / DivideBy;
                R = R + P;

                if (R.X() > 1000000 || R.X() <  -1000000 || R.Y()> 1000000 || R.Y() <  -1000000)
                {
                    engrave=false;
                    break;
                }

            }
            if (engrave)
            {
                total++;
                std::cout << 'x';
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }

    std::cout << total << std::endl;
}