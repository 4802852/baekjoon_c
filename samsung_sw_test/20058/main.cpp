#include<iostream>
#include<queue>

using namespace std;

#define endl '\n'
#define MAX_N 65

int N, Q, E;
int MAP[MAX_N][MAX_N];
int tmp_MAP[MAX_N][MAX_N];
int Visited[MAX_N][MAX_N];

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };


// 거듭제곱 계산 함수
int pow(int a, int b)
{
	int ans = 1;
	int z = a;
	while (b != 0)
	{
		if (b % 2 == 1) ans *= z;
		b /= 2;
		z = z * z;
	}
	return ans;
}


// BFS 알고리즘을 이용하여 (r, c) 에서 연결된 덩어리의 크기를 리턴
int BulkSize(int r, int c)
{
	int size, now_r, now_c, next_r, next_c;
	queue <pair<int, int>> Q;
	Q.push(make_pair(r, c));
	Visited[r][c] = 1;
	size = 1;
	while (Q.empty() == 0)
	{
		now_r = Q.front().first;
		now_c = Q.front().second;
		Q.pop();
		for (int i = 0; i < 4; i++)
		{
			next_r = now_r + dr[i];
			next_c = now_c + dc[i];
			if (next_r < 0 || E <= next_r || next_c < 0 || E <= next_c || Visited[next_r][next_c] == 1 || MAP[next_r][next_c] == 0) continue;
			Q.push(make_pair(next_r, next_c));
			Visited[next_r][next_c] = 1;
			size++;
		}
	}
	return size;
}


// MAP의 숫차 총합 리턴해주는 함수
int TotalSize()
{
	int size = 0;
	for (int i = 0; i < E; i++)
	{
		for (int j = 0; j < E; j++)
		{
			size += MAP[i][j];
		}
	}
	return size;
}


// MAP (r, c) 에서 시작하고 크기가 interval인 사각형을 시계방향으로 회전하여 tmp_MAP에 저장
void Rotate(int r, int c, int interval)
{
	for (int i = 0; i < interval; i++)
	{
		for (int j = 0; j < interval; j++)
		{
			tmp_MAP[r + i][c + j] = MAP[r + interval - 1 - j][c + i];
		}
	}
}


void CopyMap()
{
	for (int i = 0; i < E; i++)
	{
		for (int j = 0; j < E; j++)
		{
			tmp_MAP[i][j] = MAP[i][j];
		}
	}
}


// L 단계의 파이어스톰을 MAP에 적용하고 그 결과를 tmp_MAP에 저장
void Firestorm(int L)
{
	if (L == 0)
	{
		CopyMap();
		return;
	}
	int interval = pow(2, L);
	for (int i = 0; i < E; i += interval)
	{
		for (int j = 0; j < E; j += interval)
		{
			Rotate(i, j, interval);
		}
	}
}


// (파이어스톰의 회전작업이 완료된) tmp_MAP을 탐색하여 주변에 얼음이 3칸 이상일 경우 그대로, 그렇지 않을 경우 1을 감소시켜 MAP에 저장
void MeltIce()
{
	int tmp, nr, nc;
	for (int r = 0; r < E; r++)
	{
		for (int c = 0; c < E; c++)
		{
			MAP[r][c] = tmp_MAP[r][c];
			if (tmp_MAP[r][c] != 0)
			{
				tmp = 0;
				for (int k = 0; k < 4; k++)
				{
					nr = r + dr[k];
					nc = c + dc[k];
					if (nr < 0 || E <= nr || nc < 0 || E <= nc || tmp_MAP[nr][nc] == 0) continue;
					tmp++;
				}
				if (tmp < 3)
				{
					MAP[r][c]--;
				}
			}
		}
	}
}


int MaxVal(int a, int b)
{
	if (a > b) return a;
	else return b;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> Q;
	E = pow(2, N);
	for (int i = 0; i < E; i++)
	{
		for (int j = 0; j < E; j++)
		{
			cin >> MAP[i][j];
		}
	}
	// Q번에 걸쳐 L을 입력받아 Firestorm 함수 및 MeltIce 함수 실행
	for (int i = 0; i < Q; i++)
	{
		int L;
		cin >> L;
		Firestorm(L);
		MeltIce();
	}

	int MaxSize = 0;
	for (int r = 0; r < E; r++)
	{
		for (int c = 0; c < E; c++)
		{
			// 현재 위치가 방문되지 않았고, 얼음이 존재한다면 BFS 탐색을 시작한다.
			if (Visited[r][c] == 1 || MAP[r][c] == 0) continue;
			MaxSize = MaxVal(MaxSize, BulkSize(r, c));
		}
	}
	cout << TotalSize() << endl;
	cout << MaxSize << endl;

	return 0;
}