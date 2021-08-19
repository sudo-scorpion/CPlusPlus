#pragma once
#include <string>
#include <vector>
#include "Showroom.h"
using namespace std;

class Dealership {
private:
    string dealershipName;
    unsigned int maxCapacity, totalShowrooms;
    vector<Showroom> showroomList;

     // Prototypes
public:
    Dealership(string name = "Generic Dealership", unsigned int capacity = 0);
    void AddShowroom(const Showroom& s);
    float GetAveragePrice() const;
    void ShowInventory() const;
};


