#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Lego {
    string _number;
    string _theme;
    string _name;
    int _minifigs;
    int _pieces;
    double _price;

public:
    Lego(string number = "1234", string theme = "City", string name = "Lego", int minifigs = 0, int pieces = 0,
         double price = 0.0);

    string GetNumber();

    string GetTheme();

    string GetName();

    int GetMinifigs();

    int GetPieces();

    double GetPrice();

    void ReadFile(string &file, vector<Lego> &_legoSets);

    void Display(int index, vector<Lego> &_legoSets);
};

Lego::Lego(string number, string theme, string name, int minifigs, int pieces, double price) {
    _number = number;
    _theme = theme;
    _name = name;
    _minifigs = minifigs;
    _pieces = pieces;
    _price = price;
}

string Lego::GetNumber() {
    return _number;
}

string Lego::GetTheme() {
    return _theme;
}

string Lego::GetName() {
    return _name;
}

int Lego::GetMinifigs() {
    return _minifigs;
}

int Lego::GetPieces() {
    return _pieces;
}

double Lego::GetPrice() {
    return _price;
}

void Lego::ReadFile(string &file, vector<Lego> &_legoSets) {
    ifstream inputFile(file);
    if (!inputFile.is_open())
        cout << " Could not open the file" << endl;
    string lineFromFile;
    getline(inputFile, lineFromFile);
    while (getline(inputFile, lineFromFile)) {
        istringstream stream(lineFromFile);
        string token;
        //// Number,Theme,Name,Minifigs,Pieces,USPrice
        getline(stream, token, ',');
        string number = token;
        getline(stream, token, ',');
        string theme = token;
        getline(stream, token, ',');
        string name = token;
        getline(stream, token, ',');
        int minifigs = stoi(token);
        getline(stream, token, ',');
        int pieces = stoi(token);
        getline(stream, token, '\n');
        double price = stod(token);
        Lego set(number, theme, name, minifigs, pieces, price);
        _legoSets.push_back(set);
    }
}

void Lego::Display(int index, vector<Lego> &_legoSets) {
    cout << "Name: " << _legoSets[index].GetName() << endl;
    cout << "Number: " << _legoSets[index].GetNumber() << endl;
    cout << "Theme: " << _legoSets[index].GetTheme() << endl;
    cout << "Price: $" << _legoSets[index].GetPrice() << endl;
    cout << "Minifigures: " << _legoSets[index].GetMinifigs() << endl;
    cout << "Piece count: " << _legoSets[index].GetPieces() << endl;
}

int main() {
    Lego sets;
    vector<Lego> legoSets;
    string inputFile[3] = {"lego1.csv", "lego2.csv", "lego3.csv"};

    cout << std::fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;

    int option;
    cin >> option;
/*======= Load data from file(s) =======*/
    if (option == 1) {
        sets.ReadFile(inputFile[0], legoSets);
    } else if (option == 2) {
        sets.ReadFile(inputFile[1], legoSets);
    } else if (option == 3) {
        sets.ReadFile(inputFile[2], legoSets);
    } else if (option == 4) {
        for (int i = 0; i < 3; ++i)
            sets.ReadFile(inputFile[i], legoSets);
    }

//    cout << "1. Most Expensive set" << endl;
//    cout << "2. Largest piece count" << endl;
//    cout << "3. Search for set name containing..." << endl;
//    cout << "4. Search themes..." << endl;
//    cout << "5. Part count information" << endl;
//    cout << "6. Price information" << endl;
//    cout << "7. Minifigure information" << endl;
//    cout << "8. If you bought one of everything..." << endl;
//    cout << "0. Exit" << endl;

    int choice;
    cin >> choice;
    cin.get();  // Clear newline character for any later input

    /*======= Print out how many sets were loaded =======*/
    int howManySets = 0;
    for (unsigned long i = 0; i < legoSets.size(); ++i) {
        howManySets++;
    }
    cout << "Total number of sets: " << howManySets << endl;
    /*======= Based on the choice, execute the appropriate task and show the results =======*/
    if (choice == 1) {
        double highestSetValue = legoSets[0].GetPrice();
        int highestSetValueIndex = 0;
        for (unsigned long i = 0; i < legoSets.size(); ++i) {
            if (highestSetValue < legoSets[i].GetPrice()) {
                highestSetValue = legoSets[i].GetPrice();
                highestSetValueIndex = i;
            }
        }
        cout << "The most expensive set is:" << endl;
        sets.Display(highestSetValueIndex, legoSets);
    } else if (choice == 2) {
        int highestSetPieces = legoSets[0].GetPieces();
        int highestSetIndex = 0;
        for (unsigned long i = 0; i < legoSets.size(); ++i) {
            if (highestSetPieces < legoSets[i].GetPieces()) {
                highestSetPieces = legoSets[i].GetPieces();
                highestSetIndex = i;
            }
        }
        cout << "The set with the highest parts count: " << endl;
        sets.Display(highestSetIndex, legoSets);
    } else if (choice == 3) {
        vector<int> matchingSetIndex;
        int legoSetIndex = 0;
        string searchName;
        getline(cin, searchName);
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            if (legoSets[i].GetName().find(searchName) != string::npos) {
                legoSetIndex = i;
                matchingSetIndex.push_back(legoSetIndex);
            }
        }
        if (!matchingSetIndex.empty()) {
            cout << "Sets matching \"" << searchName << "\":" << endl;
            for (unsigned int i = 0; i < matchingSetIndex.size(); ++i) {
                cout << legoSets[matchingSetIndex[i]].GetNumber() << " " <<
                     legoSets[matchingSetIndex[i]].GetName() << " $" <<
                     legoSets[matchingSetIndex[i]].GetPrice() << endl;
            }
        } else {
            cout << "No sets found matching that search term" << endl;
        }
    } else if (choice == 4) {
        vector<int> matchingSetIndex;
        int legoSetIndex = 0;
        string searchCity;
        getline(cin, searchCity);
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            if (legoSets[i].GetTheme().find(searchCity) != string::npos) {
                legoSetIndex = i;
                matchingSetIndex.push_back(legoSetIndex);
            }
        }
        if (!matchingSetIndex.empty()) {
            cout << "Sets matching \"" << searchCity << "\":" << endl;
            for (unsigned int i = 0; i < matchingSetIndex.size(); ++i) {
                cout << legoSets[matchingSetIndex[i]].GetNumber() << " " <<
                     legoSets[matchingSetIndex[i]].GetName() << " $" <<
                     legoSets[matchingSetIndex[i]].GetPrice() << endl;
            }
        } else {
            cout << "No sets found matching that search term" << endl;
        }
    } else if (choice == 5) {
        int totalLoadedSets = 0;
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            totalLoadedSets += legoSets[i].GetPieces();
        }
        cout << "Average part count for " << legoSets.size() << " sets: " <<
             totalLoadedSets / legoSets.size() << endl;
    } else if (choice == 6) {
        double allSetsValue = 0;
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            allSetsValue += legoSets[i].GetPrice();
        }
        cout << "Average price for " << legoSets.size() << " sets: $" <<
             allSetsValue / legoSets.size() << endl;

        double leastValueSet = legoSets[0].GetPrice();
        int leastExpensiveSetIndex = 0;
        for (unsigned int i = 0; i < legoSets.size(); i++) {
            if (leastValueSet > legoSets[i].GetPrice()) {
                leastValueSet = legoSets[i].GetPrice();
                leastExpensiveSetIndex = i;
            }
        }
        cout << "Least expensive set:" << endl;
        sets.Display(leastExpensiveSetIndex,legoSets);

        double highestValueSet = legoSets[0].GetPrice();
        int mostExpensiveSetIndex = 0;
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            if (highestValueSet < legoSets[i].GetPrice()) {
                highestValueSet = legoSets[i].GetPrice();
                mostExpensiveSetIndex = i;
            }
        }
        cout << "Most expensive set:" << endl;
       sets.Display(mostExpensiveSetIndex,legoSets);
    } else if (choice == 7) {
        int allMinifigs = 0;
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            allMinifigs += legoSets[i].GetMinifigs();
        }
        cout << "Average number of minifigures: " <<
             allMinifigs / legoSets.size() << endl;

        int legoIndex = 0;
        int mostMinifigs = legoSets[0].GetMinifigs();
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            if (mostMinifigs < legoSets[i].GetMinifigs()) {
                mostMinifigs = legoSets[i].GetMinifigs();
                legoIndex = i;
            }
        }
        cout << "Set with the most minifigures:" << endl;
        sets.Display(legoIndex,legoSets);
    } else if (choice == 8) {
        double allLegoSetsPrice = 0.0;
        int allLegoPieces = 0;
        int allMinifigs = 0;
        for (unsigned int i = 0; i < legoSets.size(); ++i) {
            allLegoSetsPrice += legoSets[i].GetPrice();
            allLegoPieces += legoSets[i].GetPieces();
            allMinifigs += legoSets[i].GetMinifigs();
        }
        cout << "If you bought one of everything..." << endl;
        cout << "It would cost: $" << allLegoSetsPrice << endl;
        cout << "You would have " << allLegoPieces << " pieces in your collection" << endl;
        cout << "You would have an army of " << allMinifigs << " minifigures!" << endl;
    } else if (choice == 0) {
        exit(-1);
    }
    return 0;
}

