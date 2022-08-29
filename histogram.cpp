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
svg_color(size_t bin, size_t number_count, size_t bin_count, string& color)
{
    size_t sr_bin = 0;
    sr_bin = number_count / bin_count;
    if (bin > sr_bin)
        color = "red";
    else
        color = "green";
}
void svg_rect(string& color, double x, double y, double width, double height, string stroke = "black", string obv = "black")
{
    stroke = color;
    obv = color;
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << obv << "'/>" << endl;
}
string
make_info_text(double TEXT_LEFT, double IMAGE_HEIGHT, double TEXT_BASELINE)
{
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto info = GetVersion();
    //printf("Version (10) = %10x\n", info);
    //printf("Version (16) = %16x\n", info);
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    //printf("Version = %lu\n", version);
    DWORD platform = info >> 16;
    //printf("Platform = %lu\n", platform);
    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    //printf("Version_major = %lu\n", version_major);
    DWORD version_minor = version >> 8;
    //printf("Version_minor = %lu\n", version_minor);
    DWORD build;
    if ((info & 0x80000000) == 0)
    {
        build = platform;
        //printf("Build = %lu\n", build);

    }
    buffer << "Windows " << "v" << version_major << "." << version_minor << " (build " << build << ")";
    TCHAR  infoBuf[MAX_COMPUTERNAME_LENGTH+1];
    DWORD bufCharCount = MAX_COMPUTERNAME_LENGTH+1;
    GetComputerNameA( LPSTR (infoBuf), &bufCharCount );
    buffer << "<tspan x='" << TEXT_LEFT << "' y='" << IMAGE_HEIGHT - TEXT_BASELINE <<" '> "<< "Computer name: " << infoBuf << "</tspan>";
    return buffer.str();
}

void
show_histogram_svg(const vector<size_t>& bins, size_t numcount, size_t bincount, string& color) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_color(bin, numcount, bincount, color);
        svg_rect(color, TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    //svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE + 30, to_string(bins[0]));

    svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE - 30, make_info_text(TEXT_LEFT, IMAGE_HEIGHT, TEXT_BASELINE));

    svg_end();

}
