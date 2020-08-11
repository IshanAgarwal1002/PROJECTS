#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

/*===========================================================================================================================
This class consists of three vectors to simulate the sudoku.
In the row vector (size N), at ith index all numbers present in the ith row in sudoku are stored using bit masking
In the column vector (size N), at ith index all numbers present in the ith column in sudoku are stored using bit masking
In the matrix vector (size N), at ith index all numbers present in the ith mini matrix in sudoku are stored using bit masking
===========================================================================================================================*/
class checkParameters
{
    public:
        vector<int> row;                //rowMap - stores which number from 1 to N is present in the ith row
        vector<int> col;                //colMap - stores which number from 1 to N is present in the jth col
        vector<vector<int>> matrix;     //matrixMap - stores which number from 1 to N is present in the mini matrix

        checkParameters(){}
        checkParameters(int N)
        {
            row.resize(N,0);
            col.resize(N,0);
            matrix.resize(N);
            for (int i=0;i<N;++i)
                matrix[i].resize(N,0);
        }
};

/*=========================================
checks if the sudoku is valid or invalid
=========================================*/
bool validate(vector<vector<int>> &board)
{
    int N = board.size();
    checkParameters P(N);
    
    int sqrtN = sqrt(N);    //stores the square root of N
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(board[i][j] != 0)
            {
                int mask = (1<<board[i][j]);

                //checks if the number is not present in ith row, jth column and the mini matrix
                if(!(P.row[i] & mask) && !(P.col[j] & mask) && !(P.matrix[i/sqrtN][j/sqrtN] & mask))
                {
                    P.row[i] ^= mask;
                    P.col[j] ^= mask;
                    P.matrix[i/sqrtN][j/sqrtN] ^= mask;
                }
                //if there are multiple instances of same number in same row or same column or same mini matrix
                //then the sudoku cannot be solved
                else{
                    return false;
                }
            }
        }
    }

    return true;
}

/*===========================================================================
Fills the calls vector which stores indices of blocks to be filled in sudoku
N - length of sudoku
================================================================================*/
void createCalls(vector<vector<int>> &board, int N, vector<int> &calls,checkParameters &P)     
{
    int sqrtN = sqrt(N);    //stores the square root of N
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            //pushes the index of block (initialised with 0) to be solved in the calls vector
            if(board[i][j]==0)
            {
                calls.push_back(i*N+j);
            } 
            //creates mask and turns the bits on wherever required
            else
            {
                int mask = (1<<board[i][j]);
                P.row[i] ^= mask;
                P.col[j] ^= mask;
                P.matrix[i/sqrtN][j/sqrtN] ^= mask;
            }
        }
    }
}

/*====================================================
Solves sudoku using Backtracking technique
======================================================*/
bool solve(vector<vector<int>> &board, vector<int> &calls, int &N,int idx,checkParameters &P)
{
    //return true when the sudoku is sully solved
    if(idx == calls.size())
    {
        return true;
    }

    bool res = false;
    int r = calls[idx] / N;     //row index
    int c = calls[idx] % N;     //column index
    int sqrtN = sqrt(N);

    //tries to place a number from 1 to N 
    for(int num=1;num<=N;num++)
    {
        int mask = (1<<num);

        //checks if the number is not present in ith row, jth column and the mini matrix
        if(!(P.row[r] & mask) && !(P.col[c] & mask) && !(P.matrix[r/sqrtN][c/sqrtN] & mask))
        {
            board[r][c] = num;
            P.row[r] ^= mask;
            P.col[c] ^= mask;
            P.matrix[r/sqrtN][c/sqrtN] ^= mask;

            res = res || solve(board,calls,N,idx+1,P);
            if(res) return res;

            board[r][c] = 0;
            P.row[r] ^= mask;
            P.col[c] ^= mask;
            P.matrix[r/sqrtN][c/sqrtN] ^= mask;
        }
    }

    return res;
}

/*=========================
Solve function 
=========================*/
bool Solve(vector<vector<int>> &board, bool validateOrNot = true)   
//the boolean arg "validateOrNot" is for determining whether the validate function is to be called or not    
{
    if(validateOrNot && !validate(board))
    {
        return false;
    }
    
    vector<int> calls;
    int N = board.size();
    checkParameters P(N);
    createCalls(board,N,calls,P);
    return solve(board,calls,N,0,P);
}
