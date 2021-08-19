#include <iostream>
#include <string>
#include "Vehicle.h"
using namespace std;

Vehicle :: Vehicle(){
    make = "COP3503";
    model = "Rust Bucket";
    year = 1900;
    price = 0;
    mileage = 0;
}

Vehicle :: Vehicle(string make, string model, int year, float price, int mileage){
    this->make = make;
    this->model = model;
    this->year = year;
    this->price = price;
    this->mileage = mileage;
}

void Vehicle :: Display() const{
    cout << year << " " <<  make << " " << model << " " << "$" << price << " " << mileage << endl;
}

string Vehicle :: GetYearMakeModel() const {
    return to_string(year) + " " + make + " "+ model;
}

float Vehicle :: GetPrice() const{
    return price;
}
