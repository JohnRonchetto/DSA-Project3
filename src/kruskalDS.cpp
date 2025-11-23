#include "kruskalDS.h"

DSU::DSU(const std::vector<int> &elements) {
    for (auto x : elements) {
        parent[x] = -1;
    }
}

int DSU::find(int x) {
    // check if x is known, if not create a set for it
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
        return x;
    }

    // if parent[x] = -1 -> x is the representative
    if (parent[x] == -1) {
        return x;
    }

    // otherwise, follow parent recursively
    return find(parent[x]);
}

bool DSU::merge(int a, int b) {
    // find representative root for each element
    int repA = find(a);
    int repB = find(b);

    // same representative -> same set
    // No merge (cycle detected)
    if (repA == repB) {
        return false;
    }

    // point representative of one set to the other
    parent[repA] = repB;

    return true;

}
