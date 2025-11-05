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

    void Reset(long x, long y)
    {
        _x = x;
        _y = y;
    }

    // [X1,Y1] + [X2,Y2] = [X1 + X2, Y1 + Y2]
    Complex operator+(const Complex& n) const
    {
        auto lhs = n._x + _x;
        auto rhs = n._y + _y;
        return Complex(lhs, rhs );
    }

    void Add(const Complex& n)
    {
        _x = n._x + _x;
        _y = n._y + _y;
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

    void Mul(const Complex& n)
    {
        auto X1 = _x;
        auto Y1 = _y;
        auto X2 = n._x;
        auto Y2 = n._y;

        _x = X1 * X2 - Y1 * Y2;
        _y = X1 * Y2 + Y1 * X2;
    }

    // [X1,Y1] / [X2,Y2] = [X1 / X2, Y1 / Y2]
    Complex operator/(const Complex& n) const
    {
        auto lhs = std::floor(_x / n._x);
        auto rhs = std::floor(_y / n._y);
        return Complex(lhs, rhs );
    }

    void Div(const Complex& n)
    {
        _x = std::floor(_x / n._x);
        _y = std::floor(_y / n._y);
    }

    bool operator<(const Complex& n) const
    {
        return (_x < n._x) || (_y < n._y);
    }

    bool operator>(const Complex& n) const
    {
        return (_x > n._x) || (_y > n._y);
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
    const int left = -79097;
    const int top = -15068;

    Complex A(left,top); 
    Complex DivideBy(100000,100000);
    Complex Upper(1000000,1000000);
    Complex Lower(-1000000,-1000000);

    Complex P(0,0);
    Complex R(0,0);
    auto total = 0;
    for(auto x = 0; x < 1001; x++)
    {
        auto col = left + x;
        for(auto y = 0; y < 1001; y++)
        {
            P.Reset(col, top + y);
            R.Reset(0,0);

            auto engrave = true;
            for(auto round=0; (round<100) && engrave; round++)
            {
                R.Mul(R);
                R.Div(DivideBy);
                R.Add(P);

                if (R > Upper || R < Lower)
                {
                    engrave=false;
                }

            }
            if (engrave)
            {
                total++;
            }
        }
    }

    std::cout << total << std::endl;
}