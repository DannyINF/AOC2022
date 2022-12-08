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

void print_map(ExtendedVector<ExtendedVector<int>> map) {
    for (ExtendedVector e : map) {
        for (int i : e) {
            cout << i;
        }
        cout << endl;
    }
}

int sum_map(ExtendedVector<ExtendedVector<int>> map) {
    int sum = 0;
    for (ExtendedVector e : map) {
        for (int i : e) {
            sum += i;
        }
    }
    return sum;
}

int max_map(ExtendedVector<ExtendedVector<int>> map) {
    int max = 0;
    for (ExtendedVector e : map) {
        for (int i : e) {
            max = __max(max, i);
        }
    }
    return max;
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc08.txt");

    int visible_trees = 0;

    ExtendedVector<ExtendedVector<int>> map = {};
    ExtendedVector<ExtendedVector<int>> markers = {};

    while ( getline(myfile, item) ) {
        vector<int> vec;
        vector<int> marks;
        for (size_t i = 0; i < item.size(); ++i) {
            vec.push_back(item[i] - '0');
            marks.push_back(0);
        }
        ExtendedVector<int> row;
        ExtendedVector<int> marks_row;
        row.assign(vec.begin(), vec.end());
        marks_row.assign(marks.begin(), marks.end());
        map.push_back(row);
        markers.push_back(marks_row);
    }
    int row_index = 0;
    for (ExtendedVector<int> e : map) {
        int biggest_so_far = -1;
        int mark = 0;
        for (int i : e) {
            if (i > biggest_so_far) {
                markers[row_index][mark] = 1;
                biggest_so_far = i;
            }
            mark++;
        }
        row_index++;
    }

    for (int index = 0; index < map.size(); index++) {
        for (int mark = 0; mark < map[index].size(); mark++) {
            int scenic_score = 1;
            int counter;
            int height = map[index][mark];
            if (index == 0 || mark == 0 || index == map.size() - 1 || mark == map[index].size() - 1) {
                scenic_score = 0;
                markers[index][mark] = scenic_score;
                continue;
            }
            // left
            counter = 1;
            for (int i = mark - 1; i >= 1; i--) {
                if (map[index][i] >= height) {
                    break;
                }
                counter++;
            }
            scenic_score *= counter;
            // right
            counter = 1;
            for (int i = mark + 1; i < map[index].size() - 1; i++) {
                if (map[index][i] >= height) {
                    break;
                }
                counter++;
            }
            scenic_score *= counter;
            // bottom
            counter = 1;
            for (int i = index + 1; i < map.size() - 1; i++) {
                if (map[i][mark] >= height) {
                    break;
                }
                counter++;
            }
            scenic_score *= counter;
            // top
            counter = 1;
            for (int i = index - 1; i >= 1; i--) {
                if (map[i][mark] >= height) {
                    break;
                }
                counter++;
            }
            scenic_score *= counter;
            markers[index][mark] = scenic_score;
        }
    }    

    cout << max_map(markers) << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}