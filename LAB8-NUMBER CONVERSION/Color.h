#pragma once
#include <string>
#include <map>
using namespace std;

class Color {
    unsigned char _red;
     unsigned char _green;
    unsigned char _blue;
    string _colorName;
public:
    explicit Color(string colorName = "color", unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);

    unsigned char GetR() const;

    unsigned char GetG() const;

    unsigned char GetB() const;

     string GetHexValue() const;

     string GetName() const;

     void SetValue(int value);

     void SetName(const char *name);

     static string HexConversion(int value);

};





