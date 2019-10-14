#include "Functions.h"

/*int rownum[] = { -1, 0, 0, 1 };
int colnum[] = { 0, -1, 1, 0 };*/

void matrix_shortest()	//1 means path, 0 means no path
{
	int maze[row1][col1] = {
		{ 1, 1, 13, 2 },
		{ 1, 5, 5, 1 },
		{ 1, 1, 2, 1 }
	};

	point start = { 1, 1 }, end = { 0, 3 };

	printf("\nShortest Path from {%d, %d} -> {%d, %d} : %d\n", start.x, start.y, end.x, end.y, bfs_matrix(maze, start, end));
	
}

int bfs_matrix(int maze[row1][col1], point start, point end)
{
	bool visited[row1][col1];		//visited array to keep track of cells visited or not
	memset(visited, false, sizeof(visited));

	if (!ifValid(start.x, start.y) || !ifValid(end.x, end.y))
	{
		printf("\nPlease provide correct co-ordinates for start & end\n");
		return 0;
	}
		

	visited[start.x][start.y] = true;

	qnode *head = NULL, *tail = NULL;	//queue to maintain track of adjacent nodes

	qnode cell;
	cell.p = start;
	cell.d = maze[start.x][start.y];	//distance from start to next cell is taken 1 not 2 i.e. start to start is 0 even when cell value is 1

	qpush(&head, &tail, cell);

	int i, j, r, c;

	int min_dist = INT_MAX;

	while (head != NULL && tail != NULL)	//queue is not empty
	{
		qnode front = *head;
		point p = front.p;
		int flag = 0;
		

		//in case front is end i.e. we have reached to final destination
		if (p.x == end.x && p.y == end.y)	//for first push it will check whether start = end as well
		{
			min_dist = min_dist < front.d ? min_dist : front.d;
			for (i = 0; i < row1; i++)
			{
				for (j = 0; j < col1; j++)
				{
					if (!visited[i][j])
					{
						visited[end.x][end.y] = false;
						flag = 1;
						break;
					}
						
				}
				if (flag == 1)
					break;
			}
			if (!flag)
				return min_dist;
		}

	//	if (flag == 1)
	//		continue;
		
		qpop(&head, &tail);	//else check for more adjacent nodes

		//push popped cell's adjacent cells to queue for further check and traversal
		for (i = 0; i < 4; i++)
		{
			r = p.x + rownum[i];
			c = p.y + colnum[i];

			if (ifValid(r, c) && !visited[r][c])	//row and column shall be valid i.e. >=0 & maze element shall be 1 & it shall not be visited before then only add the cell to the queue
			{
				visited[r][c] = true;
				cell.p.x = r;
				cell.p.y = c;
				cell.d = front.d + maze[r][c];

				qpush_sort(&head, &tail, cell);

			}
		}
	}

	//return INT_MAX;	//i.e. destination end meeting not possible from start

}

bool ifValid(int r, int c)
{
	return (r >= 0 && r < row1 && c >= 0 && c < col1);
}

void qpush_sort(qnode **head, qnode **tail, qnode cell)	//pushing in the queue in a sorted order
{
	struct qnode *temp;
	temp = (struct qnode*)malloc(sizeof(struct qnode));

	if (!temp) //mem full
		return;

	temp->p = cell.p;
	temp->d = cell.d;
	temp->next = NULL;

	if (!(*head) && !(*tail)) //1st element insertion
	{
		*head = *tail = temp;
		temp = NULL;
		return;
	}

	if (temp->d < (*tail)->d)	//put temp towards head i.e. it came afterwards but needs to be popped before, thus not acting as a proper queue
	{
		struct qnode *temp1;
		temp1 = *head;

		if (temp->d <= temp1->d)
		{
			temp->next = *head;
			*head = temp;
			temp = NULL;
			return;
		}

		while (temp1->next && temp1->next->d < temp->d)
			temp1 = temp1->next;

		temp->next = temp1->next;
		temp1->next = temp;
		temp = NULL;
		return;
	}

	(*tail)->next = temp;
	*tail = temp;
	temp = NULL;
}

/*void qpop(qnode **head, qnode **tail)
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
}*/