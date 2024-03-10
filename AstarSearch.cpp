#include<bits/stdc++.h>
#define mii map<int, int> 
#define vi vector<int> 
#define ll long long int 
#define f first
#define s second 
#define pb push_back 
#define mp make_pair 
#define mod 100000007
using namespace std;

// Define node structure
struct Vertex {
    int a, b; // coordinates of the node
    int c, d, e; // cost parameters for pathfinding
    Vertex* parent; // pointer to parent node
};

// Function to calculate Manhattan distance heuristic
int calculateHeuristic(Vertex* current, Vertex* end) {
    return abs(current->a - end->a) + abs(current->b - end->b);
}

// Function to check if the node is within the grid
bool isValidCoordinate(int a, int b, int rows, int cols) {
    return (a >= 0 && a < rows && b >= 0 && b < cols);
}

// Function to implement A* algorithm
vector<pair<int, int>> AStarAlgorithm(vector<vector<int>>& grid, Vertex* start, Vertex* end) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Define moves in 4 directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Priority queue to store nodes to be explored
    priority_queue<pair<int, Vertex*>> queu;
    start->d = calculateHeuristic(start, end);
    start->e = start->c + start->d;
    
    queu.push({-start->e, start});

    // Initialize visited array
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    while (!queu.empty()) {
        Vertex* current = queu.top().second;
        queu.pop();

        // Check if current node is the end node
        if (current->a == end->a && current->b == end->b) {
            vector<pair<int, int>> path;
            while (current != NULL) {
                path.push_back({current->a, current->b});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited[current->a][current->b] = true;

        for (int i = 0; i < 4; i++) {
            int newA = current->a + dx[i];
            int newB = current->b + dy[i];
            
            if (isValidCoordinate(newA, newB, rows, cols) && grid[newA][newB] != 1 && !visited[newA][newB]) {
                Vertex* newVertex = new Vertex({newA, newB});
                newVertex->c = current->c + 1;
                newVertex->d = calculateHeuristic(newVertex, end);
                newVertex->e = newVertex->c + newVertex->d;
                newVertex->parent = current;

                queu.push({-newVertex->e, newVertex});
            }
        }
    }

    return {};
}

int32_t main() {
    int rows, cols;
    cout << "Enter the number of rows and columns of the grid: ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // Input the grid
    cout << "Enter the grid (0 for empty, 1 for obstacle):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }

    int startCoordinateA, startCoordinateB, endCoordinateA, endCoordinateB;
    cout << "Enter the starting point coordinates (a b): ";
    cin >> startCoordinateA >> startCoordinateB;
    cout << "Enter the ending point coordinates (a b): ";
    cin >> endCoordinateA >> endCoordinateB;

    Vertex* startPoint = new Vertex({startCoordinateA, startCoordinateB});
    Vertex* endPoint = new Vertex({endCoordinateA, endCoordinateB});

    vector<pair<int, int>> path = AStarAlgorithm(grid, startPoint, endPoint);

    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Path found:" << endl;
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
