#include<iostream>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_N 51

int N, M;
int MAP[MAX_N][MAX_N], CLOUD[MAX_N][MAX_N], tmp_CLOUD[MAX_N][MAX_N];

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };


// 1싸이클의 이동 과정을 처리하는 함수
void Process(int d, int s)
{
	// CLOUD 배열에 저장된 구름 정보와 구름의 방향, 속도를 이용하여 이동 후의 구름을 tmp_CLOUD 배열에 저장
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (CLOUD[r][c] == 0) continue;
			int nr = r + s * dr[d];
			int nc = c + s * dc[d];
			nr %= N;
			nc %= N;
			if (nr < 0) nr += N;
			if (nc < 0) nc += N;
			tmp_CLOUD[nr][nc] = 1;
			// 구름이 이동한 후의 위치에 비를 내려 물의 양 1 증가
			MAP[nr][nc]++;
		}
	}
	memset(CLOUD, 0, sizeof(CLOUD));
	// 비가 내린 위치에서 4방향 대각선을 탐색하여 물이 있을 경우 1씩 증가
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (tmp_CLOUD[r][c] == 1)
			{
				for (int i = 2; i < 9; i += 2)
				{
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (nr < 0 || N <= nr || nc < 0 || N <= nc) continue;
					if (0 < MAP[nr][nc]) MAP[r][c]++;
				}
			}
		}
	}
	// 비가 내리지 않은 곳에 물이 2 이상 있을 경우 구름 생성, CLOUD 배열에 저장
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (tmp_CLOUD[r][c] == 0 && 2 <= MAP[r][c])
			{
				MAP[r][c] -= 2;
				CLOUD[r][c] = 1;
			}
		}
	}
	memset(tmp_CLOUD, 0, sizeof(tmp_CLOUD));
}


// 모든 계산이 끝난 후 전체 물의 양을 계산하는 함수
void PrintTotal()
{
	int ans = 0;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			ans += MAP[r][c];
		}
	}
	cout << ans << endl;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	CLOUD[N - 1][0] = 1;
	CLOUD[N - 1][1] = 1;
	CLOUD[N - 2][0] = 1;
	CLOUD[N - 2][1] = 1;

	int d, s;
	for (int i = 0; i < M; i++)
	{
		cin >> d >> s;
		Process(d, s);
	}
	PrintTotal();

	return 0;
}