#ifndef PROJECT3_KRUSKALDS_H
#define PROJECT3_KRUSKALDS_H

#include <vector>
#include <unordered_map>

// disjoint set union for Kruskal
class DSU {
private:
    // Keeps track of which elements are together
    // basically have a "representative" parent for each element in the same set
    // if parent[x] == -1 -> then x is the root representative of its set
    std::unordered_map<int, int> parent;

public:
    DSU() = default;

    // initializes all elements as single sets, where
    // for each element x, parent[x] == -1
    DSU(const std::vector<int> &elements);

    // identify set that contains x (the representative root)
    int find(int x);

    // merge set that contains a and set containing b
    // false if a and b are in the same set (cycle detection)
    bool merge(int a, int b);
};


#endif //PROJECT3_KRUSKALDS_H