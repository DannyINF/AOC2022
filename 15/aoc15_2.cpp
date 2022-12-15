#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include <mutex>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

mutex output_mutex;
atomic_bool output_found(false);

int distance(const vector<int>& a, const vector<int>& b) {
    int distance = 0;
    distance += abs(a[0]-b[0]);
    distance += abs(a[1]-b[1]);
    return distance;
}

int calculate_output_for_range(int x_min, int x_max, int y_min, int y_max, const vector<vector<int>>& s, const vector<int>& d, int& max_output) {
    int output = 1;
    for (int x = x_min; x <= x_max; x++) {
        if (output_found.load()) {
            return 0;
        }
        cerr << x << endl;
        for (int y = y_min; y <= y_max; y++) {
            bool valid = true;
            for (std::size_t i = 0; i < s.size(); i++) {
                if (distance(s[i], {y, x}) <= d[i]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                output = 4000000 * x + y;
                output_found.store(true);
                break;
            }
        }
        if (output_found.load()) {
            break;
        }
    }
    std::lock_guard<std::mutex> lock(output_mutex);
    max_output = max(max_output, output);
    return output;
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc15.txt");

    int x_max = 4000000;
    int x_min = 0;
    int y_max = 4000000;
    int y_min = 0;

    vector<vector<int>> s = {};
    vector<vector<int>> b = {};
    vector<int> d = {};

    int max_output = 0;

    while ( getline(myfile, item) ) {
        vector<string> input = split(item, ' ');
        vector<int> coords_s = {stoi(split(split(input[3], ':')[0], '=')[1]), stoi(split(split(input[2], ',')[0], '=')[1])};
        s.push_back(coords_s);
        vector<int> coords_b = {stoi(split(input[9], '=')[1]), stoi(split(split(input[8], ',')[0], '=')[1])};
        b.push_back(coords_b);
        d.push_back(distance(coords_s, coords_b));
    }

    vector<thread> threads;
    int num_threads = 24;
    int x_range = x_max - x_min + 1;
    int x_range_per_thread = x_range / num_threads;
    for (int i = 0; i < num_threads; i++) {
        if (output_found.load()) {
            break;
        }
        int x_min_thread = x_min + i * x_range_per_thread;
        int x_max_thread = x_min_thread + x_range_per_thread - 1;
        threads.push_back(thread(calculate_output_for_range, x_min_thread, x_max_thread, y_min, y_max, s, d, ref(max_output)));
    }

    for (auto& t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Output: " << max_output << endl;
    cout << "Duration: " << duration.count() << " microseconds" << endl;
    return 0;
}
