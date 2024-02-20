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


// Function for BFS traversal
bool BFS(vector<vector<int>>& graph, int source, int target, int max_depth) {
    queue<pair<int, int>> q; 
    q.push({source, 0}); 
    
    while (!q.empty()) {
        int node = q.front().first;
        int depth = q.front().second;
        q.pop();

        if (node == target)
            return true; 

        if (depth < max_depth) {
            for (int neighbor : graph[node]) {
                q.push({neighbor, depth + 1}); 
            }
        }
    }

    return false; 
}

// Function for Iterative Deepening Search
bool IDS(vector<vector<int>>& graph, int source, int target, int max_depth) {
    for (int depth_limit = 0; depth_limit <= max_depth; ++depth_limit) {
        if (BFS(graph, source, target, depth_limit))
            return true;
    }
    return false;
}

int32_t main()
 {
    
     int vertices = 7;
    vector<vector<int>> graph(vertices);
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[1].push_back(4);
    graph[2].push_back(5);
    graph[2].push_back(6);

    int source = 0, target = 4, max_depth = 2;

    if (IDS(graph, source, target, max_depth))

        cout << "Target Found  maximum depth\n";
    else
        cout << "Target found maximum depth\n";

    return 0;
}
