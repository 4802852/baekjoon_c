#include<iostream>

#define MAX_N 21
#define MAX_M 401

using namespace std;

struct SHARK
{
	int r;
	int c;
	int Dir;
	bool Live;
};

int N, M, K;
int MAP[MAX_N][MAX_N][2];  // MAP[r][c][0]: 상어 번호, MAP[r][c][1]: 냄새의 나이?
int SHARK_DIRECTION[MAX_M][5][4];  // ex) 5번 상어의 방향이 3일때 우선순위: SHARK_DIRECTION[5][3][0] ~ SHARK_DIRECTION[5][3][3]

int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };

SHARK Shark[MAX_M];


// 상어가 움직일때 다음 방향을 리턴해주는 함수
int NextDirection(int n)
{
	int sr = Shark[n].r;
	int sc = Shark[n].c;
	int Dir = Shark[n].Dir;

	int empty = 0;  // 가장 우선 순위가 높은 빈공간 방향 저장
	int mysmell = 0;  // 가장 우선 순위가 높은 자기 냄새 방향 저장

	for (int i = 0; i < 4; i++)
	{
		int d = SHARK_DIRECTION[n][Dir][i];
		int nsr = sr + dr[d];
		int nsc = sc + dc[d];

		if (nsr < 0 || N <= nsr || nsc < 0 || N <= nsc) continue;

		if (empty == 0 && MAP[nsr][nsc][0] == 0)
		{
			// empty가 아직 저장이 되지 않았고, 다음 위치가 빈공간일 때 저장
			empty = d;
		}
		if (mysmell == 0 && MAP[nsr][nsc][0] == n)
		{
			// mysmell이 아직 저장이 되지 않았고, 다음 위치가 자기 냄새일 때 저장
			mysmell = d;
		}
	}
	// 빈 공간으로 이동이 가능하면 빈공간 방향을, 그게 아니라면 자기 냄새 공간 방향을 리턴
	if (empty == 0)
	{
		return (mysmell);
	}
	else
	{
		return (empty);
	}
}


// 상어가 움직이는 방향 및 이동 후 위치를 갱신하는 함수
void SharkMove()
{
	int nDir, nsr, nsc;
	for (int i = M; 0 < i; i--)
	{
		if (Shark[i].Live == false) continue;
		nDir = NextDirection(i);
		nsr = Shark[i].r + dr[nDir];
		nsc = Shark[i].c + dc[nDir];
		Shark[i] = { nsr, nsc, nDir, true };
	}
}


// 상어가 움직인 후 기존 경로 냄새의 발생시간과, 지속시간이 지난 냄새를 제거해주는 함수
void SharkSmell()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (MAP[i][j][0] != 0)
			{
				// 상어의 냄새의 발생 시간을 1 증가시키며, 지속시간이 지났을 경우 냄새 제거
				MAP[i][j][1]++;
				if (MAP[i][j][1] == K)
				{
					MAP[i][j][0] = 0;
					MAP[i][j][1] = 0;
				}
			}
		}
	}
	// 높은 번호의 상어로부터 아래로 탐색하여 동일 칸에 위치하게 되는 높은 번호의 상어들 제거
	for (int i = M; 0 < i; i--)
	{
		if (Shark[i].Live == false) continue;
		int r = Shark[i].r;
		int c = Shark[i].c;
		int out_fish = MAP[r][c][0];
		if (out_fish != 0 && out_fish != i)
		{
			// 상어가 가려는 위치에 다른 번호(높은 번호)의 상어가 있을 경우 해당 상어를 제거
			Shark[out_fish].Live = false;
		}
		MAP[r][c][0] = i;
		MAP[r][c][1] = 0;
	}
}


// 살아있는 상어의 수를 카운트 해주는 함수
int CountLivingShark()
{
	int cnt = 0;
	for (int i = 1; i <= M; i++)
	{
		if (Shark[i].Live == true)
		{
			cnt++;
		}
	}
	return (cnt);
}


void Solve()
{
	int stop = 0;
	int i;
	for (i = 1; i <= 1000; i++)
	{
		SharkMove();
		SharkSmell();
		stop = CountLivingShark();
		// 1번 상어만 살아있을 경우 break
		if (stop == 1) break;
	}
	if (i == 1001)
	{
		i = -1;
	}
	printf("%d\n", i);
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &MAP[i][j][0]);
			if (MAP[i][j][0] != 0)
			{
				Shark[MAP[i][j][0]] = { i, j, 0, true };
			}
		}
	}
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &Shark[i].Dir);
	}
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				scanf("%d", &SHARK_DIRECTION[i][j][k]);
			}
		}
	}
	Solve();
	return 0;
}