#ifndef GRAPH_H
#define GRAPH_H
#include <utility>
#include <vector>
#include <climits>
#include <tuple>
#include <string>
#include <map> 
#include <set>
#include <queue>
#include <stack>
#include <fstream>

const int INFINIT_COST = INT_MAX;

template <class T>
class Graph
{
private:
    std::map<T, std::map<T, int>> adjList;
    int numberOfEdges;
    int numberOfVertices;

public:
    Graph();
    virtual ~Graph() = default;
    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete;
    void addVertex(T theNode);
    void addEdge(T from, T to, int weight = 0);
    std::vector<T> getAllNeighboursTo(T vertex);
    int getNrOfVertices() const;
    int getNrOfEdges() const;
    void kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost);
    void prims(std::vector<std::tuple<T, T, int>>& mst, int& totalCost);
    void readFromFile(std::string file);

    std::string depthFirstSearch(T from);
    std::string breadthFirstSearch(T from);
};

#endif

template<class T>
Graph<T>::Graph()
{
    numberOfEdges = 0;
    numberOfVertices = 0;
}

template<class T>
void Graph<T>::addVertex(T theNode)
{
    if (adjList.find(theNode) != adjList.end()) {
        throw std::runtime_error("Cannot create duplicate nodes in addVertex.");
    }

    adjList[theNode] = std::map<T, int>();
    numberOfVertices++;
}

template<class T>
void Graph<T>::addEdge(T from, T to, int weight)
{
    if (adjList.find(from) == adjList.end()) {
        addVertex(from);
    }
    if (adjList.find(to) == adjList.end()) {
        addVertex(to);
    }

    adjList[from][to] = weight;
    adjList[to][from] = weight;
    numberOfEdges += 2;
}

template<class T>
std::vector<T> Graph<T>::getAllNeighboursTo(T vertex)
{
    std::vector<T> neighbors;
    for (auto entry : adjList[vertex]) {
        neighbors.push_back(entry.first);
    }

    std::sort(neighbors.begin(), neighbors.end());
    return neighbors;
}


template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
    std::vector<std::tuple<T, T, int>> edges;

    for (auto& [from, neighbors] : adjList) {
        for (auto& [to, weight] : neighbors) {
            if (from < to)
                edges.emplace_back(from, to, weight);
        }
    }

    std::sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return std::get<2>(a) < std::get<2>(b);
        });

    DisjointSets<T> ds(true, true); // Path Compression + Union by Rank

    for (auto& [from, to, _] : edges) {
        ds.makeSet(from);
        ds.makeSet(to);
    }

    for (auto& [from, to, weight] : edges) {
        if (ds.findSet(from) != ds.findSet(to)) {
            ds.unionSet(from, to);
            mst.emplace_back(from, to, weight);
            totalCost += weight;
        }
    }
}

template<class T>
void Graph<T>::prims(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
    if (adjList.empty()) return;

    std::set<T> inMST;
    std::priority_queue<std::tuple<int, T, T>, std::vector<std::tuple<int, T, T>>, std::greater<>> pq;

    T start = adjList.begin()->first;
    inMST.insert(start);

    for (auto& [neighbor, weight] : adjList[start]) {
        pq.emplace(weight, start, neighbor);
    }

    while (!pq.empty()) {
        auto [weight, from, to] = pq.top(); pq.pop();
        if (inMST.find(to) != inMST.end()) continue;
        inMST.insert(to);
        mst.emplace_back(from, to, weight);
        totalCost += weight;
        for (auto& [neighbor, w] : adjList[to]) {
            if (inMST.find(neighbor) == inMST.end()) {
                pq.emplace(w, to, neighbor);
            }
        }
    }
}


template<class T>
int Graph<T>::getNrOfVertices() const
{
    return numberOfVertices;
}

template<class T>
int Graph<T>::getNrOfEdges() const
{
    return numberOfEdges;
}

template<class T>
std::string Graph<T>::depthFirstSearch(T from)
{
    std::set<T> visited;
    std::stack<T> stack;
    std::vector<T> order;

    stack.push(from);

    while (!stack.empty()) {
        T node = stack.top();
        stack.pop();

        if (visited.find(node) != visited.end()) continue;

        visited.insert(node);
        order.push_back(node);

        auto neighbors = getAllNeighboursTo(node);
        std::reverse(neighbors.begin(), neighbors.end());
        for (auto neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                stack.push(neighbor);
            }
        }  
    }

    std::string result;
    for (int i = 0; i < order.size(); ++i) {
        result += order[i];
        if (i < order.size() - 1) {
            result += ",";
        }
    }

    return result;
}


template<class T>
std::string Graph<T>::breadthFirstSearch(T from)
{
    std::set<T> visited;
    std::queue<T> queue;
    std::vector<T> order;

    queue.push(from);
    visited.insert(from);

    while (!queue.empty()) {
        T node = queue.front();
        queue.pop();
        order.push_back(node);

        auto neighbors = getAllNeighboursTo(node);
        for (auto neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }

    std::string result;
    for (int i = 0; i < order.size(); ++i) {
        result += order[i];
        if (i < order.size() - 1) {
            result += ",";
        }
    }

    return result;
}


template<class T>
void Graph<T>::readFromFile(std::string file)
{
    std::ifstream infile(file);
    std::string from, to;
    int weight;
    while (infile >> from >> to >> weight) {
        addEdge(from, to, weight);
    }
}
