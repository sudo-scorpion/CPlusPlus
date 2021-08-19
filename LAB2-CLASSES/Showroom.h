#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
using namespace std;

class Showroom {
private:
    string showroomName = "";
    unsigned int maxCapacity = 0, totalVehicles = 0;
    vector <Vehicle> vehicleList;
// Prototypes
public:
    Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);
    const vector <Vehicle> & GetVehicleList() const;
    void  AddVehicle(const Vehicle& v);
    void ShowInventory() const;
    float GetInventoryValue() const;
};



