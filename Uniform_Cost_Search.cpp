#include <bits/stdc++.h>
#define mii map<int, int>
#define vi vector<int>
#define int long long int
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define mod 100000007
using namespace std;


vector<vector<int>> graph;
map<pair<int, int>, int> edgeCost;

vector<int> uniformCostSearch(vector<int> goal, int start)
{
  
    vector<int> minCost;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

    for (int i = 0; i < goal.size(); i++)
    {
        minCost.push_back(INT_MAX);
    }

    priorityQueue.push(make_pair(0, start));

    map<int, int> visited;
    int count = 0;

    while (!priorityQueue.empty())
    {

        pair<int, int> topElement = priorityQueue.top();
        priorityQueue.pop();

       
        if (find(goal.begin(), goal.end(), topElement.second) != goal.end())
        {
            int index = find(goal.begin(), goal.end(), topElement.second) - goal.begin();

            if (minCost[index] == INT_MAX)
                count++;
            if (minCost[index] > topElement.first)
                minCost[index] = topElement.first;
            if (count == goal.size())
                return minCost;
        }
        if (visited[topElement.second] == 0)
        {
            for (int neighbor : graph[topElement.second])
            {
                priorityQueue.push(make_pair((topElement.first +edgeCost[make_pair(topElement.second, neighbor)]),neighbor));
            }
        }
        visited[topElement.second] = 1;
    }

    return minCost;
}

int32_t main()
{
    graph.resize(7);

    graph[0].push_back(1);
    graph[0].push_back(3);
    graph[3].push_back(1);
    graph[3].push_back(6);
    graph[3].push_back(4);
    graph[1].push_back(6);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[2].push_back(1);
    graph[5].push_back(2);
    graph[5].push_back(6);
    graph[6].push_back(4);

    edgeCost[make_pair(0, 1)] = 2;
    edgeCost[make_pair(0, 3)] = 5;
    edgeCost[make_pair(1, 6)] = 1;
    edgeCost[make_pair(3, 1)] = 5;
    edgeCost[make_pair(3, 6)] = 6;
    edgeCost[make_pair(3, 4)] = 2;
    edgeCost[make_pair(2, 1)] = 4;
    edgeCost[make_pair(4, 2)] = 4;
    edgeCost[make_pair(4, 5)] = 3;
    edgeCost[make_pair(5, 2)] = 6;
    edgeCost[make_pair(5, 6)] = 3;
    edgeCost[make_pair(6, 4)] = 7;

    vector<int> goal;
    goal.push_back(6);

    vector<int> result = uniformCostSearch(goal, 0);

    cout << "Minimum cost g = " << result[0] << endl;

    return 0;
}
