#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstring>  

using namespace std;

int decrypt(char x) {
    if (x == 'A') {
        return 0;
    } else if (x == 'B') {
        return 1;
    } else if (x == 'C') {
        return 2;     
    } 
}

int predict(int x, char y) {
    if (y == 'X') {
        return ((x - 1) + 3) % 3;
    } else if (y == 'Z') {
        return ((x + 1) + 3) % 3;
    } else {
        return x;
    }
}

int points(int x, int y) {
    int points = y+1;

    if (x == y) {
        points += 3;
    } else if (((x - y) + 3) % 3 == 2) {
        points += 6;
    }

    return points;
}

int main() {

    string item;
    ifstream myfile("aoc02.txt");

    vector<string> input;    
    int score = 0;

    while ( getline(myfile, item) ) {
        cout << item[0] << " " << item[2] << endl;
        int first = decrypt(item[0]);
        int second = predict(first, item[2]);

        score += points(first, second);
    }

    cout << score << endl;

    // Close the file
    myfile.close();
}