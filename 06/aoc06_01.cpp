#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;

// This function should return the ExtendedVector v with all characters until the
// first occurrence of the character c removed.
ExtendedVector<char> remove_until_char(ExtendedVector<char> v, char c) {
    while (!v.empty() && v.front() != c) {
        v.pop_front();
    }
    v.pop_front();
    return v;
}

int main() {
    string item;
    ifstream myfile("aoc06.txt");

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
            if (!chars.contains(c)) {
                chars.push_back(c);
                number_different++;
            } else {
                chars.push_back(c);
                chars = remove_until_char(chars, c);
                number_different = chars.size();
            }

            // If the number of different characters is 4, output the current index and break out of the loop
            if (number_different == 4) {
                cout << i << endl;
                break;
            }
        }
    }

    // Close the file
    myfile.close();

    return 0;
}
