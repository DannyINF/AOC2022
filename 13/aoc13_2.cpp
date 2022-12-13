#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <list>
#include <chrono>
#include <string>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

int compare(char a, char b) {
    int a_int = 10;
    int b_int = 10;
    if (isdigit(a))
        a_int = a - '0';
    if (isdigit(b))
        b_int = b - '0';    
    if (a_int > b_int)
        return 1;
    else if (a_int < b_int) 
        return -1;
    else
        return 0;          
}

bool is_ext_digit(char c) {
    if (isdigit(c) || c == '#') {
        return true;
    }
    return false;
}

bool compare(string a, string b) {
    bool result = true;
    if (a == b)
        return true;
    int c = 0;
    int d = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i == b.size())
            return false;
        char char_a = a[i+c];
        char char_b = b[i+d];
        if (char_a == char_b)
            continue;
        if (is_ext_digit(char_a) && is_ext_digit(char_b)) {
            c = 0;
            d = 0;
            if (compare(char_a, char_b) < 0)
                return true;
            else if (compare(char_a, char_b) > 0)
                return false;
        } else if (is_ext_digit(char_b) && char_a == '[') {
            d--;
            continue;
        } else if (is_ext_digit(char_b) && char_a == ']') {
            c = 0;
            d = 0;
            return true;
        } else if (is_ext_digit(char_a) && char_b == '[') {
            i--;
            d++;
            continue;
        } else if (is_ext_digit(char_a) && char_b == ']') {
            c = 0;
            d = 0;
            return false;
        } else if (char_a == '[' && char_b == ']'){
            c = 0;
            d = 0;
            return false;
        } else if (char_a == ']' && char_b == '[') {
            c = 0;
            d = 0;
            return true;
        } else {
            c = 0;
            d = 0;
            return false;
        }
    }
    return result;
}

// Function to replace a string with another string
void replaceString(std::string& subject, const std::string& search, const std::string& replace)
{
    // Get the length of the search string
    size_t pos = 0;
    size_t searchLen = search.length();
    size_t replaceLen = replace.length();

    // Keep replacing until we can't find any more occurrences of the search string
    while ((pos = subject.find(search, pos)) != std::string::npos)
    {
        // Replace the search string with the replacement string
        subject.replace(pos, searchLen, replace);

        // Move to the end of the replacement string
        pos += replaceLen;
    }
}

int sum_vector(vector<bool> v) {
    int count = 0;
    for (bool b : v)
        if (b)
            count++;
    return count;
}

int main() {
    auto start = high_resolution_clock::now();

    string left;
    string right;
    ifstream myfile("aoc13.txt");

    vector<string> input;

    input.push_back("[[2]]");
    input.push_back("[[6]]");

    while ( getline(myfile, left) ) {
        replaceString(left, ",", "][");
        replaceString(left, "10", "#");
        replaceString(left, "[[", "[");
        replaceString(left, "]]", "]");
        input.push_back(left);
        
        getline(myfile, right);
        replaceString(right, ",", "][");
        replaceString(right, "10", "#");
        replaceString(right, "[[", "[");
        replaceString(right, "]]", "]");
        input.push_back(right);

        getline(myfile, left);

        // bool result = compare(left, right);

        // indizes.push_back(result);
        
        // cout << left << endl;
        // cout << right << endl;
        // cout << result << endl;


    }

    
    vector<bool> indizes;
    indizes.push_back(0);
    while (sum_vector(indizes) < indizes.size()) {
        indizes = {};
        int i = 0;
        while (i < input.size() - 1) {
            bool b = false;
            b = compare(input[i], input[i++]);
            if (!b) {
                iter_swap(input.begin() + i-1, input.begin() + i);
            }
            indizes.push_back(b);
 
        }

    }

    
        

    int count = 0;
    int a = 0;
    int b = 0;
    reverse(input.begin(), input.end());
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "[[2]]")
            a = i+1;
        else if (input[i] == "[[6]]")
            b = i+1;    
    }

    cout << (a * b) << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}