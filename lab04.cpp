
#include "histogram.h"


using namespace std;
struct Input
{
    vector<double> numbers;
    size_t bin_count;
};
struct progress
{
    char* privat;
    size_t size;
};

static size_t progress_callback(void* clientp,
    double dltotal,
    double dlnow,
    double ultotal,
    double ulnow)
{
    struct progress* memory = (struct progress*)clientp;
    cerr << " Progress : " << round(dlnow / dltotal * 100) << " %" << "\r";
    return 0;
}
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
make_histogram(const Input& input)
{
    vector <size_t> bins(input.bin_count, 0);
    double min;
    double max;
    find_minmax(input.numbers, min, max);
    double bin_size = (max - min) / input.bin_count;
    for (size_t i = 0; i < input.numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < (input.bin_count - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((low <= input.numbers[i]) && (input.numbers[i] < high))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[input.bin_count - 1]++;
        }

    }
    return bins;
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
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}
Input
download(const string& address)
{
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        struct progress data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &data);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            exit(1);
        }
        curl_easy_cleanup(curl);
    }
    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    Input input;
    curl_global_init(CURL_GLOBAL_ALL);
    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }
    string color = " ";
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.numbers.size(), input.bin_count, color);
}
