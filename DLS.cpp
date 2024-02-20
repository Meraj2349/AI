#include<bits/stdc++.h>
#define mii map<int, int> 
#define vi vector<int> 
#define int long long int 
#define f first
#define s second 
#define pb push_back 
#define mp make_pair 
#define mod 100000007
using namespace std;

// Depth Limited Search function
bool DLS(int current, int target, int depth, const vector<vector<int>>& graph, vector<bool>& visited) {
    if (current == target)
        return true;
    
    if (depth <= 0)
        return false;

    visited[current] = true;

    for (int neighbor : graph[current]) {
        if (!visited[neighbor] && DLS(neighbor, target, depth - 1, graph, visited))
            return true;
    }

    return false;
}

int32_t main() {
    int vertices = 7;
    vector<vector<int>> graph(vertices);

    // Adding edges to the graph
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[1].push_back(4);
    graph[2].push_back(5);
    graph[2].push_back(6);

    int source = 0, target = 6, depth_limit = 3;

    vector<bool> visited(vertices, false);

    if (DLS(source, target, depth_limit, graph, visited))
        cout << "found\n";
    else
        cout << "no found\n";

    return 0;
}
