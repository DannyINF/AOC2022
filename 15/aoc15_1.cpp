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

int distance(vector<int> a, vector<int> b) {
    int distance = 0;
    distance += abs(a[0]-b[0]);
    distance += abs(a[1]-b[1]);
    return distance;
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc15.txt");

    int x_max = 6500000;
    int x_min = -2500000;
    int y_max = 3998374;
    int y_min = -692911;

    // int x_max = 25;
    // int x_min = -2;
    // int y_max = 22;
    // int y_min = 0;

    int row_index = 2000000;
    // int row_index = 10;


    vector<char> row = {};

    for (int i = x_min; i < x_max; i++) {
        row.push_back('.');
    }

    while ( getline(myfile, item) ) {
        vector<string> input = split(item, ' ');
        vector<int> coords_s = {stoi(split(split(input[3], ':')[0], '=')[1]), stoi(split(split(input[2], ',')[0], '=')[1])};
        vector<int> coords_b = {stoi(split(input[9], '=')[1]), stoi(split(split(input[8], ',')[0], '=')[1])};
        if (coords_b[0] == row_index)
            row[coords_b[1]] = 'B';
        int dist = distance(coords_b, coords_s);
        int dist_to_row = abs(row_index - coords_s[0]);
        if (dist_to_row <= dist) {
            int i = dist_to_row;
            for (int j = coords_s[1] - (dist - i); j <= coords_s[1]; j++) {
                // cout << string(row.begin(), row.end()) << endl;
                if (j < x_min)
                    continue;
                if (coords_s[0] + i == row_index) {   
                    if (row[j - y_min] == '.')
                        row[j - y_min] = '#';
                }
                if (coords_s[0] - i == row_index) {
                    if (row[j - y_min] == '.')
                        row[j - y_min] = '#';    
                }
            }
            for (int j = coords_s[1] + (dist - i); j >= coords_s[1]; j--) {
                // cout << string(row.begin(), row.end()) << endl;
                if (j > x_max +1 )
                    continue;
                if (coords_s[0] + i == row_index) { 
                    if (row[j - y_min] == '.')
                        row[j - y_min] = '#';
                }
                if (coords_s[0] - i == row_index) {  
                    if (row[j - y_min] == '.')
                        row[j - y_min] = '#';    
                }
            }
        }
        
    }

    // for (vector<char> v : map) {
    //     for (char c : v) {
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    int count = 0;
    for (char c : row) {
        if (c == '#' || c == 'S')
            count++;
    }
    cout << count << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}