// lab04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "histogram.h"
#include <curl/curl.h>
using namespace std;
struct Input 
{
    vector<double> numbers;
    size_t bin_count;
};

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt) {
    Input data;
    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}
vector<size_t>
make_histogram(Input data) {
    vector<size_t>result(data.bin_count);
    double min, max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
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
int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    string color = " ";
    const auto input = read_input(cin, true); 
    const auto bins = make_histogram(input);
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
