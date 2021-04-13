#pragma once
#include "vector.hh"

class rectangle
{
private:
    Vector tab[4];

public:
    rectangle operator+(const Vector &v);

    rectangle operator-(const Vector &v);

    const Vector &operator[](int index) const { return tab[index]; }

    Vector &operator[](int index) { return tab[index]; }

    rectangle();
    ~rectangle();
};
rectangle rectangle::operator+(const Vector &v)
{
    rectangle result;
    for (int i = 0; i < 4; i++)
        result[i] = tab[i] + v;
    return result;
}

rectangle rectangle::operator-(const Vector &v)
{
    rectangle result;
    for (int i = 0; i < 4; i++)
        result[i] = tab[i] - v;
    return result;
}
rectangle::rectangle()
{
    double V[] = {30.0, 20.0},h=100,s=200;
    Vector v1(V);
    for (int i = 0; i < 4; i++)
        tab[i] = v1;
    tab[1][0]+=s;

     tab[2][0]+=s;
      tab[2][1]+=h;

       tab[3][1]+=h;

}

rectangle::~rectangle()
{
}
std::ostream &operator<<(std::ostream &out, rectangle const &tmp)
{
    for (int i = 0; i < 4; i++)
        out << tmp[i] << std::endl;

    return out;
}