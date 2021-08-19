#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// vector list for author's name
vector<string> author;
// vector list for number of novel
vector<int> novel;
// comma position
int commaPos = 0;
// number of comma in user input string
int commaCount = 0;

int main() {
    // Tittle
    string tittle;
    cout << "Enter a title for the data:" << endl;
    getline(cin, tittle);
    cout << "You entered: " << tittle << endl;

    // Col 1 header
    string col1;
    cout << "Enter the column 1 header:" << endl;
    getline(cin, col1);
    cout << "You entered: " << col1 << endl;

    // Col 2 header
    string col2;
    cout << "Enter the column 2 header:" << endl;
    getline(cin, col2);
    cout << "You entered: " << col2 << endl;

    while(true){
        // user data
        string input;
        string tempAuthor;
        string tempNovel;
        cout << "Enter a data point (-1 to stop input):" << endl;
        getline(cin, input);

        // close the program when user enter -1
        if (input == "-1")
            break;

        // comma position
          for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',') {
            commaPos = i;
            commaCount++;
        }
    }
        if (commaCount == 1) {
            // storing user's entered data
            tempAuthor = input.substr(0, commaPos);
            tempNovel = input.substr(commaPos + 1, input.length() - 1);
        }

        // Handling errors
        if (commaCount < 1) {
            cout << ("Error: No comma in string.") << endl;
            continue;
        }
        if (commaCount > 1){
            cout << ("Error: Too many commas in input.") << endl;
            commaCount = 0;
            continue;
        }

        // string to integer conversion
        int novelCount = 0;
        try {
            commaCount =0;
            novelCount = stoi(tempNovel);
        } catch (invalid_argument &e) {
            cout << "Error: Comma not followed by an integer." << endl;
            continue;
        }

        cout << "Data string: " << tempAuthor << endl;
        if (novelCount > 0)
            cout << "Data integer: " << novelCount << endl;
        else
            cout << "Data integer: " << tempNovel << endl;

        // storing valid data point
        author.push_back(tempAuthor);
        novel.push_back(novelCount);

    }

    cout << endl;
    cout << setw(33) << right << tittle << endl;
    cout << setw(20)  << left << col1 << "|";
    cout << setw(23)  << right << col2 << endl;
    cout << setfill('-') << setw(44) << "" << endl;
    cout << setfill(' ');

    // displaying author and novels list
    for (int i = 0; i < author.size() && !novel.empty(); i++) {
        cout << setw(20) << left << author[i] << "|";
        cout << setw(23) << right << novel[i] << endl;
    }
    cout << endl;

    // displaying histogram
    for (int i = 0; i < author.size() && !novel.empty(); i++) {
        cout << setw(20) << right << author[i] << " ";
        for (int j = 0; j < novel[i]; ++j) {
            cout << left << "*";
        }
        cout << endl;
    }
    return 0;
}







