#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

// Converts a range of numbers to a set
set<int> convert_to_set(int x, int y) {
    set<int> sectors;
    while (x <= y) {
        sectors.insert(x);
        x++;
    }
    return sectors;
}

int main() {

    // Initialize variables
    string item;
    stringstream itemstream;
    ifstream myfile("aoc04.txt");
    vector<set<int>> seglist;
    int i = 0;
    int containment_counter = 0;

    // Read the file line by line
    while (getline(myfile, item)) {
        itemstream.str(item);
        itemstream.clear();  // added this line to clear the stringstream

        // Split each line into comma-separated segments
        string segments;
        stringstream segmentstream;
        while (getline(itemstream, segments, ',')) {
            i++;

            segmentstream.str(segments);
            segmentstream.clear();  // added this line to clear the stringstream

            // Split each segment into a range of numbers
            list<int> segment_vec;
            string segment = "";
            while (getline(segmentstream, segment, '-')) {
                segment_vec.push_back(stoi(segment));
            }

            // Convert the range of numbers to a set
            set<int> range = convert_to_set(segment_vec.front(), segment_vec.back());
            segment_vec.clear();

            // Add the set to a list of sets
            seglist.push_back(range);
            set<int> out;

            // When we have read two sets, find their intersection
            if (i == 2) {
                set_intersection(seglist.front().begin(), seglist.front().end(), seglist.back().begin(), seglist.back().end(), inserter(out, out.begin()));

                // If the intersection is not empty, increment the counter
                if (out.empty() == false)
                    containment_counter++;
                    
                // Clear the list of sets and reset the counter
                seglist.clear();
                i = 0;
            }            
        }        
    }

    // Print the final value
    cout << containment_counter << endl;

    // Close the file
    myfile.close();
}
