// lab04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <math.h>
#include <conio.h>
#include <vector>
#include <string>
#include "histogram.h"
using namespace std;
vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

void make_histogram(size_t& bin_count, size_t& number_count, const vector<double>& numbers, vector <size_t>& bins, double& min, double& max)
{
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((low <= numbers[i]) && (numbers[i] < high))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }

    }
}
void show_histogram_text(vector<size_t>& bins, size_t& bin_count, size_t& number_count)
{
    size_t max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;
    // средняя высота столбца (к заданию вар. 7)
    size_t sr_bin = 0;
    sr_bin = number_count / bin_count;
    // вывод
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bin > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }
        if (bin < 100)
            cout << " ";
        if (bin < 10)
            cout << " ";
        cout << bin << "|";
        // если высота меньше средней или равна (к заданию вар. 7)
        if (bin <= sr_bin)
        {
            for (size_t i = 0; i < height; i++)
                cout << "*";
            int kmin = round(sr_bin - bin);
            for (size_t i = 0; i < kmin; i++)
                cout << "-";
        }
        // если высота выше средней (к заданию вар. 7)
        else if (bin > sr_bin)
        {
            for (size_t i = 0; i < sr_bin; i++)
                cout << "*";
            int kmax = round(bin - sr_bin);
            for (size_t i = 0; i < kmax; i++)
                cout << "+";
        }
        cout << endl;
    }
}
int main()
{
    // ввод
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: " << endl;
    const auto numbers = input_numbers(cin, number_count);
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    // расчет гистограммы
    vector <size_t> bins(bin_count, 0);
    double min;
    double max;
    string color = " ";
    find_minmax(numbers, min, max);
    make_histogram(bin_count, number_count, numbers, bins, min, max);
    svg_color(bins, number_count, bin_count, color);
    show_histogram_svg(bins, color);
    
    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
