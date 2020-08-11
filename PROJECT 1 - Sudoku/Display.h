#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;

/*=================================================================
Function to display SUDOKU
=================================================================*/
void display(vector<vector<int>> &board)
{
    int n = board.size();
    int sqrtN = sqrt(n);
    for(int i=0;i<n;i++)
    {
        if( (i % sqrtN) == 0)
            for(int j=0;j<=3*n + 4;j++)
                cout<<"-";
        cout<<"\n";

        for(int j=0;j<n;j++)
        {
            if((j % sqrtN) == 0)
                cout<<"|";
            
            if(board[i][j])
                cout<<setw(3)<<board[i][j];
            else
                cout<<setw(3)<<" ";
        }
        cout<<"|\n";
    }
    for(int j=0;j<=3*n + 4;j++)
        cout<<"-";
    cout<<"\n";
}