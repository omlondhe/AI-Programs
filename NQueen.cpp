#include <iostream>
#include <vector>
using namespace std;

class NQueens
{
private:
    // checking if we can place the queen at the current position or not
    bool isSafe(int row, int column, vector<string> &current, int n)
    {
        for (int i = row; i >= 0; i--)
        {
            if (current[i][column] == 'Q')
                return false;
        }
        int leftDiagonal = column, rightDiagonal = column;
        while (row >= 0)
        {
            if (leftDiagonal >= 0 && current[row][leftDiagonal--] == 'Q')
                return false;
            if (rightDiagonal < n && current[row][rightDiagonal++] == 'Q')
                return

                    false;

            row--;
        }
        return true;
    }

    // trying to find all the possible solutions
    void solve(int row, int n, vector<string> current, vector<vector<string>> &ans)
    {
        if (row == n)
        {
            ans.push_back(current);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (isSafe(row, i, current, n))
            {
                current[row][i] = 'Q';
                solve(row + 1, n, current, ans);
                current[row][i] = '.';
            }
        }
    }

public:
    // generating the grid and solving the problem
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> current;
        string row = "";
        for (int j = 0; j < n; j++)
            row += '.';
        for (int i = 0; i < n; i++)
            current.push_back(row);
        solve(0, n, current, ans);
        return ans;
    }

    // pretty printing all the solutions
    void print(vector<vector<string>> ans, int n)
    {
        int len = n * 3 + n + 1;
        for (int i = 0; i < ans.size(); i++)
        {
            cout << "Solution " << i + 1 << ":\n";
            for (int i = 0; i < len; i++)
                cout << "-";
            cout << "\n";
            for (string s : ans[i])
            {
                cout << "|";
                for (int i = 0; i < s.length(); i++)
                {
                    if (s[i] == '.')
                        cout << "   ";
                    else
                        cout << " " << s[i] << " ";
                    cout << "|";
                }
                cout << "\n";
                for (int i = 0; i < len; i++)
                    cout << "-";
                cout << "\n";
            }
            cout << "\n\n";
        }
    }
};

int main()
{
    int n;
    cout << "Enter the number of Queens: ";
    cin >> n;
    NQueens *nQueens = new NQueens();
    nQueens->print(nQueens->solveNQueens(n), n);
    return 0;
}