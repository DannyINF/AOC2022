#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

// Reads a text file and stores the values in a list
void readFile(string filename, list<int>& values) {
    // Initialize variables
    string item;
    int value = 0;

    // Create and open a text file
    ifstream MyFile(filename);

    // Read the file line by line
    while (getline(MyFile, item)) {
        // If the line is empty, store the accumulated value in the list
        if (item == "") {
            values.push_back(value);
            value = 0;
        }
        // Otherwise, add the line to the accumulated value
        else {
            value += stoi(item);
        }
    }

    // Store the final accumulated value in the list
    values.push_back(value);

    // Close the file
    MyFile.close();
}

// Adds the first three values in a list together
int addFirstThree(list<int>& values) {
    // Sort the list in descending order
    values.sort();
    values.reverse();

    // Get the first three values from the list and add them together
    int value = values.front();
    values.pop_front();
    value += values.front();
    values.pop_front();
    value += values.front();

    return value;
}

int main() {
    // Initialize a list to store the values from the text file
    list<int> values;

    // Read the text file and store the values in the list
    readFile("aoc1.txt", values);

    // Add the first three values in the list together
    int result = addFirstThree(values);

    // Output the result
    cout << result << endl;
}
