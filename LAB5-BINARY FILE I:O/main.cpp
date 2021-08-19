#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Ship {
    struct Armaments {
        string _weaponType;
        int _power = 0;
        float _rating = 0.0;
    };
    string _name;
    string _shipClass;
    short _length;
    int _shield;
    float _speed;
    int _weaponCount;
    vector<Armaments> weaponInventory;

public:
    // prototypes
    explicit Ship(string name = "", string shipClass = "", short length = 0, int shield = 0,
                  float speed = 0, int weapon = 0);

    static void ReadFile(vector<Ship> &_shipList, const string &file);

    static void Display(vector<Ship> &_shipList, int index);

    static void DisplayShips(vector<Ship> &_shipList);

    static void DisplayMostPowerfulWeapon(vector<Ship> &_shipList);

    static void DisplayMostPowerfulShip(vector<Ship> &_shipList);

    static void DisplayWeakestShip(vector<Ship> &_shipList);

    static void DisplayUnarmedShip(vector<Ship> &_shipList);

    static int TotalFirePower(vector<Ship> &_shipList, int index);

};

Ship::Ship(string name, string shipClass, short length, int shield, float speed, int weapon) {
    _name = std::move(name);
    _shipClass = std::move(shipClass);
    _length = length;
    _shield = shield;
    _speed = speed;
    _weaponCount = weapon;
}

int totalShips = 0;

void Ship::ReadFile(vector<Ship> &_shipList, const string &file) {
    ifstream inputFile(file, ios_base::binary);
    if (!inputFile.is_open())
        cout << "Could not open the file " << file << endl;
    else {
        int shipCount;
        inputFile.read((char *) &shipCount, sizeof(shipCount));
        for (int i = 0; i < shipCount; ++i) {
            Ship ship;
            int nameLength;
            inputFile.read((char *) &nameLength, sizeof(nameLength));
            char *tempName = new char[nameLength];
            inputFile.read(tempName, nameLength);
            string shipName = tempName;
            delete[] tempName;
            ship._name = shipName;

            int classLength;
            inputFile.read((char *) &classLength, sizeof(classLength));
            char *tempClass = new char[classLength];
            inputFile.read(tempClass, classLength);
            string className = tempClass;
            delete[] tempClass;
            ship._shipClass = className;

            short length;
            inputFile.read((char *) &length, sizeof(length));
            ship._length = length;


            int shield;
            inputFile.read((char *) &shield, sizeof(shield));
            ship._shield = shield;

            float speed;
            inputFile.read((char *) &speed, sizeof(speed));
            ship._speed = speed;

            int totalWeapon;
            inputFile.read((char *) &totalWeapon, sizeof(totalWeapon));
            ship._weaponCount = totalWeapon;

            if (totalWeapon > 0) {
                Ship::Armaments weaponSystem;
                for (int j = 0; j < totalWeapon; ++j) {
                    int weaponTypeLength;
                    inputFile.read((char *) &weaponTypeLength, sizeof(weaponTypeLength));
                    char *tempWeaponType = new char[weaponTypeLength];
                    inputFile.read(tempWeaponType, weaponTypeLength);
                    string weaponTypeName = tempWeaponType;
                    delete[] tempWeaponType;
                    weaponSystem._weaponType = weaponTypeName;

                    int power;
                    inputFile.read((char *) &power, sizeof(power));
                    weaponSystem._power = power;

                    float rating;
                    inputFile.read((char *) &rating, sizeof(rating));
                    weaponSystem._rating = rating;
                    ship.weaponInventory.push_back(weaponSystem);
                }
            }
            _shipList.push_back(ship);
            totalShips++;
        }
    }
}

int Ship::TotalFirePower(vector<Ship> &_shipList, int index) {
    int total = 0;
    for (int k = 0; k < _shipList[index]._weaponCount; ++k) {
        total += _shipList[index].weaponInventory[k]._power;
    }
    return total;
}

void Ship::Display(vector<Ship> &_shipList, int index) {
    cout << "Name: " << _shipList[index]._name << endl;
    cout << "Class: " << _shipList[index]._shipClass << endl;
    cout << "Length: " << _shipList[index]._length << endl;
    cout << "Shield capacity: " << _shipList[index]._shield << endl;
    cout << "Maximum Warp: " << _shipList[index]._speed << endl;
    cout << "Armaments: " << endl;

    if (_shipList[index]._weaponCount <= 0)
        cout << "Unarmed\n" << endl;
    else {
        for (int i = 0; i < _shipList[index]._weaponCount; ++i) {
            cout << _shipList[index].weaponInventory[i]._weaponType << ", " <<
                 _shipList[index].weaponInventory[i]._power << ", " <<
                 _shipList[index].weaponInventory[i]._rating << endl;
        }
        cout << "Total firepower: " << TotalFirePower(_shipList, index) << '\n' << endl;
    }
}


void Ship::DisplayShips(vector<Ship> &_shipList) {
    for (int i = 0; i < totalShips; ++i) {
        Display(_shipList, i);
    }
}

void Ship::DisplayMostPowerfulWeapon(vector<Ship> &_shipList) {
    int index;
    int maxPower = _shipList[0].weaponInventory[0]._power;
    for (int i = 0; i < totalShips; ++i) {
        for (int j = 1; j < _shipList[i]._weaponCount; ++j) {
            int tempMaxPower = _shipList[i].weaponInventory[j]._power;
            if (maxPower < tempMaxPower) {
                maxPower = tempMaxPower;
                index = i;
            }
        }
    }
    Display(_shipList, index);
}

void Ship::DisplayMostPowerfulShip(vector<Ship> &_shipList) {
    int index = 0;
    int maxCombinedPower = TotalFirePower(_shipList, 0);
    for (int i = 1; i < totalShips; ++i) {
        int tempMaxCombinedPower = TotalFirePower(_shipList, i);
        if (maxCombinedPower < tempMaxCombinedPower) {
            maxCombinedPower = tempMaxCombinedPower;
            index = i;
        }
    }
    Display(_shipList, index);
}

void Ship::DisplayWeakestShip(vector<Ship> &_shipList) {
    int index = 0;
    int minCombinedPower = TotalFirePower(_shipList, 0);
    for (int i = 1; i < totalShips; ++i) {
        int tempMinCombinedPower = TotalFirePower(_shipList, i);
        if (tempMinCombinedPower != 0) {
            if (minCombinedPower > tempMinCombinedPower) {
                minCombinedPower = tempMinCombinedPower;
                index = i;
            }
        }
    }
    Display(_shipList, index);
}

void Ship::DisplayUnarmedShip(vector<Ship> &_shipList) {
    for (int i = 0; i < totalShips; ++i) {
        if (_shipList[i]._weaponCount == 0) {
            Display(_shipList, i);
        }
    }
}


int main() {
    int option;
    Ship ship;
    vector<Ship> shipList;

    cout << "Which inputFile(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;

    cin >> option;
    /* Load files here */

    switch (option) {
        case 1:
            ship.ReadFile(shipList, "friendlyships.shp");
            break;
        case 2:
            ship.ReadFile(shipList, "enemyships.shp");
            break;
        case 3:
            ship.ReadFile(shipList, "friendlyships.shp");
            ship.ReadFile(shipList, "enemyships.shp");
            break;
        default:
            cout << "Invalid input!" << endl;
            exit(-1);
    }

    cout << "1. Print all ship" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ship" << endl;

    cin >> option;
/* Work your magic here */

    switch (option) {
        case 1:
            ship.DisplayShips(shipList);
            break;
        case 2:
            ship.DisplayMostPowerfulWeapon(shipList);
            break;
        case 3:
            ship.DisplayMostPowerfulShip(shipList);
            break;
        case 4:
            ship.DisplayWeakestShip(shipList);
            break;
        case 5:
            ship.DisplayUnarmedShip(shipList);
            break;
        default:
            cout << "Invalid input!" << endl;
            exit(-1);
    }
    return 0;
}

