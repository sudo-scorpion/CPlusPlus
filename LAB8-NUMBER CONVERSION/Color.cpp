
#include "Color.h"


Color::Color(string colorName, unsigned char red, unsigned char green , unsigned char blue) {
    _colorName = std::move(colorName);
    _red = red;
    _green = green;
    _blue = blue;
}

unsigned char Color::GetR() const {
    return _red;
}

unsigned char Color::GetG() const {
return _green;
}

unsigned char Color::GetB() const {
return _blue;
}

string Color::GetName() const{
    return _colorName;
}

string Color::GetHexValue() const{

    string redString = HexConversion((int)GetR());
    string greenString = HexConversion((int)GetG());
    string blueString = HexConversion((int)GetB());

    return "0x" + redString + greenString + blueString;
}

void Color::SetName(const char *name) {
_colorName = name;
}

string Color::HexConversion(int value) {

    map <int , string> hexValue;
    hexValue[0] = "0";
    hexValue[1] = "1";
    hexValue[2] = "2";
    hexValue[3] = "3";
    hexValue[4] = "4";
    hexValue[5] = "5";
    hexValue[6] = "6";
    hexValue[7] = "7";
    hexValue[8] = "8";
    hexValue[9] = "9";
    hexValue[10] = "A";
    hexValue[11] = "B";
    hexValue[12] = "C";
    hexValue[13] = "D";
    hexValue[14] = "E";
    hexValue[15] = "F";

    string hexString1 = "0";
    string hexString2 = "0";

    int quotient = value / 16;
    int reminder = value % 16;

    auto iter = hexValue.begin();
    for (; iter != hexValue.end(); iter++) {
        if (iter->first == quotient){

            hexString1 = iter->second;
        }
    }

    iter = hexValue.begin();
    for (; iter != hexValue.end(); iter++) {
        if (iter->first == reminder){
            hexString2 = iter->second;
        }
    }

    return hexString1 + hexString2;
}



