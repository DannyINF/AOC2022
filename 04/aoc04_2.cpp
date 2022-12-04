#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>


using namespace std;

set<int> convert_to_set(int x, int y) {
    set<int> sectors;
    while (x <= y) {
        sectors.insert(x);
        x++;
    }
    return sectors;
}

int main() {

    string item;
    stringstream itemstream;
    ifstream myfile("aoc04.txt");

    
    vector<set<int>> seglist;
    int i = 0;
    int containment_counter = 0;

    while ( getline(myfile, item) ) {
        itemstream.str(item);
        itemstream.clear();  // added this line to clear the stringstream
        
        string segments;
        stringstream segmentstream;
        while (getline(itemstream, segments, ',')) {
            i++;
            cout << "segments: " << segments << endl;
            segmentstream.str(segments);
            segmentstream.clear();  // added this line to clear the stringstream
            cout << "segmentstream: " << segmentstream.str() << endl;
            list<int> segment_vec;
            cout << 2 << endl;
            string segment = "";
            while (getline(segmentstream, segment, '-')) {
                cout << "seg: " << segment << endl;
                segment_vec.push_back(stoi(segment));
            }
            set<int> range = convert_to_set(segment_vec.front(), segment_vec.back());
            segment_vec.clear();
            for (int const& z : range)
            {
                std::cout << z << ' ';
            }
            cout << endl;
            seglist.push_back(range);
            set<int> out;
            cout << 3 << endl;
            if (i == 2) {
                set_intersection(seglist.front().begin(), seglist.front().end(), seglist.back().begin(), seglist.back().end(), inserter(out, out.begin()));
                if (out.empty() == false)
                    containment_counter++;
                seglist.clear();
                i = 0;
            }            
        }        
    }

    cout << containment_counter << endl;

    // Close the file
    myfile.close();
}
