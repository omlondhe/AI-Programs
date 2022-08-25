#include <bits/stdc++.h>
using namespace std;

bool isSafe(int i, int j)
{
    return i >= 0 && j >= 0 && i < 3 && j < 3;
}

int getNumberOfMisplacedTiles(vector<vector<int>> input, vector<vector<int>> output)
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

class QueueItem
{
public:
    int parentI;
    int parentJ;
    int i;
    int j;
    vector<vector<int>> input;

    QueueItem(int parentI,
              int parentJ,
              int i,
              int j,
              vector<vector<int>> input)
    {
        this->parentI = parentI;
        this->parentJ = parentJ;
        this->i = i;
        this->j = j;
        this->input = input;
    }
};

class PuzzleAndZeroPosition
{
public:
    int i;
    int j;
    int newI;
    int newJ;
    vector<vector<int>> input;

    PuzzleAndZeroPosition(
        int i,
        int j,
        int newI,
        int newJ,
        vector<vector<int>> input)
    {
        this->i = i;
        this->j = j;
        this->newI = newI;
        this->newJ = newJ;
        this->input = input;
    }
};

int solve(vector<vector<int>> &input, vector<vector<int>> &output, pair<int, int> index)
{
    int iMove[] = {-1, 1, 0, 0};
    int jMove[] = {0, 0, -1, 1};
    queue<QueueItem *> q;
    q.push(new QueueItem(-1, -1, index.first, index.second, input));
    int depth = 0;
    int numberOfMisplacedTiles = getNumberOfMisplacedTiles(input, output);

    while (!q.empty())
    {
        int n = q.size();
        depth++;
        priority_queue<pair<int, PuzzleAndZeroPosition *>, vector<pair<int, PuzzleAndZeroPosition *>>, greater<pair<int, PuzzleAndZeroPosition *>>> minHeap;
        int minimumNumberOfMisplacedTiled = INT_MAX;

        while (n--)
        {
            QueueItem *front = q.front();
            q.pop();
            int i = front->i;
            int j = front->j;
            vector<vector<int>> currentInput = front->input;

            for (int k = 0; k < 4; k++)
            {
                int newI = i + iMove[k];
                int newJ = j + jMove[k];
                if (isSafe(newI, newJ) && newI != front->parentI && newJ != front->parentJ)
                {
                    swap(currentInput[i][j], currentInput[newI][newJ]);
                    numberOfMisplacedTiles = getNumberOfMisplacedTiles(currentInput, output);
                    if (numberOfMisplacedTiles == 0)
                    {
                        print(currentInput);
                        return depth;
                    }
                    minimumNumberOfMisplacedTiled = min(minimumNumberOfMisplacedTiled, numberOfMisplacedTiles);
                    minHeap.push({numberOfMisplacedTiles, new PuzzleAndZeroPosition(i, j, newI, newJ, currentInput)});
                    swap(currentInput[i][j], currentInput[newI][newJ]);
                }
            }
        }

        while (!minHeap.empty() && minHeap.top().first == minimumNumberOfMisplacedTiled)
        {
            PuzzleAndZeroPosition *puzzleAndZeroPosition = minHeap.top().second;
            minHeap.pop();
            q.push(new QueueItem(puzzleAndZeroPosition->i, puzzleAndZeroPosition->j, puzzleAndZeroPosition->newI, puzzleAndZeroPosition->newJ, puzzleAndZeroPosition->input));
            print(puzzleAndZeroPosition->input);
        }
    }

    return depth;
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
    // looping
    // vector<vector<int>> input = {{1, 2, 5},
    //                              {8, 6, 3},
    //                              {7, 4, 0}};
    // vector<vector<int>> output = {{1, 2, 3},
    //                               {8, 0, 4},
    //                               {7, 6, 5}};

    // working
    // vector<vector<int>> input = {{1, 2, 3},
    //                              {0, 4, 6},
    //                              {7, 5, 8}};
    // vector<vector<int>> output = {{1, 2, 3},
    //                               {4, 5, 6},
    //                               {7, 8, 0}};

    // looping
    vector<vector<int>> input = {{1, 2, 3},
                                 {8, 0, 4},
                                 {7, 6, 5}};
    vector<vector<int>> output = {{2, 8, 1},
                                  {0, 4, 3},
                                  {7, 6, 5}};

    cout << solve(input, output, getBlank(input)) << "\n";

    return 0;
}
