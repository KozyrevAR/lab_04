#include "histogram.h"
void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() == 0)
        return;
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        else if (max < number)
        {
            max = number;
        }

    }
    return;
}
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end()
{
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "' >" << text << "</text>";
}
// функция из д.з.
void
svg_color(vector<size_t>& bins, size_t number_count, size_t bin_count, string& color)
{
    size_t sr_bin = 0;
    sr_bin = number_count / bin_count;
    for (size_t bin : bins)
    {
        if (bin > sr_bin)
            color = "red";
        else if (bin <= sr_bin)
            color = "green";
    }
}
void svg_rect(string& color, double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    stroke = color;
    fill = color;
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}
void
show_histogram_svg(const vector<size_t>& bins, string& color) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));

        svg_rect(color, TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();

}