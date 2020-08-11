#include<cstdlib>
#include<time.h>
#include"solver.h"
using namespace std;

/*==============================================================
This function creates and returns a random permutation of 1 to N
==============================================================*/
int* createPerm(int N)
{
	srand(time(0));

    // initializing array
    int *p = new int[N];
    for(int i=0;i<N;i++)
        p[i] = i+1;

    int temp, sIndex;       //sIndex - index that will be swapped
    for(int i = N-1;i>0;i--)
    {
        sIndex = rand()%(i+1);
        temp = p[i];
        p[i] = p[sIndex];
        p[sIndex] = temp;
    }

	return p;
}

/*=================================================================================================================
Generates sudoku, N - length of sudoku, emptyBlocks - the number of blocks in sudoku which will be filled or solved
=================================================================================================================*/
bool generateSudoku(int N, int emptyBlocks,vector<vector<int>> &board)
{
    //a random permutation of 1 to N is generated
    int *perm = createPerm(N);

    //the permutation is placed along the main diagonal of empty board
    for(int i = 0;i<N;i++)
        board[i][i] = perm[i];

    delete[] perm;

    //the board is now solved
    bool res = Solve(board,false);

    //error handling
    if(!res)
    {
        cout<<"Error! Aborting!";
        exit(0);
    }

    //random permutation of 1 to N*N  
    perm = createPerm(N*N);

    //some blocks of the filled sudoku are cleared here (assigned 0)
    int r,c;
    for(int i=0;i<emptyBlocks;i++)
    {
        r = (perm[i]-1)/N;
        c = (perm[i]-1)%N;
        board[r][c] = 0;
    }

    delete [] perm;
    
    return res;
}
