#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

int main() {
    string item;
    list<int> elves;
    // Create and open a text file
    ifstream MyFile("aoc1.txt");
    int value = 0;
    while ( getline(MyFile, item) ) {
        if (item == "") {
            elves.push_back(value);
            value = 0;
        } else {
            value += stoi(item);
        }
    }
    elves.push_back(value);

    elves.sort();
    elves.reverse();
    value = elves.front();
    elves.pop_front();
    value += elves.front();
    elves.pop_front();
    value += elves.front();
    cout << value << endl;

    // Close the file
    MyFile.close();
}