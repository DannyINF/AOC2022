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

bool operator==(const Drop& lhs, const Drop& rhs) {
    if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
        return true;
    return false;    
}

int x_min = 10;
int y_min = 10;
int z_min = 10;
int x_max = 0;
int y_max = 0;
int z_max = 0;

ExtendedVector<Drop> visited = {};

int neighbors(Drop drop, ExtendedVector<Drop> drops) {
    cout << drop.x << "," << drop.y << "," << drop.z << endl;
    if (visited.contains(drop))
        return 0;
    if (drop.x > x_max || drop.x < x_min || drop.y > y_max || drop.y < y_min || drop.z > z_max || drop.z < z_min)
        return -1;
    for (Drop d : drops) {
        if (drop == d)
            return 0;
    }

    int top;
    int bottom;
    int left;
    int right;
    int front;
    int back;

    visited.push_back(drop);

    if (drops.contains({drop.x, drop.y, drop.z+1})) {
        visited.push_back({drop.x, drop.y, drop.z+1});
        top = 1;
    } else
        top = neighbors({drop.x, drop.y, drop.z+1}, drops);

    if (drops.contains({drop.x, drop.y, drop.z-1})) {
        visited.push_back({drop.x, drop.y, drop.z-1});
        bottom = 1;
    } else
        bottom = neighbors({drop.x, drop.y, drop.z-1}, drops);

    if (drops.contains({drop.x, drop.y+1, drop.z})) {
        visited.push_back({drop.x, drop.y+1, drop.z});
        left = 1;
    } else
        left = neighbors({drop.x, drop.y+1, drop.z}, drops);

    if (drops.contains({drop.x, drop.y-1, drop.z})) {
        visited.push_back({drop.x, drop.y-1, drop.z});
        right = 1;
    } else
        right = neighbors({drop.x, drop.y-1, drop.z}, drops);

    if (drops.contains({drop.x+1, drop.y, drop.z})) {
        visited.push_back({drop.x+1, drop.y, drop.z});
        front = 1;
    } else
        front = neighbors({drop.x+1, drop.y, drop.z}, drops);

    if (drops.contains({drop.x-1, drop.y, drop.z})) {
        visited.push_back({drop.x-1, drop.y, drop.z});
        back = 1;
    } else
        back = neighbors({drop.x-1, drop.y, drop.z}, drops);


   
    for (int i : {top, bottom, left, right, front, back})
        if (i == -1)
            return 0;
    return top + bottom + left + right + front + back;
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc18.txt");

    ExtendedVector<Drop> drops;

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

    for (Drop d : drops) {
        x_min = min(x_min, d.x);
        y_min = min(y_min, d.y);
        z_min = min(z_min, d.z);
        x_max = max(x_max, d.x);
        y_max = max(y_max, d.y);
        z_max = max(z_max, d.z);
    }

    cout << x_min << endl;
    cout << y_min << endl;
    cout << z_min << endl;
    cout << x_max << endl;
    cout << y_max << endl;
    cout << z_max << endl;

    for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
            for (int z = z_min; z <= z_max; z++) {
                sides -= neighbors({x, y, z}, drops);
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