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
    auto t_start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc14.txt");
    vector<vector<int>> points = {};
    while ( getline(myfile, item) ) {
        if (item.size() > 3) {
            vector<string> values = split(item, " -> ");
            vector<int> line;
            for (string s : values) {
                vector<string> x_y = split(s, ',');
                line.push_back(stoi(x_y[0]));
                line.push_back(stoi(x_y[1]));
            }
            points.push_back(line);
        }
    }

    int x_max = 750;
    int x_min = 0;
    int y_max = 169;    

    vector<vector<char>> map = {};

    for (int i = 0; i <= y_max; i++) {
        vector<char> line;
        for (int j = x_min; j <= x_max; j++) {
            line.push_back('.');
        }
        map.push_back(line);
    }
    for (int i = x_min; i <= x_max; i++) {
        map[y_max][i-x_min] = '#';
    }

    for (vector<int> v : points) {
        for (int i = 0; i < v.size() - 3; i+=2) {
            int a = v[i];
            int b = v[i + 1];
            int c = v[i + 2];
            int d = v[i + 3];
            if (a > c) {
                int z = a;
                a = c;
                c = z;
            }
            if (b > d) {
                int z = b;
                b = d;
                d = z;
            }
            if (a == c) {
                for (int j = b; j <= d; j++) {
                    map[j][a-x_min] = '#';
                }
            } else if (b == d) {
                for (int j = a; j <= c; j++) {
                    map[b][j-x_min] = '#';
                }
            }
        }
        cout << endl;
    }

    cout << map.size() << endl;

    bool abyss = false;
    int count = 0;
    while (!abyss) {
        
        count++;
        vector<int> start = {-1, 500-x_min};
        vector<int> end = {0, 500-x_min};
        while (start != end) {
            start = end;
            if (start[0] == y_max || map[0][500-x_min] == 'o') {
                abyss = true;       
                break;
            } else if (map[start[0] + 1][start[1]] == '.')
                end = {start[0] + 1, start[1]};
            else if (map[start[0] + 1][start[1] - 1] == '.')    
                end = {start[0] + 1, start[1] - 1};
            else if (map[start[0] + 1][start[1] + 1] == '.')    
                end = {start[0] + 1, start[1] + 1}; 
        }
        if (!abyss)
            map[end[0]][end[1]] = 'o';  
        
    }

    for (vector<char> v : map) {
        for (char c : v) {
            cout << c;
        }
        cout << endl;
    }

    cout << count-1 << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - t_start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}