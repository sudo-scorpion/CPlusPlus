#pragma once
#include <string>
using namespace std;

class Vehicle {
private:
    string make, model;
    unsigned int year, mileage;
    float price;

//Prototypes
public:
    Vehicle();
    Vehicle(string make, string model, int year, float price, int mileage);
    void Display() const;
    string GetYearMakeModel() const;
    float  GetPrice() const;
};



