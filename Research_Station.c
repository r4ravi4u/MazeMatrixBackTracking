#include "Functions.h"

void research()	//1 means path, 0 means no path
{
	int maze[row][col] = {
		{ 0, 0, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1, 0, 1 },
	};

	point end_A = { 0, 2 }, end_B = { 1, 7 }, end_C = { 5, 7 };	//rare elements location
	point start;

	int i, j;
	int dA = INT_MAX, dB = INT_MAX, dC = INT_MAX, min_dist = INT_MAX;
	int r = INT_MAX, c = INT_MAX;
	int distA, distB, distC;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (maze[i][j] == 1)
			{
				start.x = i;
				start.y = j;
				dA = bfs(maze, start, end_A);
				if (dA == INT_MAX)
					break;

				dB = bfs(maze, start, end_B);
				if (dB == INT_MAX)
					break;

				dC = bfs(maze, start, end_C);
				if (dC == INT_MAX)
					break;

				if (min_dist > dA + dB + dC)
				{
					min_dist = dA + dB + dC;
					r = i;
					c = j;
					distA = dA;
					distB = dB;
					distC = dC;					
				}
					
			}
		}
	}

	if (r == INT_MAX)
		printf("\n!! No Research station possible in this area !!\n");
	else
	{
		printf("\n Research Station shall be at : {%d, %d}\n", r, c);
		printf("\n Its Distance from Rare Element A {%d, %d} : %d\n", end_A.x, end_A.y, distA);
		printf("\n Its Distance from Rare Element B {%d, %d} : %d\n", end_B.x, end_B.y, distB);
		printf("\n Its Distance from Rare Element C {%d, %d} : %d\n", end_C.x, end_C.y, distC);
		printf("\n Total Distance from Research Station : %d\n", min_dist);
	}
}

int bfs(int maze[row][col], point start, point end)
{
	if (!maze[start.x][start.y] || !maze[end.x][end.y])	//if start or end has 0, hence not possible to track path
		return INT_MAX;

	bool visited[row][col];		//visited array to keep track of cells visited or not
	memset(visited, false, sizeof(visited));

	visited[start.x][start.y] = true;

	qnode *head = NULL, *tail = NULL;	//queue to maintain track of adjacent nodes

	qnode cell ;
	cell.p = start;
	cell.d = 0;	//distance from start to next cell is taken 1 not 2 i.e. start to start is 0 even when cell value is 1

	qpush(&head, &tail, cell);

	int i,r,c;

	while (head != NULL && tail != NULL)	//queue is not empty
	{
		qnode front = *head;
		point p = front.p;

		//in case front is end i.e. we have reached to final destination
		if (p.x == end.x && p.y == end.y)	//for first push it will check whether start = end as well
			return front.d;

		qpop(&head, &tail);	//else check for more adjacent nodes

		//push popped cell's adjacent cells to queue for further check and traversal
		for (i = 0; i < 4; i++)
		{
			r = p.x + rownum[i];
			c = p.y + colnum[i];

			if (isValid(r, c) && maze[r][c] && !visited[r][c])	//row and column shall be valid i.e. >=0 & maze element shall be 1 & it shall not be visited before then only add the cell to the queue
			{
				visited[r][c] = true;
				cell.p.x = r;
				cell.p.y = c;
				cell.d = front.d + 1;

				qpush(&head, &tail, cell);

			}
		}
	}

	return INT_MAX;	//i.e. destination end meeting not possible from start

}

bool isValid(int r, int c)
{
	return (r >= 0 && r < row && c >= 0 && c < col);
}

void qpush(qnode **head, qnode **tail, qnode cell)
{
	struct qnode *temp;
	temp = (struct qnode*)malloc(sizeof(struct qnode));

	if (!temp) //mem full
		return;

	//temp->data = (char *)malloc(strlen(data)*sizeof(char));
	temp->p = cell.p;
	temp->d = cell.d;
	temp->next = NULL;

	if (!(*head) && !(*tail)) //1st element insertion
	{
		*head = *tail = temp;
		temp = NULL;
		return;
	}

	(*tail)->next = temp;
	*tail = temp;
	temp = NULL;
}

void qpop(qnode **head, qnode **tail)
{
	struct qnode *temp;

	if (!(*head))	//empty list
	{
		printf("\nList is empty !!\n\n");
		return;
	}

	temp = *head;
	if (*head == *tail)
		*tail = temp->next;
	*head = temp->next;
	free(temp);
}