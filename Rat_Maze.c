#include "Functions.h"

typedef struct coordinate
{
	int r;	//row
	int c;	//column
	char dir;	//direction D L R U : Down Left Right Up
}coord;

void rat_maze()
{
	int m[4][4] = {  { 1, 0, 0, 0 },
					 { 1, 1, 0, 1 },
					 { 1, 1, 0, 0 },
					 { 0, 1, 1, 1 } 
					};

	char *path = printPath(m, 4);

}
bool inStack(coord stack[], int top, int r, int c) //true if item present, else return false
{
	while (top >= 0)
	{
		if (stack[top].r == r && stack[top].c == c)
			return true;
		top--;
	}

	return false;
}

bool isOK(int r, int c, int n)
{
	return (r >= 0 && r < n && c >= 0 && c < n);
}

char** printPath(int m[4][4], int n)
{
	if (!m[0][0] || !m[n-1][n-1]) //starting or ending cell is blocked
		return;

	int r, c;
	r = c = 0;

	coord *stack = (coord *)malloc(n*n*sizeof(coord)); //stack for bfs elements
	if (!stack)
		return;

	memset(stack, -1, n*n*sizeof(coord));

	int top = -1;	//stack top

	bool **visited = (bool**)malloc(n*sizeof(bool *));	//visited matrix for the cells which have been traversed
	if (!visited)
		return;

	for (int i = 0; i < n; i++)
	{
		visited[i] = (bool *)malloc(n*sizeof(bool)); 

		if (!visited[i])
		{
			free(visited);
			return;
		}

		memset(&visited[i][0], false, n*sizeof(bool));
	}

	//initialise stack with start matrix co-ordinate : r is row  and c is column 
	stack[++top].r = 0;
	stack[top].c = 0;
	stack[top].dir = '\0';

	char *s = (char *)malloc(n*n*sizeof(char));	//to strong traversal string and print then
	if (!s)
		return;

	memset(s, '\0', n*n*sizeof(char));

	int count = 0;
	while (r < n && c < n) //till we do not reach the final destination
	{
		int flag = 0;
		if (!stack[top].dir)	//pop the element if its the start co-ordinate
		{
			stack[top].r = -1;
			stack[top].c = -1;
			top--;
			visited[0][0] = true;
		}
		
		//find neighbouring elements and if not present already in stack and also not visited yet then push onto stack 1 by 1 
		if (isOK(r-1, c, n) && m[r-1][c] && !visited[r-1][c] && !inStack(stack, top, r-1, c))	//U Up element
		{
			top++;
			stack[top].r = r-1;
			stack[top].c = c;
			stack[top].dir = 'U';
			flag++;
		}
		if (isOK(r, c + 1, n) && m[r][c + 1] && !visited[r][c+1] && !inStack(stack, top, r, c+1))	//R Right element
		{
			top++;
			stack[top].r = r;
			stack[top].c = c + 1;
			stack[top].dir = 'R';
			flag++;
		}
		if (isOK(r, c - 1, n) && m[r][c - 1] && !visited[r][c-1] && !inStack(stack, top, r, c-1))	//L Left element
		{
			top++;
			stack[top].r = r;
			stack[top].c = c - 1;
			stack[top].dir = 'L';
			flag++;
		}
		if (isOK(r + 1, c, n) && m[r + 1][c] && !visited[r + 1][c] && !inStack(stack, top, r + 1, c))	//D Down element
		{
			top++;
			stack[top].r = r+1;
			stack[top].c = c;
			stack[top].dir = 'D';
			flag++;
		}

		if (!flag) //means we need to backtrack as no relevant neighbour to pass thru
		{
			r = stack[top].r;
			c = stack[top].c;
			s[--count] = '\0';
			visited[r][c] = true;
			top--;
		}
		else
		{
			r = stack[top].r;
			c = stack[top].c;
			s[count++] = stack[top].dir;
			visited[r][c] = true;

			memset(&stack[top], -1, sizeof(coord));

			top--;

			if (flag > 1)	//more than 1 relevant neighbours i.e more than 1 path from this cell
			{
				//push 
			}
		}

		if (r == n - 1 && c == n - 1)	//need to print the string
		{
			for (int i = 0; i < count; i++)
				printf("%c", s[i]);

			memset(s, '\0', n*n*sizeof(char));
			count = 0;

			if (top < 0)
				break;

			r = stack[top].r;
			c = stack[top].c;
			s[count++] = stack[top].dir;
			
			//initialising 
			visited[r][c] = false;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (m[i][j] <= 2 && m[i][j] > 0)
						visited[r][c] = 0;
					else if (m[i][j] > 2)
						m[i][j]--;
				}
			}

			top--;

		}
	}

	//free the allocated memory, once all work done
	for (int i = 0; i < n; i++)
	{
		if (visited[i])
			free(visited[i]);
	}

	if (visited)
		free(visited);

	if (stack)
		free(stack);

	if (s)
		free(s);
}