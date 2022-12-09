#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <algorithm>
#include <map>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

struct Data {
    int x = 0;
    int y = 0;
};

bool operator==(const Data& lhs, const Data& rhs)
{
    if (lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    return false;    
}

void update_position_t(map<int, Data> * field_h, vector<map<int, Data>> * fields_t, char direction, int * number) {
    for (int i = 0; i < 9; i++) {
        map<int, Data> * before;
        map<int, Data> * field_t = &(*fields_t)[i];
        if (i == 0)
            before = field_h;
        else
            before = &(*fields_t)[i-1];    
        struct Data * difference = new struct Data();
        difference->x = before->find(*number)->second.x - field_t->find(*number-1)->second.x;
        difference->y = before->find(*number)->second.y - field_t->find(*number-1)->second.y;

        if (abs(difference->x) < 2 && abs(difference->y) < 2) {
            field_t->insert({*number, field_t->find(*number-1)->second});
        } else {
            struct Data * manipulation = new struct Data();
            manipulation->x = difference->x / -2;
            manipulation->y = difference->y / -2;  
            manipulation->x += before->find(*number)->second.x;
            manipulation->y += before->find(*number)->second.y;      
            field_t->insert({*number, *manipulation});      
        }
    }
    
}

void update_position_h(map<int, Data> * field_h, vector<map<int, Data>> * fields_t, int steps, char direction, int * number) {
    for (int i = 0; i < steps; i++) {
        *number += 1;
        struct Data * manipulation = new struct Data();
        if (direction == 'R')
            manipulation->x = 1;
        else if (direction == 'L')
            manipulation->x = -1;
        else if (direction == 'U')
            manipulation->y = 1;
        else if (direction == 'D')
            manipulation->y = -1;        
        manipulation->x += field_h->find(*number-1)->second.x;  
        manipulation->y += field_h->find(*number-1)->second.y;    
        (*field_h).insert({*number, *manipulation});
        update_position_t(field_h, fields_t, direction, number);
    }
    
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc09.txt");

    map<int, Data> field_h;
    vector<map<int, Data>> fields_t = {};
    int counter = 0;

    struct Data * begin = new struct Data();
    begin->y = 0;
    begin->x = 0;
    field_h.insert({0, *begin});
    for(int i = 0; i < 9; i++) {
        fields_t.push_back({});
        fields_t[i].insert({0, *begin});
    }

    while ( getline(myfile, item) ) {
        update_position_h(&field_h, &fields_t, stoi(split(item, ' ')[1]), split(item, ' ')[0].at(0), &counter);
    }

    set<string> vals;
    
    for(pair<const int, Data> kv : fields_t[8]) {
        stringstream ss;
        ss << kv.second.x << ", " << kv.second.y << endl;
        vals.insert(ss.str());
    } 

    cout << vals.size() << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}