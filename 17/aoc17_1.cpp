#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Block {
    int width;
    int ident;
    vector<pair<int, int>> points;
    int pos;
    void reset()
    {
        pos = 2;
    }
};

vector<Block> blocks = {
    {4, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 2},
    {3, 1, {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}}, 2},
    {3, 2, {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}}, 2},
    {1, 3, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 2},
    {2, 4, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, 2}
};

vector<char> directions;
vector<set<int>> room = {{-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}};

int first = 247;
int between = 1755;
int height = 2747;
vector<set<int>> r = {};

bool get_xy(int x, int y) {
    return room[x].count(y) > 0;
}

void set_xy(int x, int y) {
    room[x].insert(y);
}

int set_to_int(const std::set<int>& s) {
  // Check if the set is empty
  if (s.empty()) {
    // Return 0 if the set is empty
    return 0;
  }

  // Initialize a variable to store the result
  int result = 0;

  // Iterate over the elements in the set
  for (auto it = s.begin(); it != s.end(); ++it) {
    // Add the element to the result
    result += *it;
  }

  // Return the result
  return result;
}
void calc(int i) {
    int y = set_to_int(*max_element(room.begin(), room.end(), [](const auto &lhs, const auto &rhs) { return *max_element(lhs.begin(), lhs.end()) < *max_element(rhs.begin(), rhs.end()); })) + 4;
    static int idx = 0;
    for (const char &d : directions) {
        if (d == 'down') {
            if (any_of(blocks[idx].points.begin(), blocks[idx].points.end(), [&](const auto &point) { return get_xy(blocks[idx].pos + point.first, y + point.second - 1); })) {
                break;
            } else {
                --y;
            }
        } else {
            if (d == '<') {
                if (blocks[idx].pos >= 1 && !any_of(blocks[idx].points.begin(), blocks[idx].points.end(), [&](const auto &point) { return get_xy(blocks[idx].pos + point.first - 1, y + point.second); })) {
                    --blocks[idx].pos;
                }
            }
            else {
                if (blocks[idx].pos <= 6 - blocks[idx].width && !any_of(blocks[idx].points.begin(), blocks[idx].points.end(), [&](const auto &point) { return get_xy(blocks[idx].pos + point.first + 1, y + point.second); })) {
                    ++blocks[idx].pos;
                }
            }
        }
    }
    for (const auto &point : blocks[idx].points) {
        set_xy(blocks[idx].pos + point.first, y + point.second);
    }
    if ((i - first + between) % (between + 1) == 0) {
        idx = (idx + 1) % blocks.size();
        blocks[idx].reset();
    }
}

int main() {
    for (int i = 0; i < height; ++i) {
        calc(i);
    }
    cout << set_to_int(*max_element(room.begin(), room.end(), [](const auto &lhs, const auto &rhs) { return *max_element(lhs.begin(), lhs.end()) < *max_element(rhs.begin(), rhs.end()); })) << endl;
    return 0;
}
