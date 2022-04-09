#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_N 21
#define MAX_M 6

int N, M;
int MAP[MAX_N][MAX_N], tmp_MAP[MAX_N][MAX_N], visited[MAX_N][MAX_N], tmp_visited[MAX_N][MAX_N];
int Score = 0;
int flag;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };


// MAP을 탐색하여 중력이 작용했을 경우 변화를 계산하는 함수
void Gravity()
{
	for (int c = 1; c <= N; c++)
	{
		int floor = N;
		for (int r = N; 1 <= r; r--)
		{
			if (MAP[r][c] == -2) continue;
			else if (MAP[r][c] == -1)
			{
				floor = r - 1;
			}
			else if (r == floor)
			{
				floor--;
			}
			else
			{
				MAP[floor][c] = MAP[r][c];
				MAP[r][c] = -2;
				floor--;
			}
		}
	}
}


// MAP 배열을 반시계 방향으로 회전하는 함수
void Rotate(int r, int c, int interval)
{
	for (int i = 0; i < interval; i++)
	{
		for (int j = 0; j < interval; j++)
		{
			tmp_MAP[r + i][c + j] = MAP[r + j][c + interval - 1 - i];
		}
	}
	for (int i = 0; i < interval; i++)
	{
		for (int j = 0; j < interval; j++)
		{
			MAP[r + i][c + j] = tmp_MAP[r + i][c + j];
		}
	}
}


// (r, c)의 주변을 탐색하여 블록인지를 리턴해주는 함수
int isBlock(int r, int c)
{
	int block_num = MAP[r][c];
	for (int i = 0; i < 4; i++)
	{
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 1 || N < nr || nc < 1 || N < nc) continue;
		if (MAP[nr][nc] == 0 || MAP[nr][nc] == block_num) return 1;
	}
	return 0;
}


// 가장 큰 블록을 탐색하여 삭제해주는 함수
void DeleteMaximum()
{
	int max_r, max_c;  // 가장 큰 블록의 기준 블록 좌표 저장
	int max_size = 0;  // 가장 큰 블록의 사이즈 저장
	int max_rainbow = 0;  // 가장 큰 블록의 무지개 블록 수 저장
	flag = 0;  // 블록이 존재하지 않을 경우 0, 그렇지 않을 경우 1
	queue<pair<int, int>> Q;
	memset(visited, 0, sizeof(visited));
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] <= 0 || visited[r][c] == 1) continue;
			if (isBlock(r, c) == 0) continue;
			// 기준 블록 (r, c)에서 탐색하여 해당 블록의 사이즈 및 무지개 블록 수 계산
			flag = 1;
			memset(tmp_visited, 0, sizeof(tmp_visited));
			int block_num = MAP[r][c];
			int tmp_size = 0;
			int tmp_rainbow = 0;
			Q.push(make_pair(r, c));
			tmp_visited[r][c] = 1;
			visited[r][c] = 1;
			
			while (Q.empty() == 0)
			{
				int now_r = Q.front().first;
				int now_c = Q.front().second;
				Q.pop();
				if (0 <= MAP[now_r][now_c]) tmp_size++;
				if (MAP[now_r][now_c] == 0) tmp_rainbow++;
				for (int i = 0; i < 4; i++)
				{
					int nr = now_r + dr[i];
					int nc = now_c + dc[i];
					if (nr < 1 || N < nr || nc < 1 || N < nc || tmp_visited[nr][nc] == 1) continue;
					if (MAP[nr][nc] == 0)
					{
						tmp_visited[nr][nc] = 1;
						Q.push(make_pair(nr, nc));
					}
					else if (MAP[nr][nc] == block_num)
					{
						tmp_visited[nr][nc] = 1;
						visited[nr][nc] = 1;
						Q.push(make_pair(nr, nc));
					}
				}
			}
			if (max_size < tmp_size)
			{
				max_r = r;
				max_c = c;
				max_size = tmp_size;
				max_rainbow = tmp_rainbow;
			}
			else if (max_size == tmp_size && max_rainbow <= tmp_rainbow)
			{
				max_r = r;
				max_c = c;
				max_rainbow = tmp_rainbow;
			}
		}
	}
	if (flag == 0) return;  // 블록이 없을 경우 리턴
	// 블록이 있을 경우 가장 큰 블록 삭제
	int block_num = MAP[max_r][max_c];
	memset(visited, 0, sizeof(visited));
	Q.push(make_pair(max_r, max_c));
	visited[max_r][max_c] = 1;
	while (Q.empty() == 0)
	{
		int now_r = Q.front().first;
		int now_c = Q.front().second;
		Q.pop();
		MAP[now_r][now_c] = -2;
		for (int i = 0; i < 4; i++)
		{
			int nr = now_r + dr[i];
			int nc = now_c + dc[i];
			if (nr < 1 || N < nr || nc < 1 || N < nc || visited[nr][nc] == 1) continue;
			if (MAP[nr][nc] == 0 || MAP[nr][nc] == block_num)
			{
				Q.push(make_pair(nr, nc));
				visited[nr][nc] = 1;
			}
		}
	}
	// 삭제된 블록의 제곱수를 점수에 합산
	Score += max_size * max_size;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	while (1)
	{
		DeleteMaximum();
		if (flag == 0) break;
		Gravity();
		Rotate(1, 1, N);
		Gravity();
	}

	cout << Score << endl;

	return 0;
}