#include "Functions.h"

void spaceship()
{
	int grid[][5] = {
						{ 0, 0, -1, 0, 0 },	/*-1 means spaceship position*/
						{ 0, 2, 1, 2, 0 },
						{ 1, 2, 2, 2, 1 },
						{ 0, 1, 1, 2, 0 },
						{ 0, 2, 2, 2, 0 },
						{ 0, 2, 2, 0, 0 },
						{ 0, 2, 2, 2, 1 },
					}; //a[0] row has spaceship
	
	/*printf("No. of rows : %d\n", sizeof(grid) / sizeof(grid[0]));
	printf("No. of columns : %d", sizeof(grid[0])/sizeof(int));*/

	bool bomb = false;	//bomb can be used only once
	int spaceship = -1;

	int r = sizeof(grid) / sizeof(grid[0]); //no. of rows
	int c = sizeof(grid[0]) / sizeof(int); //no. of columns

	int i = 0, j = -1; //spaceship position grid[i][j]
	
	for (j = 0; j < c; j++)	//for spaceship column
	{
		if (grid[i][j] == -1)
		{
			if (spaceship < 0)
				spaceship = j;
			else
			{
				printf("There are multiple spaceships. Why ??");
				return;
			}
		}
	}
	
	if (spaceship < 0)
	{
		printf("Where is spaceship ?");
		return;
	}

	j = spaceship; //backup restored

	while (i < r-1)
	{
		//Check first for Bomb condition

		if (grid[i + 1][j] == 2 && ((j > 0) ? grid[i + 1][j - 1] == 2 : 1) && ((j < c - 1) ? grid[i + 1][j + 1] == 2 : 1)) //if true means use bomb
		{
			if (bomb) //bomb used already
			{
				printf("!! Dying Now !! \n\n Total coins at this point : %d", grid[i][j] + 1);	//+1 coz spaceship starts from -1
				return;
			}
			//use Bomb for 5x5 matrix above control line (control line means spaceship current row)
			bomb = true; //bomb used

			int k=0, l=0; //for bomb matrix
			//for relative position of column of ship so that usage of bomb can be maximised. If in total left, bomb effect in right or vice versa
			int pos_start = 0, pos_end = 0;	//column start & end position for bomb
			if (j > 1 && j < c - 2)	//both left and right side shall have equal bomb effect
			{
				pos_start = j - 2;
				pos_end = j + 2;
			}
			else if (j <= 1) // right side max effect
			{
				pos_start = 0;
				if (j == 0)
					pos_end = j + 4;
				else
					pos_end = j + 3;
			}
			else //left side max effect
			{
				pos_end = c - 1;
				if (j == c - 1)
					pos_start = j - 4;
				else
					pos_start = j - 3;
			}

			for (k = i + 1; k < r && k <= i + 5; k++) //for row
			{
				for (l = pos_start; l <= pos_end && l < c - 1; l++)
				{
					if (grid[k][l] == 2)	//converting 2 to 0 as per bomb execution
						grid[k][l] = 0;
				}
			}

		}
				
		// check for coin in upcoming row
		if (grid[i + 1][j] == 1)	//stay
		{
			grid[i + 1][j] += grid[i][j];
			i++;
			continue;
		}
		if (j > 0 && grid[i + 1][j - 1] == 1) //move left
		{
			grid[i + 1][j - 1] += grid[i][j];
			i++;
			j--;
			continue;
		}
		if(j < c-1 && grid[i + 1][j + 1] == 1)	//move right
		{
			grid[i + 1][j + 1] += grid[i][j];
			i++;
			j++;
			continue;
		}

		//check for empty in upcoming row for safe position
		if (grid[i + 1][j] == 0)	//stay
		{
			grid[i + 1][j] += grid[i][j];
			i++;
			continue;
		}
		if (j > 0 && grid[i + 1][j - 1] == 0) //move left
		{
			grid[i + 1][j - 1] += grid[i][j];
			i++;
			j--;
			continue;
		}
		if (j < c - 1 && grid[i + 1][j + 1] == 0)	//move right
		{
			grid[i + 1][j + 1] += grid[i][j];
			i++;
			j++;
			continue;
		}

		
	}

	//last row left i.e. topmost row
	if (grid[i + 1][j] == 2 && (j > 0) ? grid[i + 1][j - 1] == 2 : 1 && (j < c - 1) ? grid[i + 1][j + 1] == 2 : 1) //if true means use bomb if not used
	{
		if (!bomb)
		{
			bomb = true;
			printf("!! Game Finished !! \n\n Total coins at this point : %d", grid[i][j] + 1);	//+1 coz spaceship starts from -1
			return;
		}
		printf("!! Dying Now !! \n\n Total coins at this point : %d", grid[i][j] + 1);	//+1 coz spaceship starts from -1
		return;
	}
	if (grid[i + 1][j] == 1 || (j > 0) ? grid[i + 1][j - 1] == 1 : 1 || (j < c - 1) ? grid[i + 1][j + 1] == 1 : 1)
		printf("!! Game Finished !! \n\n Total coins at this point : %d", grid[i][j] + 2);	//+1 coz spaceship starts from -1
	else
		printf("!! Game Finished !! \n\n Total coins at this point : %d", grid[i][j] + 1);	//+1 coz spaceship starts from -1
}