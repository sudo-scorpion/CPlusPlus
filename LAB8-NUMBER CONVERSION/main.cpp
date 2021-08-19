#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
#include "Color.h"
#include <bitset>

using namespace std;

void ReadFile(const char* filename,  map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);

int main()
{
    cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
    cout << "7. Load all 6 files" << endl;
    int choice;
    cin >> choice;

    map<string, Color> colors;
    if (choice >= 1 && choice <= 6)
    {
        string file = "colors" + to_string(choice) + ".txt";
        ReadFile(file.c_str(), colors);
    }
    else if (choice == 7)
    {
        for (int i = 1; i <= 6; i++)
        {
            string file = "colors" + to_string(i) + ".txt";
            ReadFile(file.c_str(), colors);
        }

    }

    // Secondary menu
    cout << "1. Show all colors" << endl;
    cout << "2. Search for a color" << endl;
    cin >> choice;

    if (choice == 1)
        PrintColors(colors);
    else if (choice == 2)
        SearchForColor(colors);
    return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors) {
    // TODO: Read the file, create and store some Color objects
    ifstream inputFile(filename);
    if (!inputFile.is_open())
        cout << " Could not open the file " << filename << endl;
    else {
        string lineFromFile;
        while (getline(inputFile, lineFromFile)) {
            istringstream stream(lineFromFile);
            string token;
            getline(stream, token, ' ');
            string colorName = token;
            getline(stream, token, ' ');
            int colorValue = stoi(token);

            bitset<32> red(colorValue);
            bitset<32> green(colorValue);
            bitset<32> blue(colorValue);
            red = (red >>= 16) & (bitset<32>) 255;
            int redValue = (int) red.to_ulong();
            green = (green >>= 8) & (bitset<32>) 255;
            int greenValue = (int) green.to_ulong();
            blue = (blue >>= 0) & (bitset<32>) 255;
            int blueValue = (int) blue.to_ulong();

            Color color(colorName, redValue, greenValue, blueValue);
            colors[colorName] = color;
        }
    }
}

void PrintColors(const map<string, Color>& colors) {
    int counter = 0;
    auto iter = colors.begin();
    for (; iter != colors.end(); iter++) {
        cout << left << setw(20) << iter->first;
        cout << right << setw(10) << iter->second.GetHexValue();
        cout << "\t\t" << (int)iter->second.GetR() << "," << (int)iter->second.GetG() << "," << (int)iter->second.GetB() << endl;
        counter++;
    }
    cout << "Number of colors: " << counter << endl;
}
void PrintColor(const Color& color)
{
    cout << left << setw(20) << color.GetName();
    cout << right << setw(10) << color.GetHexValue();
    cout << "\t\t" << (int)color.GetR() << "," << (int)color.GetG() << "," << (int)color.GetB() << endl;
}
void SearchForColor(map<string, Color>& colors)
{
    // TODO: Get some input, check if that key exists, then print out the color (or an error message)
    string color;
    cin >> color;
    if (colors.find(color)!= colors.end()) {
        PrintColor(colors.find(color)->second);
    }
    else
        cout << color << " not found!" << endl;
}
