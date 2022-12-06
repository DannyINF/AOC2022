#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVecor.h"

using namespace std;

// This function should return true if the character c is present in the vector v
// and false otherwise.
bool is_char_in_vector(ExtendedVector<char> v, char c) {
    for (char ch : v) {
        if (ch == c)
            return true;
    }
    return false;
}

// This function should return the ExtendedVector v with all characters until the
// first occurrence of the character c removed.
ExtendedVector<char> remove_until_char(ExtendedVector<char> v, char c) {
    cout << "pop: ";
    while (!v.empty() && v.front() != c) {
        cout << v.pop_front();
    }
    cout << v.pop_front();
    cout << endl;
    return v;
}

int main() {
    string item;
    ifstream myfile("aoc06.txt");

    // Check if the file was successfully opened
    if (!myfile) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    vector<int> input;

    // Read lines from the file and process them
    while (getline(myfile, item)) {
        int i = 0;
        int number_different = 0;
        ExtendedVector<char> chars = {};

        // Iterate over each character in the line
        for (char c : item) {
            i++;

            // Check if the current character is in the vector
            cout << "is char in v: " << is_char_in_vector(chars, c) << endl;
            if (!is_char_in_vector(chars, c)) {
                chars.push_back(c);
                number_different++;
            } else {
                chars.push_back(c);
                chars = remove_until_char(chars, c);
                number_different = chars.size();
            }

            // Output the current vector
            for (char ch : chars) {
                cout << ch;
            }
            cout << endl;

            // If the number of different characters is 14, output the current index and break out of the loop
            if (number_different == 14) {
                cout << i << endl;
                break;
            }
        }
    }

    // Close the file
    myfile.close();

    return 0;
}
