#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include<map>
#include <vector>

using namespace std;

class State {
    string _state, _perCapital, _population, _medianIncome, _numOfHousehold;
public:
    explicit State(string state = "", string perCapital = "", string population = "",
                   string medianIncome = "", string numOfHouseholds = "");

    const string &getState() const;

    string getPerCapital() const;

    string getPopulation() const;

    string getMedianIncome() const;

    string getNumOfHousehold() const;

    static void ReadFile(const string &filename);

    static void Display(int option, const string &state, const map<string, State> &stateMaps);
};

map<string, State> stateContainer;

State::State(string state, string perCapital, string population, string medianIncome,
             string numOfHouseholds) {
    _state = std::move(state);
    _perCapital = std::move(perCapital);
    _population = std::move(population);
    _medianIncome = std::move(medianIncome);
    _numOfHousehold = std::move(numOfHouseholds);
}

const string &State::getState() const {
    return _state;
}

string State::getPerCapital() const {
    return _perCapital;
}

string State::getPopulation() const {
    return _population;
}

string State::getMedianIncome() const {
    return _medianIncome;
}

string State::getNumOfHousehold() const {
    return _numOfHousehold;
}

void State::ReadFile(const string &fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
        cout << " Could not open the file " << fileName << endl;
    else {
        string lineFromFile;
        getline(inputFile, lineFromFile);
        while (getline(inputFile, lineFromFile)) {
            istringstream stream(lineFromFile);
            string token;
            getline(stream, token, ',');
            string stateName = token;
            getline(stream, token, ',');
            string perCapital = token;
            getline(stream, token, ',');
            string population = token;
            getline(stream, token, ',');
            string medianIncome = token;
            getline(stream, token, ',');
            string numOfHouseHolds = token;
            State state(stateName, perCapital, population, medianIncome, numOfHouseHolds);
            stateContainer[stateName] = state;
        }
    }
}

void State::Display(int option, const string &state, const map<string, State> &stateMaps) {
    // display all states
    if (option == 1) {
        auto iter = stateMaps.begin();
        for (; iter != stateMaps.end(); iter++) {
            cout << iter->second.getState() << endl;
            cout << "Population: " << iter->second.getPopulation() << endl;
            cout << "Per Capita Income: " << iter->second.getPerCapital() << endl;
            cout << "Median Household Income: " << iter->second.getMedianIncome() << endl;
            cout << "Number of Households: " << iter->second.getNumOfHousehold() << endl;
            cout << endl;
        }
    }
    // display targeted state
    if (option == 2) {
        auto iter = stateMaps.begin();
        for (; iter != stateMaps.end(); iter++) {
            if (iter->first == state) {
                cout << iter->second.getState() << endl;
                cout << "Population: " << iter->second.getPopulation() << endl;
                cout << "Per Capita Income: " << iter->second.getPerCapital() << endl;
                cout << "Median Household Income: " << iter->second.getMedianIncome() << endl;
                cout << "Number of Households: " << iter->second.getNumOfHousehold() << endl;
                return;
            }
        }
        cout << "No match found for " << state << endl;
        return;
    }
}

// random number generator
mt19937 random_mt(time(nullptr));

int Random(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

// dice roller
void RollDice(int numberOfRolls, int numberOfSides) {
    map<int, int> diceRoll;

    //////  Approach 1

    for (int i = 1; i < numberOfSides + 1; ++i) {
        diceRoll[i] = 0;
    }

    for (int i = 0; i < numberOfRolls; ++i) {
        int rand = Random(1, numberOfSides);
        auto iter = diceRoll.begin();
        for (; iter != diceRoll.end(); iter++) {
            if (iter->first == rand) {
                iter->second++;
            }
        }
    }

    auto iter1 = diceRoll.begin();
    for (; iter1 != diceRoll.end(); iter1++) {
        cout << iter1->first << ": " << iter1->second << endl;
    }

///// Approach 2

//    int count = 0;
//
//    for (int i = 1; i < numberOfRolls + 1; ++i) {
//        int roll = Random(1, numberOfSides);
//        diceRoll[i] = roll;
//    }
//    for (int i = 1; i < numberOfSides + 1; ++i) {
//        auto iter = diceRoll.begin();
//        for (; iter != diceRoll.end(); iter++) {
//            if (iter->second == i) {
//                count++;
//            }
//        }
//        cout << i << ": " << count << endl;
//        count = 0;
//    }
}

int main() {
    State state;
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;

    if (option == 1) {
        int randomSeed;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);

        cout << "Number of times to roll the die: ";
        int times;
        cin >> times;

        cout << "Number of sides on this die: ";
        int sides;
        cin >> sides;

        RollDice(times, sides);

        // option 2
    } else if (option == 2) {
        // Load the states
        state.ReadFile("states.csv");
        // Get input for option 1 (show all states) or 2 (do a search for a particular state)
        cout << "1. Print all states" << endl;
        cout << "2. Search for a state" << endl;
        cin >> option;
        string targetState;
        if (option == 2) {
            cin >> targetState;
        }
        state.Display(option, targetState, stateContainer);
    }

    return 0;
}

