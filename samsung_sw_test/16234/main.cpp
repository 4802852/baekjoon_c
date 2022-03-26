#include<iostream>
#include<queue>

#define MAX_N 50

using namespace std;

int N, L, R;
int matrix[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int ansDay = 0;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };
bool flag = true;

void bfs(int r, int c)
{
	queue<pair<int, int>> Q, Q2;
	Q.push(make_pair(r, c));
	Q2.push(make_pair(r, c));
	visited[r][c] = 1;
	int sum = 0;
	int cnt = 0;

	while (Q.empty() == 0)
	{
		int now_r = Q.front().first;
		int now_c = Q.front().second;
		Q.pop();

		sum = sum + matrix[now_r][now_c];
		cnt++;
		for (int i = 0; i < 4; i++)
		{
			int nr = now_r + dr[i];
			int nc = now_c + dc[i];

			if (nr < 0 || N <= nr || nc < 0 || N <= nc) continue;
			if (visited[nr][nc] == 1) continue;
			if ((L <= abs(matrix[now_r][now_c] - matrix[nr][nc])) && (abs(matrix[now_r][now_c] - matrix[nr][nc]) <= R))
			{
				visited[nr][nc] = 1;
				Q.push(make_pair(nr, nc));
				Q2.push(make_pair(nr, nc));
			}
		}
	}
	int val = sum / cnt;

	while (Q2.empty() == 0)
	{
		int x = Q2.front().first;
		int y = Q2.front().second;
		Q2.pop();
		matrix[x][y] = val;
	}
}

bool can_move(int r, int c)
{
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (nr < 0 || N <= nr || nc < 0 || N <= nc) continue;
		if ((L <= abs(matrix[r][c] - matrix[nr][nc])) && (abs(matrix[r][c] - matrix[nr][nc]) <= R))
		{
			return true;
		}
	}
	return false;
}


int main(int argc, char** argv)
{	
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &N, &L, &R);
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	
	while (flag)
	{
		flag = false;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (!visited[i][j] and can_move(i, j))
				{
					bfs(i, j);
					flag = true;
				}
			}
		}
		if (flag == true)
		{
			ansDay++;
		}
		memset(visited, 0, sizeof(visited));
	}

	printf("%d\n", ansDay);
	return 0;
}