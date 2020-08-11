#include"game.h"
using namespace std;

/*=====================================================================================
This function generates the number of blocks that will be filled in the original sudoku 
=====================================================================================*/
int totalFilledBlocks(int N)
{
    int sqrtN = sqrt(N);
    N *= sqrtN;
    srand(time(0));
    N += rand()%10;
    return N;
}

/*==============================================================
                        WELCOME
==============================================================*/
void welcome()
{   
    cout<<"\n\n";
    cout<<"=======================================WELCOME TO=============================================";
    cout<<"\n                                         SUDOKU";
    cout<<"\n\n                                        1. 9 X 9";
    cout<<"\n                                       2. 16 X 16";
   
    char c;
    while(true){
        cout<<"\nChoose a SUDOKU by entering 1 or 2: ";
        cin>>c;
        if(c == '1' || c == '2')
            break;
        else
            cout<<"\nWrong choice! Input again.\n";
    }

    int N;
    if(c == '1')    N = 9;
    else if(c == '2') N = 16;
    
    //creating the board(sudoku) and initializing it with 0 which represents empty blocks
    vector<vector<int>> board(N,vector<int>(N,0));

    //number of blocks that are empty in sudoku (count of number of zeros)
    int emptyBlocks = N*N - totalFilledBlocks(N);

    //generates and displays SUDOKU
    if(generateSudoku(N,emptyBlocks,board))
        display(board);

    //this set is for similar purpose as calls vector used in solver.h
    unordered_set<int> blocksToBeFilled;

    int sqrtN = sqrt(N);

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(!board[i][j])
                blocksToBeFilled.insert(i*N+j);
        }
    }

    //lets play
    playGame(board,N,blocksToBeFilled);
}


int main()
{
    welcome();
    return 0;
}