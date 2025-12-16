#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <unordered_map>
#include <iostream>
#include <vector>

template <class T>
class DisjointSets {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
    bool usePathCompression;
    bool useUnionByRank;

public:
    DisjointSets(bool pathCompression = false, bool unionByRank = false);
    int size();
    void makeSet(T u);
    T findSet(T u);
    void unionSet(T u, T v);
    T getParent(T u);
};

template <class T>
DisjointSets<T>::DisjointSets(bool pathCompression, bool unionByRank)
    : usePathCompression(pathCompression), useUnionByRank(unionByRank) {}

template <class T>
int DisjointSets<T>::size() {
    return parent.size();
}

template <class T>
void DisjointSets<T>::makeSet(T u) {
    if (parent.find(u) == parent.end()) {
        parent[u] = u;
        rank[u] = 0;
    }
}

template <class T>
T DisjointSets<T>::findSet(T u) {
    if (parent[u] != u) {
        if (usePathCompression) {
            parent[u] = findSet(parent[u]);
        }
        else {
            return findSet(parent[u]);
        }
    }
    return parent[u];
}

template <class T>
void DisjointSets<T>::unionSet(T u, T v) {
    T rootU = findSet(u);
    T rootV = findSet(v);

    if (rootU == rootV) return;

    if (useUnionByRank) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
    else {
        parent[rootV] = rootU;
    }
}


template <class T>
T DisjointSets<T>::getParent(T u) {
    if (parent.find(u) != parent.end()) {
        return parent[u];
    }
    return T();
}

#endif
