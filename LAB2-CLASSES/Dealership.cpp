#include "Dealership.h"
#include <iostream>
#include <string>
using namespace std;

Dealership :: Dealership(string name, unsigned int capacity){
        dealershipName = name;
        maxCapacity = capacity;
}

void Dealership :: AddShowroom(const Showroom& s){
    if (totalShowrooms == maxCapacity)
        cout << "Dealership is full, can't add another showroom!" << endl;
    else{
        showroomList.push_back(s);
        totalShowrooms++;
    }
}

float Dealership :: GetAveragePrice() const{
    unsigned totalVehicle = 0;
    float avgPrice = 0, totalValue = 0;
    for (int i = 0; i < showroomList.size(); ++i) {
        totalVehicle += showroomList.at(i).GetVehicleList().size();
        totalValue += showroomList.at(i).GetInventoryValue();
    }
    avgPrice= totalValue/totalVehicle;
         return avgPrice;
}

void Dealership :: ShowInventory() const{
    if (totalShowrooms == 0) {
        cout << dealershipName << " is empty!" << endl;
        cout << "Average car price: $0.00";
    }
    else {
        for (int i = 0; i < showroomList.size(); ++i) {
            showroomList.at(i).ShowInventory();
            cout << endl;
        }
        cout << "Average car price: $" << GetAveragePrice();
    }
}
