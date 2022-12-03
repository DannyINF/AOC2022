#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <set>


using namespace std;

int convert_to_number(char x) {
    int y = x;
    if (isupper(x)) {
        return y - 38;
    } else {
        return y - 96;
    }
}

set<char> convert_to_set(string s) {
    // Method 2, by iterating over string and inserting each
    // element of string into the set
    set <char> s_set;

    // Ranged-based for loop OR For-each loop
    for (auto i : s)
        s_set.insert(i);

    return s_set;
}



int main() {

    string item;
    ifstream myfile("aoc03.txt");

    int value = 0;

    while ( getline(myfile, item) ) {
        string half = item.substr(0, item.length()/2);
        string otherHalf = item.substr(item.length()/2);

        set<char> set1 = convert_to_set(half);
        set<char> set2 = convert_to_set(otherHalf);
        set<char> intersect;

        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersect, intersect.begin()));

        value += convert_to_number(*intersect.begin());
        
    }

    cout << value << endl;

    // Close the file
    myfile.close();
}