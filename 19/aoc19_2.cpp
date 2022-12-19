#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <regex>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;
using namespace std::chrono;

struct robot {
    int clay_cost = 0;
    int obsidian_cost = 0;
    int ore_cost = 0;
};

int max_clay_cost = 0;
int max_obsidian_cost = 0;
int max_ore_cost = 0;

int max_geode = 0;

long long int calls = 0;

bool forecast(int time_remaining, int geodes, int geode_robots) {
    for (int i = 0; i < time_remaining; i++) {
        geodes += geode_robots + i;
    }
    if (geodes > max_geode)
        return false;
    return true;    
}

int max_geodes(robot ore, int ore_robots, robot clay, int clay_robots, robot obsidian, int obsidian_robots, robot geode, int geode_robots, int ores, int clays, int obsidians, int geodes, int time_remaining) {
    calls++;
    if (calls % 100000000 == 0)
        cout << max_geode << " " << calls << endl;
    if (time_remaining == 0) {
        return geodes;
    }
    if (forecast(time_remaining, geodes, geode_robots)) {
        return geodes;
    }

    max_geode = max(max_geode, geodes);

    int build_ore = 0;
    int build_clay = 0;
    int build_obsidian = 0;
    int build_geode = 0;
    
    if (geode.ore_cost <= ores && geode.obsidian_cost <= obsidians)
        build_geode = max_geodes(ore, ore_robots, clay, clay_robots, obsidian, obsidian_robots, geode, geode_robots + 1, ores + ore_robots - geode.ore_cost, clays + clay_robots, obsidians + obsidian_robots - geode.obsidian_cost, geodes + geode_robots, time_remaining - 1); 
    if (ore.ore_cost <= ores && ore_robots < max_ore_cost)
        build_ore = max_geodes(ore, ore_robots + 1, clay, clay_robots, obsidian, obsidian_robots, geode, geode_robots, ores + ore_robots - ore.ore_cost, clays + clay_robots, obsidians + obsidian_robots, geodes + geode_robots, time_remaining - 1);
    if (clay.ore_cost <= ores && clay_robots < max_clay_cost)
        build_clay = max_geodes(ore, ore_robots, clay, clay_robots + 1, obsidian, obsidian_robots, geode, geode_robots, ores + ore_robots - clay.ore_cost, clays + clay_robots, obsidians + obsidian_robots, geodes + geode_robots, time_remaining - 1);
    if (obsidian.ore_cost <= ores && obsidian.clay_cost <= clays && obsidian_robots < max_obsidian_cost)
        build_obsidian = max_geodes(ore, ore_robots, clay, clay_robots, obsidian, obsidian_robots + 1, geode, geode_robots, ores + ore_robots - obsidian.ore_cost, clays + clay_robots - obsidian.clay_cost, obsidians + obsidian_robots, geodes + geode_robots, time_remaining - 1);  

    int no_build = max_geodes(ore, ore_robots, clay, clay_robots, obsidian, obsidian_robots, geode, geode_robots, ores + ore_robots, clays + clay_robots, obsidians + obsidian_robots, geodes + geode_robots, time_remaining - 1);   

    int result = 0;
    for (int i : {no_build, build_ore, build_clay, build_obsidian, build_geode})
        result = max(result, i);    
    return result;    
}

int main() {
    auto start = high_resolution_clock::now();

    string item;
    ifstream myfile("aoc19.txt");

    regex pattern("Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.");
    smatch match;

    vector<vector<robot>> blueprints;

    int count = 0;

    while ( getline(myfile, item)  && count < 3) {
        count++;
        if (regex_search(item, match, pattern)) {
            struct robot * ore = new struct robot;
            struct robot * clay = new struct robot;
            struct robot * obsidian = new struct robot;
            struct robot * geode = new struct robot;

            ore->ore_cost = stoi(match[2]);
            clay->ore_cost = stoi(match[3]);
            obsidian->ore_cost = stoi(match[4]);
            obsidian->clay_cost = stoi(match[5]);
            geode->ore_cost = stoi(match[6]);
            geode->obsidian_cost = stoi(match[7]);

            blueprints.push_back({*ore, *clay, *obsidian, *geode});
        }
    }

    for (vector<robot> blueprint : blueprints) {
        cout << blueprint[0].ore_cost << " " << blueprint[1].ore_cost << " " << blueprint[2].ore_cost << " " << blueprint[2].clay_cost << " " << blueprint[3].ore_cost << " " << blueprint[3].obsidian_cost << endl;
    }

    int result = 1;
    for (int i = 0; i < blueprints.size(); i++) {
        max_geode = 0;
        max_clay_cost = 0;
        max_obsidian_cost = 0;
        max_ore_cost = 0;
        for (robot r : {blueprints[i][0], blueprints[i][1], blueprints[i][2], blueprints[i][3]}) {
            max_clay_cost = max(max_clay_cost, r.clay_cost);
            max_obsidian_cost = max(max_obsidian_cost, r.obsidian_cost);
            max_ore_cost = max(max_ore_cost, r.ore_cost);
        }
        cout << result << endl;
        result *= max_geodes(blueprints[i][0], 1, blueprints[i][1], 0, blueprints[i][2], 0, blueprints[i][3], 0, 0, 0, 0, 0, 32);
    }

    cout << result << endl;

    // Close the file
    myfile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count()/1000000.0 << " seconds" << endl;
}