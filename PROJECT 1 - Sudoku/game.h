#include<stack>
#include<unordered_set>
#include"Display.h"
#include"generate.h"
using namespace std;

/*==============================================================
Function to print instructions of game
==============================================================*/
void instructions()
{
    cout<<"\nPress S or s to solve Sudoku.";
    cout<<"\nPress I or i to input.";
    cout<<"\nPress U or u to undo.";
    cout<<"\nPress E or e to exit.";
    cout<<"\n";
}

/*==============================================================
Clears all the entries done by user in sudoku
==============================================================*/
void clear(vector<vector<int>> &board, stack<pair<int,int>> &st, int &N)
{
    while(st.size() != 0)
    {
        pair<int,int> rVal;
        rVal = st.top();
        st.pop();

        board[rVal.first/N][rVal.first%N] = rVal.second;
    }
}

/*====================================================================
Used to undo a change done by user in sudoku (implemented using stack)
====================================================================*/
void undo(vector<vector<int>> &board,stack<pair<int,int>> &st, int &N)
{
    //if stack size is 0
    if(st.size() == 0)
    {
        cout<<"\nMake a move first!";
        return;
    }

    pair<int,int> rVal;
    rVal = st.top();
    st.pop();

    board[rVal.first/N][rVal.first%N] = rVal.second;
    display(board);
}

/*==============================================================
Function to call Solve function from solver.h
==============================================================*/
void betterCallSolve(vector<vector<int>> &board,stack<pair<int,int>> &st, int &N)
{
    //if sudoku is invalid (because of incorrect entries by user)
    //clears the entries done by user and solves it
    if(!Solve(board))
    {
        cout<<"The board can't be solved because of wrong entries. Clearing all the entries!\n";
        clear(board,st,N);
        Solve(board,false);
    }

    cout<<"SOLUTION:\n";
    display(board);
}

/*==============================================================
Function to take input from user 
==============================================================*/
void userInput(vector<vector<int>> &board, int &N, unordered_set<int> &blocksToBeFilled, stack<pair<int,int>> &st)
{
    int r=0,c=0,val=0;

    //inputs the row number and checks if it is valid or not
    while(true)
    {
        cout<<"\nEnter row: ";
        cin>>r;
        if(r>=1 && r<=N)
            break;
        else
            cout<<"\nInvalid row number. Input again.";
    }

    //inputs the column number and checks if it is valid or not
    while(true)
    {
        cout<<"Enter column: ";
        cin>>c;
        if(c>=1 && c<=N)
            break;
        else
            cout<<"\nInvalid column number. Input again.";
    }

    //inputs the value to be filled at the r-th row and c-th column and checks if it is valid or not
    while(true)
    {
        cout<<"Enter number: ";
        cin>>val;
        if(val>=1 && val<=N)
            break;
        else
            cout<<"\nInvalid value. Input again.";
    }

    --r,--c;

    //checks if the original sudoku is not being corrupted
    if(blocksToBeFilled.count(r*N+c))
    {
        st.push({r*N+c,board[r][c]});
        board[r][c] = val;
        display(board);
    }
    else{
        cout<<"You are not allowed to change the sudoku! Fill an empty block.\n";
    }
}

/*==============================================================
Just see its name
==============================================================*/
void playGame(vector<vector<int>> &board, int N, unordered_set<int> &blocksToBeFilled)
{
    int sqrtN = sqrt(N);
    stack<pair<int,int>> st;            //stack to implement undo and clear operations
    while(true)
    {
        instructions();                 //prints instructions
    
        char c;
        cin>>c;

        if(c == 'S' || c == 's')
        {
            betterCallSolve(board,st,N);
            break;
        }
        else if(c == 'I' || c == 'i')
        {
            userInput(board,N,blocksToBeFilled,st);
        }
        else if(c == 'U' || c == 'u')
        {
            undo(board, st, N);
        }
        else if(c == 'E' || c == 'e')
        {
            break;
        }
        else
        {
            cout<<"Wrong choice!\n";
        }
    }
}