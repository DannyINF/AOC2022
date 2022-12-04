#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "../custom_functions/custom_functions.h"

using namespace std;

int main() {

    string item;
    ifstream myfile("aocXX.txt");

    vector<int> input;

    while ( getline(myfile, item) ) {
        input.push_back(stoi(item));
    }

    // Close the file
    myfile.close();
}