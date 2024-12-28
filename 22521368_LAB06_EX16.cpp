#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Structure for grid cell
struct Cell
{
    int x, y;
    int f, g, h; // f = g + h
    Cell *parent;

    Cell(int x = 0, int y = 0) : x(x), y(y), f(0), g(0), h(0), parent(nullptr) {}
};

// Structure to compare cells in priority queue
struct CompareCell
{
    bool operator()(const Cell *a, const Cell *b)
    {
        return a->f > b->f;
    }
};

class PathFinder
{
private:
    vector<vector<int>> grid;
    int rows, cols;

    // Check if a cell is valid and walkable
    bool isValid(int x, int y)
    {
        return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
    }

    // Calculate heuristic (Manhattan distance)
    int calculateHeuristic(int x, int y, int destX, int destY)
    {
        return abs(x - destX) + abs(y - destY);
    }

public:
    PathFinder(int r, int c) : rows(r), cols(c)
    {
        // Initialize grid with 0s (walkable) and 1s (obstacles)
        grid = vector<vector<int>>(rows, vector<int>(cols, 0));

        // Add some obstacles (1s)
        grid[1][1] = 1;
        grid[1][2] = 1;
        grid[2][1] = 1;
        grid[3][3] = 1;
    }

    vector<pair<int, int>> findPath(int startX, int startY, int endX, int endY)
    {
        vector<pair<int, int>> path;
        priority_queue<Cell *, vector<Cell *>, CompareCell> openList;
        vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

        Cell *start = new Cell(startX, startY);
        start->f = start->h = calculateHeuristic(startX, startY, endX, endY);

        openList.push(start);

        // Direction arrays for 4-directional movement
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!openList.empty())
        {
            Cell *current = openList.top();
            openList.pop();

            int x = current->x;
            int y = current->y;

            closedList[x][y] = true;

            // If we reached the destination
            if (x == endX && y == endY)
            {
                // Reconstruct path
                while (current != nullptr)
                {
                    path.push_back({current->x, current->y});
                    current = current->parent;
                }
                reverse(path.begin(), path.end());
                return path;
            }

            // Check all adjacent cells
            for (int i = 0; i < 4; i++)
            {
                int newX = x + dx[i];
                int newY = y + dy[i];

                if (isValid(newX, newY) && !closedList[newX][newY])
                {
                    Cell *successor = new Cell(newX, newY);
                    successor->g = current->g + 1;
                    successor->h = calculateHeuristic(newX, newY, endX, endY);
                    successor->f = successor->g + successor->h;
                    successor->parent = current;

                    openList.push(successor);
                }
            }
        }

        return path; // Empty path if no route found
    }

    void printGrid(const vector<pair<int, int>> &path)
    {
        vector<vector<char>> display(rows, vector<char>(cols, '.'));

        // Mark obstacles
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 1)
                    display[i][j] = '#';
            }
        }

        // Mark path
        for (const auto &p : path)
        {
            display[p.first][p.second] = '*';
        }

        // Print the grid
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << display[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

int main()
{
    PathFinder finder(5, 5);

    // Find path from (0,0) to (4,4)
    vector<pair<int, int>> path = finder.findPath(0, 0, 4, 4);

    if (path.empty())
    {
        cout << "No path found!" << endl;
    }
    else
    {
        cout << "Path found! The route is:" << endl;
        finder.printGrid(path);
    }

    return 0;
}