#include <iostream>
#include <string>
#include "Vehicle.h"
#include "Showroom.h"
using namespace std;

Showroom :: Showroom(string name, unsigned int capacity){
    showroomName = name;
    maxCapacity = capacity;
}

const vector<Vehicle> &Showroom::GetVehicleList() const {
    return vehicleList;
}

void  Showroom :: AddVehicle(const Vehicle& v){

    if (totalVehicles == maxCapacity)
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    else {
        vehicleList.push_back(v);
        totalVehicles++;
    }
}

void Showroom :: ShowInventory() const{
    if (totalVehicles == 0)
        cout << showroomName << " is empty!" << endl;
    else {
        cout << "Vehicles in " << showroomName << endl;
        for (int i = 0; i < vehicleList.size(); ++i) {
            vehicleList.at(i).Display();
        }
    }

}

float Showroom :: GetInventoryValue() const{

        float totalVal = 0;
        int i = 0;
           for (int i = 0; i < vehicleList.size() && !vehicleList.empty(); ++i) {
            totalVal += vehicleList.at(i).GetPrice();
    }
    return totalVal;
    }


