#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

// Converts a string to a set of characters
set<char> convert_to_set_char(string s) {
    set <char> s_set;

    // Iterate over the string and insert each character into the set
    for (auto i : s)
        s_set.insert(i);

    return s_set;
}

// Splits a string into a vector of substrings using a given separator
vector<string> split(string s, char sep) {
    vector<string> output = {};
    int pos1 = s.find_first_of(sep);
    if (pos1 == -1)
        output.push_back(s);
    else {
        string sub1 = s.substr(0, pos1);
        string sub2 = s.substr(pos1+1, s.length()-1);
        if (sub1.length() > 0)
            output.push_back(sub1);
        if (sub2.length() > 0) {
            vector<string> remainder = split(sub2, sep);
            output.insert(output.end(), remainder.begin(), remainder.end());
        }     
    }

    return output;
}