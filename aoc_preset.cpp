#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

int main() {

    string item;
    ifstream myfile("aocXX.txt");

    while ( getline(myfile, item) ) {
        
    }

    // Close the file
    myfile.close();
}