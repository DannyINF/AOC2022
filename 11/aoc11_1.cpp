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

class Monkey {
    public:
        ExtendedVector<int> items;
        string operation;
        int test;
        int on_true;
        int on_false;
};

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc11.txt");

    ExtendedVector<Monkey> monkeys;

    while ( getline(myfile, item) ) {
        if (split(item, ' ')[0] == "Monkey") {
            Monkey monkey;
            monkeys.push_back(monkey);
        } else if (split(item, ' ').size() > 1) {
            if (split(item, ' ')[0] == "Starting") {
                for (int i = 2; i < split(item, ' ').size(); i++) {
                    monkeys.back().items.push_back(stoi(split(item, ' ')[i]));
                }
            } else if (split(item, ' ')[0] == "Operation:") {
                monkeys.back().operation = (split(item, ' ')[3] + " " + split(item, ' ')[4] + " " + split(item, ' ')[5]);
            } else if (split(item, ' ')[0] == "Test:") {
                monkeys.back().test = stoi(split(item, ' ')[3]);
            } else if (split(item, ' ')[1] == "true:") {
                monkeys.back().on_true = stoi(split(item, ' ')[5]);
            } else if (split(item, ' ')[1] == "false:") {
                monkeys.back().on_false = stoi(split(item, ' ')[5]);
            }
        }
    }

    ExtendedVector<int> inspects;
    for (Monkey monkey : monkeys)
        inspects.push_back(0);

    for (int i = 0; i < 20; i++) {
        int index = 0;
        for (int m = 0; m < monkeys.size(); m++) {
            if (monkeys[m].items.size() > 0) {
                for (int item : monkeys[m].items) {
                    inspects[index]++;
                    vector<string> split_operation = split(monkeys[m].operation, ' ');
                    int new_level;
                    
                    for (int j = 0; j < split_operation.size(); j++) {
                        if (split_operation[j] == "old")
                            split_operation[j] = to_string(monkeys[m].items.front());
                    }

                    if (split_operation[1] == "*") {
                        new_level = stoi(split_operation[0]) * stoi(split_operation[2]);
                    } else {
                        new_level = stoi(split_operation[0]) + stoi(split_operation[2]);
                    }

                    new_level = new_level / 3;

                    monkeys[m].items.pop_front();

                    if (new_level % monkeys[m].test == 0) {
                        monkeys[monkeys[m].on_true].items.push_back(new_level);
                    } else {
                        monkeys[monkeys[m].on_false].items.push_back(new_level);
                    }
                }
                
            }
            index++;
        }
    }

    int biggest = 0;
    int second_biggest = 0;

    for (int i : inspects) {
        if (i > biggest) {
            second_biggest = biggest;
            biggest = i;
        } else if (i > second_biggest) {
            second_biggest = i;
        }
    }

    cout << biggest * second_biggest << endl;
    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}