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
    int i = 0;
    list<string> lines;

    // Read the file line by line
    while (getline(myfile, item)) {
        i++;
        lines.push_back(item);

        // When we have read three lines, process them to find the final value
        if (i == 3) {
            // Convert each line to a set of characters
            set<char> set1 = convert_to_set(lines.front());
            lines.pop_front();
            set<char> set2 = convert_to_set(lines.front());
            lines.pop_front();
            set<char> set3 = convert_to_set(lines.front());
            lines.pop_front();

            // Find the intersections of the sets
            set<char> intersect1;
            set<char> intersect2;
            set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersect1, intersect1.begin()));
            set_intersection(set3.begin(), set3.end(), intersect1.begin(), intersect1.end(), inserter(intersect2, intersect2.begin()));

            // Add the number value of the first character in the intersection to the final value
            value += convert_to_number(*intersect2.begin());
            i = 0;
        }
    }

    // Print the final value
    cout << value << endl;

    // Close the file
    myfile.close();
}
