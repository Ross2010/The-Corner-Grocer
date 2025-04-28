//Corner Grocer Program Documentation
//Name: Rostyslav Melnik
//Date: 04/21/2025


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

// Function to read file and count frequencies
map<string, int> getWordFrequencies(const string& filename) {
    map<string, int> frequencies;
    ifstream inputFile(filename);
    string word;

    if (inputFile.is_open()) {
        while (inputFile >> word) {
            // Convert to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Remove punctuation
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

            frequencies[word]++;
        }
        inputFile.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }
    return frequencies;
}

// Function to count frequency with input validation
void lookupFrequency(const map<string, int>& frequencies) {
    cout << "Enter the item: ";
    string searchWord;
    cin >> searchWord;

    if (cin.fail()) {
        cout << "Invalid input." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    searchWord.erase(remove_if(searchWord.begin(), searchWord.end(), ::ispunct), searchWord.end());

    if (frequencies.count(searchWord)) {
        cout << searchWord << " appears " << frequencies.at(searchWord) << " times." << endl;
    } else {
        cout << searchWord << " not found in the list." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume any remaining input
}

// Function to print frequency list
void printFrequencyList(const map<string, int>& frequencies) {
    cout << "\nFrequency of all items purchased:" << endl;
    for (const auto& pair : frequencies) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Function to print histogram
void printHistogram(const map<string, int>& frequencies) {
    cout << "\nItem Frequency Histogram:" << endl;
    for (const auto& pair : frequencies) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    map<string, int> wordFrequencies = getWordFrequencies("CS210_Project_Three_Input_File.txt");
    int choice;

    do {
        cout << "\nCorner Grocer Menu:" << endl;
        cout << "1. Lookup Frequency of an Item" << endl;
        cout << "2. Print Frequency of All Items" << endl;
        cout << "3. Print Item Frequency Histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; //re-display the menu
            continue;
        }

        switch (choice) {
            case 1:
                lookupFrequency(wordFrequencies);
                break;
            case 2:
                printFrequencyList(wordFrequencies);
                break;
            case 3:
                printHistogram(wordFrequencies);
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}