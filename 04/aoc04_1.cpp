#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

// Convert a range of integers from x to y, inclusive, into a set
set<int> convert_to_set(int x, int y) {
    set<int> sectors;
    while (x <= y) {
        sectors.insert(x);
        x++;
    }
    return sectors;
}

int main() {
    // Open the input file
    ifstream myfile("aoc04.txt");

    // Create a string stream to hold each line of the file
    string item;
    stringstream itemstream;

    // Create a vector to hold the sets of integers from each line
    vector<set<int>> seglist;

    // Initialize the counter for containment
    int containment_counter = 0;

    // Read each line of the file
    while (getline(myfile, item)) {
        // Assign the line to the string stream
        itemstream.str(item);
        itemstream.clear(); // Clear the string stream

        // Create a string stream to hold the comma-separated segments
        string segments;
        stringstream segmentstream;

        // Read each comma-separated segment
        while (getline(itemstream, segments, ',')) {
            // Assign the segment to the string stream
            segmentstream.str(segments);
            segmentstream.clear(); // Clear the string stream

            // Create a list to hold the start and end of the segment range
            list<int> segment_vec;

            // Create a string to hold each integer in the segment range
            string segment = "";

            // Read each integer in the segment range
            while (getline(segmentstream, segment, '-')) {
                segment_vec.push_back(stoi(segment));
            }

            // Convert the segment range to a set
            set<int> range = convert_to_set(segment_vec.front(), segment_vec.back());

            // Clear the list of integers
            segment_vec.clear();

            // Add the set to the vector of sets
            seglist.push_back(range);

            // Create an empty set to hold the intersection of the two sets
            set<int> out;

            // If there are two sets in the vector, find the intersection
            if (seglist.size() == 2) {
                set_intersection(seglist.front().begin(), seglist.front().end(), seglist.back().begin(), seglist.back().end(), inserter(out, out.begin()));

                // If the intersection is equal to one of the sets, increment the containment counter
                if (out == seglist.front() || out == seglist.back())
                    containment_counter++;

                // Clear the vector of sets
                seglist.clear();
            }
        }
    }

    // Print the number of lines with containment
    cout << containment_counter << endl;

    // Close the file
    myfile.close();

    return 0;
}
