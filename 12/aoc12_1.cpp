#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <tuple>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

int convert_to_number(char x) {
    if (x == 'S')
        x = 'a';
    else if (x == 'E')
        x = 'z';    
    return x - 96;
}

vector<int> getIndex(vector<vector<char>> v, char k)
{
    for (int i = 0; i < v.size(); i++) {
        auto it = find(v[i].begin(), v[i].end(), k);
        if (it != v[i].end()) 
        {
            int index = it - v[i].begin();
            return {index, i};
        }
    }
    return {-1, -1};
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc12.txt");

    vector<vector<char>> map = {};

    while ( getline(myfile, item) ) {
        vector<char> v(item.begin(), item.end());
        map.push_back(v);
    }

    vector<vector<tuple<bool, double>>> visited;
    for (auto a : map) {
        vector<tuple<bool, double>> v;
        for (auto b : a) {
            if (b == 'S')
                v.push_back({true, 0});
            else    
                v.push_back({false, 1000000});
        }
        visited.push_back(v);
    }

    ExtendedVector<vector<int>> waiting_list;

    vector<int> position = getIndex(map, 'S');
    while (map[position.back()][position.front()] != 'E') {
        tuple<bool, double> current = visited[position.back()][position.front()];
        visited[position.back()][position.front()] = {true, get<1>(current)};
        if (position.back() > 0) {
            tuple<bool, double> left = visited[position.back()-1][position.front()];
            if (convert_to_number(map[position.back()-1][position.front()]) - convert_to_number(map[position.back()][position.front()]) < 2 && (!get<0>(left) ||  get<1>(left) > get<1>(current) + 1)) {
                visited[position.back()-1][position.front()] = {get<0>(left), get<1>(current) + 1};
                if (!waiting_list.contains({position.front(), position.back()-1}))
                    waiting_list.push_back({position.front(), position.back()-1});
            }
        }
        if (position.back() < map.size() - 1) {
            tuple<bool, double> right = visited[position.back()+1][position.front()];
            if (convert_to_number(map[position.back()+1][position.front()]) - convert_to_number(map[position.back()][position.front()]) < 2 && (!get<0>(right) || get<1>(right) > get<1>(current) + 1)) {
                visited[position.back()+1][position.front()] = {get<0>(right), get<1>(current) + 1};
                if (!waiting_list.contains({position.front(), position.back()+1}))
                    waiting_list.push_back({position.front(), position.back()+1});
            }
        }
        if (position.front() > 0) {
            tuple<bool, double> top = visited[position.back()][position.front()-1];
            if (convert_to_number(map[position.back()][position.front()-1]) - convert_to_number(map[position.back()][position.front()]) < 2 && (!get<0>(top) || get<1>(top) > get<1>(current) + 1)) {
                visited[position.back()][position.front()-1] = {get<0>(top), get<1>(current) + 1};
                if (!waiting_list.contains({position.front()-1, position.back()}))
                    waiting_list.push_back({position.front()-1, position.back()});
            }
        }
        if (position.front() < map[0].size() - 1) {
            tuple<bool, double> bottom = visited[position.back()][position.front()+1];
            if (convert_to_number(map[position.back()][position.front()+1]) - convert_to_number(map[position.back()][position.front()]) < 2 && (!get<0>(bottom) || get<1>(bottom) > get<1>(current) + 1)) {
                visited[position.back()][position.front()+1] = {get<0>(bottom), get<1>(current) + 1};
                if (!waiting_list.contains({position.front()+1, position.back()}))
                    waiting_list.push_back({position.front()+1, position.back()});
            }
        }
        position = waiting_list.pop_front();
    }

    vector<int> positionE = getIndex(map, 'E');

    cout << get<1>(visited[positionE.back()][positionE.front()]) << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}