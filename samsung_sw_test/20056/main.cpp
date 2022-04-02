#include<iostream>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_N 51
#define MAX_M 2501

int N, M, K;
int MAP[MAX_N][MAX_N][6];  // [ total, even, odd, mass, speed, direction ]
int C_MAP[MAX_N][MAX_N][6];  // 이동 후의 상태를 임시로 저장하는 MAP과 동일한 배열

int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };


// 이동 후의 상태를 임시로 저장하는 C_MAP의 정보를 MAP으로 옮기고, C_MAP을 초기화
void CopyMap()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				MAP[i][j][k] = C_MAP[i][j][k];
			}
		}
	}
	memset(C_MAP, 0, sizeof(C_MAP));
}


void MoveFireballs()
{
	int nr, nc, m, s, d;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (MAP[r][c][0] == 0) continue;
			if (MAP[r][c][0] == 1)
			{
				// 현재 위치의 파이어볼의 수가 1개일 때
				s = MAP[r][c][4];
				d = MAP[r][c][5];
				nr = r + s * dr[d];
				nc = c + s * dc[d];
				nr %= N;
				nc %= N;
				if (nr < 0) nr += N;
				if (nc < 0) nc += N;

				// 다음 위치의 파이어볼 수++
				C_MAP[nr][nc][0]++;
				// 방향의 홀수/짝수에 따라 카운트수++
				if (d % 2 == 1)
				{
					C_MAP[nr][nc][2]++;
				}
				else
				{
					C_MAP[nr][nc][1]++;
				}
				// 다음 위치 파이어볼들의 질량 및 속도 합산
				C_MAP[nr][nc][3] += MAP[r][c][3];
				C_MAP[nr][nc][4] += s;
				C_MAP[nr][nc][5] = d;
			}
			else
			{
				// 현재 위치의 파이어볼 수가 여러개일 때
				m = MAP[r][c][3] / 5;
				if (m == 0) continue;  // 5로 나눈 질량이 0이라면 소멸
				s = MAP[r][c][4] / MAP[r][c][0];
				// 현재 칸에 모인 파이어볼들의 방향이 짝수방향 혹은 홀수방향으로 통일되었다면 0,2,4,8, 아니라면 1,3,5,7
				if (MAP[r][c][0] == MAP[r][c][1] || MAP[r][c][0] == MAP[r][c][2]) d = 0;
				else d = 1;
				while (d < 8)
				{
					// 조건에 맞는 질량 및 속도, 방향으로 이동하도록 계산
					nr = r + s * dr[d];
					nc = c + s * dc[d];
					nr %= N;
					nc %= N;
					if (nr < 0) nr += N;
					if (nc < 0) nc += N;

					C_MAP[nr][nc][0]++;
					if (d % 2 == 1)
					{
						C_MAP[nr][nc][2]++;
					}
					else
					{
						C_MAP[nr][nc][1]++;
					}
					C_MAP[nr][nc][3] += m;
					C_MAP[nr][nc][4] += s;
					C_MAP[nr][nc][5] = d;
					d += 2;
				}
			}
		}
	}
}


void PrintMass()
{
	int mass = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (MAP[i][j][0] == 0) continue;
			if (MAP[i][j][0] == 1)
			{
				// 현재 칸에 파이어볼이 1개라면 질량을 합산
				mass += MAP[i][j][3];
			}
			else
			{
				// 현재 칸에 파이어볼이 여러개라면 조건에 따라 4개로 나뉜 뒤의 질량을 합산
				int tmp = MAP[i][j][3] / 5;
				mass += tmp * 4;
			}
		}
	}
	cout << mass << endl;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	// freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		MAP[r - 1][c - 1][0] = 1;
		MAP[r - 1][c - 1][3] = m;
		MAP[r - 1][c - 1][4] = s;
		MAP[r - 1][c - 1][5] = d;
	}
	
	for (int i = 0; i < K; i++)
	{
		MoveFireballs();
		CopyMap();
	}

	PrintMass();

	return 0;
}