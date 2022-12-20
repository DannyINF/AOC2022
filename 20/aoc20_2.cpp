#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <algorithm>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

long long int key = 811589153;

struct number {
    int index;
    long long int value;
};

bool operator==(const number& lhs, const number& rhs) {
    if (lhs.index == rhs.index && lhs.value == rhs.value)
        return true;
    return false;    
}

bool operator==(const number& lhs, const long long int& rhs) {
    if (lhs.value == rhs)
        return true;
    return false;   
     
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void moveElement(std::list<number> &list, number x) {
    // Find the position of the element x in the list
    int size = list.size() - 1;
    auto it = std::find(list.begin(), list.end(), x);
    if (it != list.end()) {
        // Store the position of the element x in the list
        long long int pos = std::distance(list.begin(), it);
        // Erase the element from the list
        list.erase(it);
        // Calculate the new position for the element x, wrapping around if necessary
        long long int newPos = ((pos + x.value) % size + size) % size;
        // Insert the element x at the new position
        list.insert(std::next(list.begin(), newPos), x);
    }
}

void shift_list_left(std::list<number>& l) {
  // Find the index of the first element with value 0
  auto it = std::find(l.begin(), l.end(), 0);
  // Rotate the vector so that the element with value 0 is at the front
  std::rotate(l.begin(), it, l.end());
}


long long int getSum(const std::list<number> &list) {
    // Find the position of the element with value 0
    auto it = std::find(list.begin(), list.end(), 0);
    // Move the iterator to the 1000th element after the element with value 0
    std::advance(it, (distance(list.begin(), it) + 1000) % list.size() - (distance(list.begin(), it)));
    // Get the value at the 1000th element
    long long int x = (*it).value;
    cout << x << endl;
    // Move the iterator to the 2000th element after the element with value 0
    std::advance(it, (distance(list.begin(), it) + 1000) % list.size() - (distance(list.begin(), it)));
    // Get the value at the 2000th element
    long long int y = (*it).value;
    cout << y << endl;
    // Move the iterator to the 3000th element after the element with value 0
    std::advance(it, (distance(list.begin(), it) + 1000) % list.size() - (distance(list.begin(), it)));
    // Get the value at the 3000th element
    long long int z = (*it).value;
    cout << z << endl;
    // Return the sum of the three elements
    return x + y + z;
}


int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc20.txt");

    list<number> input;
    int index = 0;
    while ( getline(myfile, item) ) {
        struct number * n = new struct number;
        n->index = index;
        n->value = stoi(item) * key;
        input.push_back(*n);
        index++;
    }

    list<number> working_list = input;
    vector<number> elements_to_move(input.begin(), input.end());

    for (int i = 0; i < 10; i++) {
        for (number x : elements_to_move) {
            moveElement(working_list, x);
        }
    }

    shift_list_left(working_list);
    cout << getSum(working_list) << endl; 

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}
