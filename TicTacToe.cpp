#include <iostream>
#include <vector>
using namespace std;

void printTicTacToe(vector<vector<string>> &ticTacToe)
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
                cout << " ";
            cout << ticTacToe[i][j];
            if (j < 2)
                cout << " | ";
        }
        if (i < 2)
            cout << "\n-----------\n";
    }
    cout << "\n\n";
}

bool isValidCell(vector<vector<string>> &ticTacToe, pair<int, int> position)
{
    return ticTacToe[position.first][position.second] == " ";
}

pair<int, int> getUserSelection(vector<vector<string>> &ticTacToe)
{
    int cellNumber;
    pair<int, int> position;
    do
    {
        cout << "Enter the cell number (1-9) to add your 'O':\t";
        cin >> cellNumber;
        if (cellNumber < 1 || cellNumber > 9)
            continue;
        cellNumber--;
        position = {cellNumber / 3, cellNumber % 3};
    } while (!isValidCell(ticTacToe, position));
    return position;
}

string getWinner(vector<vector<string>> &ticTacToe)
{
    for (int i = 0; i < 3; i++)
    {
        if (ticTacToe[i][0] != " " && ticTacToe[i][0] == ticTacToe[i][1] && ticTacToe[i][1] == ticTacToe[i][2])
            return ticTacToe[i][0];
        if (ticTacToe[0][i] != " " && ticTacToe[0][i] == ticTacToe[1][i] && ticTacToe[1][i] == ticTacToe[2][i])
            return ticTacToe[0][i];
    }
    if (ticTacToe[1][1] != " " && ((ticTacToe[0][0] == ticTacToe[1][1] && ticTacToe[1][1] == ticTacToe[2][2]) || (ticTacToe[0][2] == ticTacToe[1][1] && ticTacToe[1][1] == ticTacToe[2][0])))
        return ticTacToe[1][1];

    bool emptySpotAvailable = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ticTacToe[i][j] == " ")
                emptySpotAvailable = true;
        }
    }
    return emptySpotAvailable ? "-1" : " ";
}

int miniMax(vector<vector<string>> ticTacToe, bool isMax)
{
    string winner = getWinner(ticTacToe);
    if (winner != "-1")
        return winner == "O"
                   ? -1
               : winner == "X"
                   ? 1
                   : 0;

    int value = isMax ? INT_MIN : INT_MAX;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ticTacToe[i][j] == " ")
            {
                ticTacToe[i][j] = isMax ? "X" : "O";
                int result = miniMax(ticTacToe, !isMax);
                ticTacToe[i][j] = " ";
                value = isMax ? max(value, result) : min(value, result);
            }
        }
    }

    return value;
}

pair<int, int> getAISelection(vector<vector<string>> &ticTacToe)
{
    int maxValue = INT_MIN;
    pair<int, int> position;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ticTacToe[i][j] == " ")
            {
                ticTacToe[i][j] = "X";
                int value = miniMax(ticTacToe, false);
                ticTacToe[i][j] = " ";
                if (maxValue < value)
                {
                    maxValue = value;
                    position = {i, j};
                }
            }
        }
    }
    cout << "AI's turn added 'X' at position '" << (position.first * 3) + (position.second) + 1 << "'\n";
    return position;
}

int main()
{
    vector<vector<string>> ticTacToe = {{" ", " ", " "},
                                        {" ", " ", " "},
                                        {" ", " ", " "}};
    cout << "Hello, you as a User will be assigned 'O' and Computer will play using 'X'\n";
    printTicTacToe(ticTacToe);

    int moves = 0;
    while (moves < 9)
    {
        pair<int, int> position = (moves & 1) ? getUserSelection(ticTacToe) : getAISelection(ticTacToe);
        ticTacToe[position.first][position.second] = (moves & 1) ? "O" : "X";
        printTicTacToe(ticTacToe);
        string winner = getWinner(ticTacToe);
        if (winner != "-1")
        {
            cout << (winner == "O"
                         ? "You"
                     : winner == "X"
                         ? "Computer"
                         : "No one")
                 << " Won!\n";
            cout << "You both played '" << moves + 1 << "' moves!\n";
            break;
        }
        moves++;
    }

    return 0;
}