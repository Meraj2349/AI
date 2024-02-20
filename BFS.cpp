#include <bits/stdc++.h>
using namespace std;

int32_t main()
{
    bool visited[100];
    vector<vector<int>> adj(100);

    for (int i = 0; i < 100; i++)
    {
        visited[i] = false;
    }

    cout << "Enter nodes and edges: ";

    int edge, node;
    cin >> edge >> node;

    cout << "Enter node1 node2 :" << endl;
    int x_connected, y_connected;

    for (int i = 0; i < edge; i++)
    {
        cin >> x_connected >> y_connected;
        adj[x_connected].push_back(y_connected);
        adj[y_connected].push_back(x_connected);
    }
    queue<int> q;

    // starting node

    q.push(1);

    visited[1] = true;

    while (!q.empty())
    {
        int currentNode = q.front();
        cout << "visited node :" << currentNode << endl;
        q.pop();

        for (int i = 0; i < adj[currentNode].size(); i++)
        {
            int adjNode = adj[currentNode][i];

            if (!visited[adjNode])
            {
                visited[adjNode] = true;
                q.push(adjNode);
            }

            /* code */
        }

        /* code */
    }
    return 0;
}
// input:
// Enter nodes and edges:
// 3 3
// Enter node1 node2 :
// 1 2 
// 1 3
// 1 4
// output:
// 1
// 2
// 3
// 4