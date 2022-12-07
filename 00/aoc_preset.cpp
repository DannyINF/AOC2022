#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include "../custom_functions/custom_functions.h"

using namespace std;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aocXX.txt");

    while ( getline(myfile, item) ) {
        
    }

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}