#include <bits/stdc++.h>
using namespace std;

// function to check if the block we are trying to move is save to move or not
bool isSafe(int i, int j)
{
    return i >= 0 && j >= 0 && i < 3 && j < 3;
}

// getting number of misplaced tiles
int getNumberOfMisplacedTiles(vector<vector<int>> &input, vector<vector<int>> &output)
{
    int misplaced = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (input[i][j] != output[i][j])
                misplaced++;
        }
    }
    return misplaced == 0 ? 0 : misplaced - 1;
}

// printing the 8-puzzle
void print(vector<vector<int>> &arr)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << arr[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

// custom class to add data to the priority_queue
class QueueItem
{
public:
    vector<vector<int>> input;
    pair<int, int> index;

    QueueItem(vector<vector<int>> input, pair<int, int> index)
    {
        this->input = input;
        this->index = index;
    }
};

int solve(vector<vector<int>> &input, vector<vector<int>> &output, pair<int, int> index)
{
    int iMove[] = {-1, 1, 0, 0};
    int jMove[] = {0, 0, -1, 1};
    int depth = 0;
    // priority queue with "f(n) = g(n) + h(n)" as min priority value
    priority_queue<pair<int, QueueItem *>, vector<pair<int, QueueItem *>>, greater<pair<int, QueueItem *>>> minHeap;
    minHeap.push({depth + getNumberOfMisplacedTiles(input, output), new QueueItem(input, index)});

    while (!minHeap.empty())
    {
        pair<int, QueueItem *> top = minHeap.top();
        minHeap.pop();
        int f = top.first;
        vector<vector<int>> currentInput = top.second->input;
        int i = top.second->index.first;
        int j = top.second->index.second;
        depth++;

        for (int k = 0; k < 4; k++)
        {
            int newI = i + iMove[k];
            int newJ = j + jMove[k];

            if (isSafe(newI, newJ))
            {
                swap(currentInput[newI][newJ], currentInput[i][j]);
                int misplacedTiles = getNumberOfMisplacedTiles(currentInput, output);
                print(currentInput);
                if (misplacedTiles == 0)
                    return depth;
                minHeap.push({depth + misplacedTiles, new QueueItem(currentInput, {newI, newJ})});
                swap(currentInput[newI][newJ], currentInput[i][j]);
            }
        }
    }

    return -1;
}

// getting the index of blank cell blank cell
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
    vector<vector<int>> input = {{1, 2, 3},
                                 {0, 4, 6},
                                 {7, 5, 8}};
    vector<vector<int>> output = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 0}};

    // vector<vector<int>> input = {{1, 2, 5},
    //                              {8, 6, 3},
    //                              {7, 4, 0}};
    // vector<vector<int>> output = {{1, 2, 3},
    //                               {8, 0, 4},
    //                               {7, 6, 5}};

    cout << solve(input, output, getBlank(input)) << "\n";

    return 0;
}

// vector<vector<int>> input = {{1, 2, 3},
//                              {8, 0, 4},
//                              {7, 6, 5}};
// vector<vector<int>> output = {{2, 8, 1},
//                               {0, 4, 3},
//                               {7, 6, 5}};
