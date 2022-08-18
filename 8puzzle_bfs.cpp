#include <bits/stdc++.h>
using namespace std;

bool isSafe(int i, int j)
{
    return i >= 0 && j >= 0 && i < 3 && j < 3;
}

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

int solve(vector<vector<int>> &input, vector<vector<int>> &output, pair<int, int> index)
{
    int iMove[] = {-1, 1, 0, 0};
    int jMove[] = {0, 0, -1, 1};
    queue<pair<pair<int, int>, vector<vector<int>>>> q;
    q.push({{index.first, index.second}, input});
    int iterations = 0;

    while (!q.empty())
    {
        int n = q.size();
        iterations++;

        while (n--)
        {
            auto front = q.front();
            q.pop();
            int i = front.first.first;
            int j = front.first.second;
            vector<vector<int>> currentInput = front.second;

            for (int k = 0; k < 4; k++)
            {
                int newI = i + iMove[k];
                int newJ = j + jMove[k];
                if (isSafe(newI, newJ))
                {
                    swap(currentInput[i][j], currentInput[newI][newJ]);
                    q.push({{newI, newJ}, currentInput});
                    print(currentInput);
                    if (currentInput == output)
                        return iterations;
                    swap(currentInput[i][j], currentInput[newI][newJ]);
                }
            }
        }
    }

    return iterations;
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
    vector<vector<int>> input = {{1, 2, 5},
                                 {8, 6, 3},
                                 {7, 4, 0}};
    vector<vector<int>> output = {{1, 2, 3},
                                  {8, 0, 4},
                                  {7, 6, 5}};

    cout << solve(input, output, getBlank(input)) << "\n";

    return 0;
}