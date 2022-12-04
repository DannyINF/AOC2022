#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstring>  

using namespace std;

// Decrypts a single character using the provided cipher
int decrypt(char x) {
    if (x == 'A' || x == 'X') {
        return 0;
    } else if (x == 'B' || x == 'Y') {
        return 1;
    } else if (x == 'C' || x == 'Z') {
        return 2;     
    } 
}

// Calculates the points for a given pair of decrypted characters
int points(int x, int y) {
    int points = y + 1;

    if (x == y) {
        points += 3;
    } else if (((x - y) + 3) % 3 == 2) {
        points += 6;
    }

    return points;
}

int main() {
    // Initialize variables
    string item;
    ifstream myfile("aoc02.txt");
    vector<string> input;    
    int score = 0;

    // Read the file line by line
    while (getline(myfile, item)) {
        // Decrypt the characters at indices 0 and 2 on each line
        int first = decrypt(item[0]);
        int second = decrypt(item[2]);

        // Calculate the points for the decrypted characters and add them to the score
        score += points(first, second);
    }

    // Output the final score
    cout << score << endl;

    // Close the file
    myfile.close();
}
