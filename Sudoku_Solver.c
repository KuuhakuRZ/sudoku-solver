// Code: necessary libraries
#include <stdio.h>
#include <stdbool.h>

// Code: global variables 
#define N 9
int count = 0; //def count as global scope

// Code: count+1, the number of times the function was called. 

void print(int grid[N][N]){ //print box & sub-box
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("-----------------------\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                printf("| ");
            }
            printf("%d", grid[i][j]);
            if (j != 8) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

bool isValid (int grid[N][N], int row, int col, int k){ //check same num
        for (int i = 0; i < 9; i++) { // 1. fixed col, check row
            if (grid[i][col] == k){
                return false; //same num ruturn false
            }
        }
        for (int j = 0; j < 9; j++){ // 2. fixed row, check cow
            if (grid[row][j] == k){
                return false; //same num ruturn false
            } 
        }
        //reset start point for initial spot of sub-box
        int k_row = (row /3)*3;
        int k_col = (col /3)*3;
        // 3. sub-box check 
        for (int i = k_row; i < (k_row + 3); i++){
            for (int j = k_col; j < (k_col + 3); j++){
                if (grid[i][j] == k){
                    return false; //same num ruturn false
                }
            }

        }
        return true; //no same num return true
    }

bool solveSudoku(int grid[N][N], int row, int col){ //backtracking sorting
    count ++; //times of iteration
    if (col == N){ 
        row += 1;
        col = 0;
    }
    if (row == N){ //all elements checked, return true
        return true;
    }
    if (grid[row][col] != 0){ //not zero skip
        //printf("%i\n",grid[row][col]); debug text
        return solveSudoku(grid, row, (col + 1));
    }
    for (int k = 1; k <= 9; k++){ // try 1-9 num
        if (isValid(grid, row, col, k)){
            grid[row][col] = k;
            if (solveSudoku(grid, row, (col + 1))){ //back tracking point
                //printf("it goes here\n"); debug text
                return true;
            }
            grid[row][col] = 0; //reset go back to k for-loop, recheck the number 
        }
    }
    return false; //if no valid number, return false
    //if main branch is false, it means no sol
}

int main() 
    {
    // This is hard coding to receive the ”grid”
    int grid[N][N] = {
        {0, 2, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 6, 0, 0, 0, 0, 3}, 
        {0, 7, 4, 0, 8, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 3, 0, 0, 2},
        {0, 8, 0, 0, 4, 0, 0, 1, 0}, 
        {6, 0, 0, 5, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 7, 8, 0}, 
        {5, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}};
        printf("The input Sudoku puzzle:\n");
    // ”print” is a function we define to print the ”grid”
        if (solveSudoku(grid, 0, 0)) 
        {
    // If the puzzle is solved then:
        printf("Solution found after %d iterations:\n", count);
        print(grid);
        } 
        else 
        {
        printf("No solution exists.\n");
        }
        return 0;
    }