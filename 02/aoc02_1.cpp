#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstring>  

using namespace std;

int decrypt(char x) {
    if (x == 'A' || x == 'X') {
        return 0;
    } else if (x == 'B' || x == 'Y') {
        return 1;
    } else if (x == 'C' || x == 'Z') {
        return 2;     
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
        int second = decrypt(item[2]);

        score += points(first, second);

    }

    cout << score << endl;

    // Close the file
    myfile.close();
}