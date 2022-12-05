#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <deque>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVecor.h"

using namespace std;

char get_char(string s, int index) {
    index = 1 + (index) * 4;
    return s[index];
}

vector<ExtendedVector<char>> stacks = {};

int main() {

    string item;
    ifstream myfile("aoc05.txt");

    for (int i = 0; i < 9; i++) {
        stacks.push_back({});
    }

    for (int i = 0; i < 8; i++) {
        getline(myfile, item);
        for (int i = 0; i < 9; i++) {
            char x = get_char(item, i);
            cout << x << endl;
            if (x != ' ') {
                stacks[i].push_back(x);
            }
        }
    }

    while (getline(myfile, item)) {
        vector<string> y = split(item, ' ');
        if (y[0] == "move") {
            for (int i = 0; i < stoi(y[1]); i++) {
                stacks[stoi(y[5])-1].push_front(stacks[stoi(y[3])-1].pop_front());
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        cout << stacks[i].front() << "";
    }

    // Close the file
    myfile.close();
}