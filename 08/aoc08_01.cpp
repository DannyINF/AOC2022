#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <numeric>
#include "../custom_functions/custom_functions.h"

using namespace std;
using namespace std::chrono;

void print_map(vector<vector<int>> *map) {
    ofstream myfile;
    myfile.open ("output.txt");
    for (vector e : *map) {
        for (int i : e) {
            myfile << i;
        }
        myfile << endl;
    }
    myfile.close();
}

int sum_map(vector<vector<int>> *map) {
    int sum = 0;
    for (vector e : *map) {
        // sum += reduce(e.begin(), e.end());
        for (int i : e) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("message.txt");

    int visible_trees = 0;

    vector<vector<int>> map = {};
    vector<vector<int>> markers = {};

    while ( getline(myfile, item) ) {
        vector<int> vec;
        vector<int> marks;
        for (size_t i = 0; i < item.size(); ++i) {
            vec.push_back(item[i] - '0');
            marks.push_back(0);
        }
        vector<int> row;
        vector<int> marks_row;
        row.assign(vec.begin(), vec.end());
        marks_row.assign(marks.begin(), marks.end());
        map.push_back(row);
        markers.push_back(marks_row);
    }
    vector<int> row_max = {};
    int row_index = 0;
    for (vector<int> e : map) {
        int biggest_so_far = -1;
        int mark = 0;
        for (int i : e) {
            if (i > biggest_so_far) {
                markers[row_index][mark] = 1;
                biggest_so_far = i;
            }
            mark++;
        }
        row_max.push_back(biggest_so_far);
        row_index++;
    }
    

    row_index = 0;
    for (vector<int> e : map) {
        int biggest_so_far = -1;
        int mark = e.size() - 1;
        for (mark; mark >= 0; mark--) {
            int i = e[mark];
            if (i > biggest_so_far) {
                markers[row_index][mark] = 1;
                biggest_so_far = i;
                if (i == row_max[row_index])
                    break;
            }
        }
        row_index++;
    }

    vector<int> column_max;
    int column_index = 0;
    for (column_index; column_index < map[0].size(); column_index++) {
        int biggest_so_far = -1;
        int mark = 0;
        for (mark; mark < map.size(); mark++) {
            int i = map[mark][column_index];
            if (i > biggest_so_far) {
                markers[mark][column_index] = 1;
                biggest_so_far = i;
            }
        }
        column_max.push_back(biggest_so_far);
    }

    column_index = 0;
    for (column_index; column_index < map[0].size(); column_index++) {
        int biggest_so_far = -1;
        int mark = map.size() - 1;
        for (mark; mark >= 0; mark--) {
            int i = map[mark][column_index];
            if (i > biggest_so_far) {
                markers[mark][column_index] = 1;
                biggest_so_far = i;
                if (i == column_max[column_index])
                    break;
            }
        }
    }

    cout << sum_map(&markers) << endl;
    
    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}