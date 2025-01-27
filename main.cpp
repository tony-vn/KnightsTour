#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define GRID_MAX_SIZE 8

int isSafe(int y, int x, int grid[][GRID_MAX_SIZE])
{
    return (y < GRID_MAX_SIZE && y >= 0 && x < GRID_MAX_SIZE && x >= 0 && grid[y][x] == -1);
}

int solveKT(int grid[][GRID_MAX_SIZE], int movei, int y, int x)
{
    // moves moving clockwise starting from the top-right quadrant
    int moveX[] = {1,2,2,1,-1,-2,-2,-1};
    int moveY[] = {2,1,-1,-2,-2,-1,1,2};
    if(movei == (GRID_MAX_SIZE*GRID_MAX_SIZE)) // base case i.e. at 64, go return from recursion, print 63 as the last move
        return 1;
    for(int i = 0; i < 8; i++) // loop through different knight moves
    {
        int next_y = y + moveY[i];
        int next_x = x + moveX[i];
        if(isSafe(next_y,next_x,grid)==1)
        {
            grid[next_y][next_x] = movei; // set square as the next move
            if(solveKT(grid, movei+1,next_y,next_x) == 1)
            {
                return 1; // solution reached
            }
            else
            {
                grid[next_y][next_x] = -1; // due to backtracking, revert the square as not the next move
            }
        }
    }
    return 0; // backtrack
}

void solveKTHelper()
{

    int movei = 1;
    srand((unsigned) time(0));
    int grid[GRID_MAX_SIZE][GRID_MAX_SIZE];
    for(int y = 0; y < GRID_MAX_SIZE; y++)
        for(int x = 0; x < GRID_MAX_SIZE; x++)
            grid[y][x] = -1; // unvisited squares initialize to -1
    int x = rand() % GRID_MAX_SIZE, y = rand() % GRID_MAX_SIZE;
    cout << x << " " << y << endl;
    grid[y][x]=0; // initialize first square as 0
    if(solveKT(grid,movei,y,x)==1) // arrays are pass-by reference, hence no explicit pass by reference needed
    {
        for(int y = 0; y < GRID_MAX_SIZE; y++)
        {
            for(int x = 0; x < GRID_MAX_SIZE; x++)
            {
                cout << " ";
                if(grid[y][x] < 9) // double-digit print formatting for single digit move
                    cout << 0;
                cout<< grid[y][x]+1;
            }

            cout << endl;
        }
    }
    else
        cout << "solution does not exit" << endl;
}

int main()
{
    solveKTHelper();
    return 0;
}
