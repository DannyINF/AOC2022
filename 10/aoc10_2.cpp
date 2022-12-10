#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc10.txt");

    ExtendedVector<int> values_x;
    values_x.push_back(1);

    while ( getline(myfile, item) ) {
        vector<string> command = split(item, ' ');
        if (command[0] == "addx") {
            values_x.push_back(values_x.back());
            values_x.push_back(values_x.back() + stoi(command[1]));
        } else {
            values_x.push_back(values_x.back());
        }
    }

    ofstream output("output.txt");
    for (int i : values_x) {
        output << i << endl;
    }
    output.close();

    int index = 0;
    for (int input : values_x) {
        index = index % 40;
        if (index == 0)
            cout << endl;
        if (index == input || index == input - 1 || index == input + 1) {
            cout << "#";
        } else {
            cout << " ";
        }
        index++;
    }

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}