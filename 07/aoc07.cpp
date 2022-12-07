#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "../custom_functions/custom_functions.h"
#include "../custom_functions/ExtendedVector.h"

using namespace std;

struct file {
    string name;
    int size;
};

struct dir {
    dir * parent;
    ExtendedVector<dir*> dirs = {};
    ExtendedVector<file*> files = {};
    string name;
    int size = 0;
};

int get_filesize(ExtendedVector<file*> files) {
    int size = 0;
    for (file * f : files) {
        size += f -> size;
    }
    return size;
}

int get_dirsize(ExtendedVector<dir*> dirs) {
    int size = 0;
    for (dir * d : dirs) {
        int dirsize = 0;
        dirsize += get_dirsize(d -> dirs);
        dirsize += get_filesize(d -> files);
        d -> size = dirsize;
        size += dirsize;
    }
    return size;
}

void print_files(ExtendedVector<file*> files, int intendation) {
    for (file * f : files) {
        for (int i = 0; i < intendation; i++)
            cout << ' ';
        cout << f -> name << " " << f -> size << endl;
    }
}

void print_structure(ExtendedVector<dir*> dirs, int intendation) {
    for (dir * d : dirs) {
        for (int i = 0; i < intendation; i++)
            cout << ' ';
        cout << d -> name << " " << d -> size << endl;
        print_structure(d -> dirs, intendation + 4);
        print_files(d -> files, intendation + 4);
    }
}

int print_small_dirs(ExtendedVector<dir*> dirs) {
    int size = 0;
    for (dir * d : dirs) {
        if (d -> size <= 100000) {
            size += d -> size;
            cout << d -> name << endl;
        }
        size += print_small_dirs(d -> dirs);
    }
    return size;
}

int find_smallest_fitting_dir(ExtendedVector<dir*> dirs) {
    int current_size = 42143088;
    int needed_size = 40000000;
    int max_size = 70000000;
    vector<int> returns = {};
    returns.push_back(max_size);
    for (dir * d : dirs) {
        if (d -> size >= current_size-needed_size) {
            returns.push_back(d -> size);
            returns.push_back(find_smallest_fitting_dir(d -> dirs));
        }
    }
    return *min_element(returns.begin(), returns.end());
}

int main() {

    string item;
    ifstream myfile("aoc07.txt");

    ExtendedVector<dir*> root = {};
    struct dir slash;
    slash.name = "/";
    root.push_back(&slash);
    dir * pointer = &slash;

    while ( getline(myfile, item) ) {
        vector<string> command = split(item, ' ');
        ExtendedVector<string> ext_command = {};

        ext_command.assign(command.begin(), command.end());

        if (ext_command.front() == "$") {
            if (ext_command[1] == "cd") {
                if (ext_command[2] == "..") {
                    pointer = pointer -> parent;
                } else {
                    for (dir * d : pointer -> dirs) {
                        if (d -> name == ext_command[2]) {
                            pointer = d;
                            break;
                        }
                    }
                }
            }

        } else if (ext_command.front() == "dir") {
            struct dir * new_dir = new struct dir();
            new_dir -> name = ext_command[1];
            new_dir -> parent = pointer;
            pointer -> dirs.push_back(new_dir);
        } else {
            struct file * new_file = new struct file();
            new_file -> size = stoi(ext_command.front());
            new_file -> name = ext_command[1];
            pointer -> files.push_back(new_file);
        }
    }

    cout << get_dirsize(root);
    print_structure(root, 0);

    cout << print_small_dirs(root) << endl;

    cout << "delete: " << find_smallest_fitting_dir(root) << endl;
    

    // Close the file
    myfile.close();
}