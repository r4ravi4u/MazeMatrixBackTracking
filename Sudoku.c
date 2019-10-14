/*
Given an incomplete Sudoku configuration in terms of a 9x9  2-D square matrix (mat[][]) the task to print a solution of the Sudoku. For simplicity you may assume that there will be only one unique solution.

3 1 6 5 7 8 4 9 2
5 2 9 1 3 4 7 6 8
4 8 7 6 2 9 5 3 1
2 6 3 4 1 5 9 8 7
9 7 4 8 6 3 1 2 5
8 5 1 7 9 2 6 4 3
1 3 8 9 4 7 2 5 6
6 9 2 3 5 1 8 7 4
7 4 5 2 8 6 3 1 9

9x9 matrix

1<=T<=10
0<=mat[]<=9

Backtracking Algorithm Application
*/

#include "Functions.h"
#define ROW 9
#define COL 9

int SolutionDone(int T[ROW][COL], int* i, int* j)
{
	for (*i = 0; *i < ROW; (*i)++)
	{
		for (*j = 0; *j < COL; (*j)++)
		{
			if (!T[*i][*j])
				return 0;
		}
	}
	return 1;
}

int isSafe(int T[ROW][COL], int r, int c, int n)
{
	//r row from column 0 to COL
	for (int j = 0; j < COL; j++)
	{
		if (T[r][j] == n)
			return 0;
	}

	//c column from row 0 to ROW
	for (int i = 0; i < ROW; i++)
	{
		if (T[i][c] == n)
			return 0;
	}

	//same box 3*3 grid
	int row = r - (r % 3);
	int col = c - (c % 3);
	for (int i = row; i <= row + 2; i++)
		for (int j = col; j <= col + 2; j++)
			if (T[i][j] == n)
				return 0;
	
	//if all above cases pass i.e. no return  from them, means its safe to put this n into T[r][c]
	return 1;
}

int SudokuUtil(int T[ROW][COL])
{
	int r, c;
	
	if (SolutionDone(T, &r, &c))	//means no 0 in T now and hence Sudoku has been solved
		return 1;

	//Now here we got row and column where we found 0 in Matrix T
	for (int i = 1; i <= 9;i++)	//since no. can be from 1 to 9
	{
		if (isSafe(T, r, c, i))	//will check if the no. is suitable to put or not and then proceed for next cell to fill up
		{
			T[r][c] = i;

			if (SudokuUtil(T))
				return 1;
					
			T[r][c] = 0;
		}
		
	}

	return 0;	//This is backtracking, in case not found solution 
}

void Sudoku()
{
	FILE *fp = fopen("Test.txt", "r");

	int N;
	fscanf(fp, "%d", &N);
	while (N--)
	{
		int T[ROW][COL];

		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				fscanf(fp, "%d", &T[i][j]);
	
		SudokuUtil(T);
		
		//print Sudoku Solution
		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				printf("%d ", T[i][j]);

		printf("\n");	//For next TC

	}

	fclose(fp);
}