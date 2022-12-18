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

struct Drop {
    int x;
    int y;
    int z;
};

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc18.txt");

    vector<Drop> drops;

    while ( getline(myfile, item) ) {
        struct Drop * drop = new struct Drop();
        vector<string> coords = split(item, ',');
        drop->x = stoi(coords[0]);
        drop->y = stoi(coords[1]);
        drop->z = stoi(coords[2]);
        drops.push_back(*drop);
    }


    int sides = drops.size() * 6;
    for (int i = 0; i < drops.size(); i++) {
        Drop one = drops[i];
        for (int j = i + 1; j < drops.size(); j++) {
            Drop two = drops[j];
            int equals = 0;
            if (one.x == two.x)
                equals++;
            if (one.y == two.y)
                equals++;
            if (one.z == two.z)
                equals++;  
            if (equals == 2) {
                if (one.x + 1 == two.x || one.x - 1 == two.x || one.y + 1 == two.y || one.y - 1 == two.y || one.z + 1 == two.z || one.z - 1 == two.z)
                    sides -= 2;
            }          
        }
    }

    cout << sides << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}