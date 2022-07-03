#include "C:\Users\PC\Desktop\labs\lab04\histogram.h"

#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}
void test_ravnie()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1, 1, 1 }, min, max);
    assert(min == 1);
    assert(max == 1);
}
void test_only1()
{
    double min = 0;
    double max = 0;
    find_minmax({ 1 }, min, max);
    assert(min == 1);
    assert(max == 1);
}
void test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
// тесты из д.з.
void check_color1()
{
    vector <size_t> a = { 3, 2, 5 };
    string color = " ";
    svg_color(a, 10, 3, color);
    assert(color == "red");
}
void check_color2()
{
    vector <size_t> a = { 1, 3, 2, 1, 2, 1 };
    string color = " ";
    svg_color(a, 10, 3, color);
    assert(color == "green");
}
int main()
{
    test_positive();
    test_negative();
    test_ravnie();
    test_only1();
    test_empty();
    check_color1();
    check_color2();
}