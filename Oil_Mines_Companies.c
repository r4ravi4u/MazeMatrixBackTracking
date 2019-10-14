#include "Functions.h"

int diff = INT_MAX;

int MinimumDifference(int n_companies, int* mines, int n_mines, int pos)
{
	
	int mean_val = 0;
	bool flag = false, flag1 = false;

	for (int k = 0; k < n_mines; k++)
		mean_val += mines[k];

	mean_val /= n_companies;

	//int *curr_allocation = (int*)malloc(n_companies * sizeof(int));
	int curr_allocation = 0;

	int max_alloc = 0, min_alloc = 0;

	int j = 0;
	
	for (int i = 0; i < n_companies; i++)
	{
		curr_allocation = 0;
		
		if (n_companies == n_mines)
			curr_allocation = mines[i];

		else
		{
			while (j < n_mines && curr_allocation < mean_val)
			{
				if (pos == j && pos != 0 && !flag)
				{
					flag = true;
					break;
				}
				
				curr_allocation += mines[j];
				j++;
				
			}
			if (j < n_mines)
			{
				//if ((curr_allocation - mean_val) > (mean_val - (curr_allocation - mines[j - 1])))
				if ((curr_allocation - mean_val) > mean_val/2)
				{
					curr_allocation = curr_allocation - mines[j - 1];
					j--;
				}
				else if (curr_allocation > mean_val && !flag1 && pos <= j-1)	//for re-iteration as we can get better combination afterwards
				{
					pos = j - 1;
					flag1 = true;	//that break point has already been set for this iteration, no more changes now for this iteration
				}
					
	
			} 
		}

		if (j == n_mines-1)
			curr_allocation += mines[j];

		if (curr_allocation > max_alloc)
			max_alloc = curr_allocation;

		if (i == 0)
			min_alloc = curr_allocation;

		else if (curr_allocation < min_alloc)
			min_alloc = curr_allocation;
		
	}

	diff = diff < max_alloc - min_alloc ? diff : max_alloc - min_alloc;

	if (pos && pos < n_mines && flag1)	//flag1 will be false when no more break point changes.
		MinimumDifference(n_companies, mines, n_mines, pos);

	return diff;

}

void oil_mines()
{
	int n_companies = 0;
	int n_mines = 0;

	printf("\n No. Of companies : ");
	scanf_s("%d", &n_companies);

	if (n_companies < 1)
	{
		printf("Companies can't be less than 1"); // Error
		return;
	}

	printf("\n No. Of oil mines : ");
	scanf_s("%d", &n_mines);

	if (n_mines < n_companies)
	{
		printf("Mines less than Companies"); // Error
		return;
	}

	int *mines = (int*)malloc(n_mines * sizeof(int));

	if (!mines)
	{
		printf("Failed to allocate memory");
		return;
	}

	for (int i = 0; i < n_mines; i++)	//enter values for each mine
	{
		printf("Value of Mine %d : ", i+1);
		scanf_s("%d", &mines[i]);
		if (mines[i] < 1)	//value can't be 0 or less than 0
		{
			printf("Mine Value can't be 0 or Negative"); // Error
			return;
		}
	}

	printf("\n Min Diff = %d\n", MinimumDifference(n_companies, mines, n_mines,0));

	free(mines);

	return;
}