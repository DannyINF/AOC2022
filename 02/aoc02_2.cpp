#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstring>  

using namespace std;

// Decrypts a single character using the provided cipher
int decrypt(char x) {
    if (x == 'A') {
        return 0;
    } else if (x == 'B') {
        return 1;
    } else if (x == 'C') {
        return 2;     
    } 
}

// Predicts the value of the second character based on the value of the first character
int predict(int x, char y) {
    if (y == 'X') {
        return ((x - 1) + 3) % 3;
    } else if (y == 'Z') {
        return ((x + 1) + 3) % 3;
    } else {
        return x;
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
        // Decrypt the character at index 0 and predict the value of the character at index 2
        int first = decrypt(item[0]);
        int second = predict(first, item[2]);

        // Calculate the points for the decrypted characters and add them to the score
        score += points(first, second);
    }

    // Output the final score
    cout << score << endl;

    // Close the file
    myfile.close();
}
