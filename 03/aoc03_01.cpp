#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Converts a character to a number
int convert_to_number(char x) {
    int y = x;
    if (isupper(x)) {
        return y - 38;
    } else {
        return y - 96;
    }
}

// Converts a string to a set of characters
set<char> convert_to_set(string s) {
    set <char> s_set;

    // Insert each character from the string into the set
    for (auto i : s) {
        s_set.insert(i);
    }

    return s_set;
}

int main() {
    // Initialize variables
    string item;
    ifstream myfile("aoc03.txt");
    int value = 0;

    // Read the file line by line
    while (getline(myfile, item)) {
        // Split the line into two halves
        string half = item.substr(0, item.length()/2);
        string otherHalf = item.substr(item.length()/2);

        // Convert each half of the line to a set of characters
        set<char> set1 = convert_to_set(half);
        set<char> set2 = convert_to_set(otherHalf);

        // Find the intersection of the two sets
        set<char> intersect;
        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersect, intersect.begin()));

        // Add the number value of the first character in the intersection to the final value
        value += convert_to_number(*intersect.begin());
    }

    // Output the final value
    cout << value << endl;

    // Close the file
    myfile.close();
}
