#include <iostream>
#include <ostream>

class Complex
{
private:
    int _x;
    int _y;

public:

    Complex(int x, int y) : _x(x), _y(y)
    {
    }   

    // [X1,Y1] + [X2,Y2] = [X1 + X2, Y1 + Y2]
    Complex operator+(const Complex& n)
    {
        auto lhs = n._x + _x;
        auto rhs = n._y + _y;
        return Complex(lhs, rhs );
    }

    // [X1,Y1] * [X2,Y2] = [X1 * X2 - Y1 * Y2, X1 * Y2 + Y1 * X2]
    Complex operator*(const Complex& n)
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
    Complex operator/(const Complex& n)
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
    Complex A(167,53);
    Complex R(0,0);
    Complex Ten(10,10);

    for (auto round = 0; round < 3; round++)
    {
        R = R * R;
        R = R / Ten;
        R = R + A;
    }

    std::cout << R << std::endl;
}