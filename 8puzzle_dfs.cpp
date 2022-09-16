#include <bits/stdc++.h>
using namespace std;

// function to check if the block we are trying to move is save to move or not
bool isSafe(int i, int j)
{
    return i >= 0 && j >= 0 && i < 3 && j < 3;
}

// printing the 8-puzzle
void print(vector<vector<int>> arr)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << arr[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void solve(vector<vector<int>> input, vector<vector<int>> &output, int i, int j, vector<int> &iterations, int depth, vector<vector<int>> &visited)
{
    if (input == output)
    {
        iterations.push_back(depth);
        return;
    }
    visited[i][j] = 1;
    int iMove[] = {-1, 1, 0, 0};
    int jMove[] = {0, 0, -1, 1};
    depth++;

    for (int k = 0; k < 4; k++)
    {
        int newI = i + iMove[k];
        int newJ = j + jMove[k];
        if (isSafe(newI, newJ) && !visited[newI][newJ])
        {
            swap(input[i][j], input[newI][newJ]);
            print(input);
            solve(input, output, newI, newJ, iterations, depth, visited);
            swap(input[i][j], input[newI][newJ]);
        }
    }
    visited[i][j] = 0;
    cout << "-----\n";
}

pair<int, int> getBlank(vector<vector<int>> input)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (input[i][j] == 0)
                return {i, j};
        }
    }
    return {1, 1};
}

int main()
{
    vector<vector<int>> input = {{1, 2, 0},
                                 {8, 4, 3},
                                 {7, 6, 5}};
    vector<vector<int>> output = {{1, 2, 3},
                                  {8, 0, 4},
                                  {7, 6, 5}};

    // vector<vector<int>> input = {{1, 2, 3},
    //                              {0, 4, 6},
    //                              {7, 5, 8}};
    // vector<vector<int>> output = {{1, 2, 3},
    //                               {4, 5, 6},
    //                               {7, 8, 0}};

    vector<vector<int>> visited = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    auto blankPosition = getBlank(input);
    vector<int> iterations;
    solve(input, output, blankPosition.first, blankPosition.second, iterations, 0, visited);

    cout << "______\n\n";
    for (int i : iterations)
        cout << i << " ";
    cout << "\n";

    return 0;
}