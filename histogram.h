#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
void find_minmax(const vector<double>& numbers, double& min, double& max);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(string& color, double x, double y, double width, double height, string stroke, string fill);
void show_histogram_svg(const vector<size_t>& bins, string& color);
void svg_color(vector<size_t>& bins, size_t number_count, size_t bin_count, string& color);

