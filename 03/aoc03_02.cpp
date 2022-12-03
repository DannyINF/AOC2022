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

    int i = 0;
    list<string> lines;

    while ( getline(myfile, item) ) {
        i++;
        lines.push_back(item);
        if (i == 3) {
            set<char> set1 = convert_to_set(lines.front());
            lines.pop_front();
            set<char> set2 = convert_to_set(lines.front());
            lines.pop_front();
            set<char> set3 = convert_to_set(lines.front());
            lines.pop_front();
            
            set<char> intersect1;
            set<char> intersect2;

            set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersect1, intersect1.begin()));
            set_intersection(set3.begin(), set3.end(), intersect1.begin(), intersect1.end(), inserter(intersect2, intersect2.begin()));

            value += convert_to_number(*intersect2.begin());
            i = 0;
        }
        
    }

    cout << value << endl;

    // Close the file
    myfile.close();
}