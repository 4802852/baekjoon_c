#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

#define endl '\n'

int M, S;
// MAP[r][c][0]: (r, c) 칸에 존재하는 물고기의 토탈 수
// MAP[r][c][d]: (r, c) 칸에 존재하는 방향이 d인 물고기의 수
// tmp_MAP 에는 이동 후의 물고기 정보를 저장하고, 이를 MAP에 카피함으로써 물고기 복제 진행
int MAP[5][5][9], tmp_MAP[5][5][9], smell_MAP[5][5];
priority_queue<pair<int, int>> pq;
int sr, sc;  // 상어의 위치

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

int sdr[] = { 0, -1, 0, 1, 0 };
int sdc[] = { 0, 0, -1, 0, 1 };


// (r, c) 위치에서 d의 방향인 물고기가 이동하게 되는 방향을 리턴하는 함수
int PossibleDir(int r, int c, int d)
{
	int origin_d = d;
	int nr = r + dr[d];
	int nc = c + dc[d];
	if (1 <= nr && nr <= 4 && 1 <= nc && nc <= 4 && smell_MAP[nr][nc] == 0 && !(nr == sr && nc == sc)) return d;
	d--;
	if (d == 0) d = 8;
	while (1)
	{
		if (d == origin_d) return 0;
		nr = r + dr[d];
		nc = c + dc[d];
		if (1 <= nr && nr <= 4 && 1 <= nc && nc <= 4 && smell_MAP[nr][nc] == 0 && !(nr == sr && nc == sc)) return d;
		d--;
		if (d == 0) d = 8;
	}
}


// 상어가 가장 많은 물고기를 먹는 경로를 탐색하는 dfs 함수
void dfs(int r, int c, int route, int total)
{
	if (100 <= route)
	{
		pq.push(make_pair(total, -route));
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		int nr = r + sdr[i];
		int nc = c + sdc[i];
		if (nr < 1 || 4 < nr || nc < 1 || 4 < nc) continue;
		int tmp_val = tmp_MAP[nr][nc][0];
		tmp_MAP[nr][nc][0] = 0;
		dfs(nr, nc, 10 * route + i, total + tmp_val);
		tmp_MAP[nr][nc][0] = tmp_val;
	}
}


// 상어의 이동 위치 탐색, 이동 경로에 물고기 삭제 및 물고기 냄새 생성
void MaxSharkEatFish()
{
	// priority queue에 dfs 탐색 결과 값을 (먹은 최대 물고기 수, -경로) 형태로 저장하여, pq.top()에서 먹은 물고기 수와 사전순으로 가장 빠른 경로를 확인
	pq = priority_queue<pair<int, int>>();
	dfs(sr, sc, 0, 0);
	int route = -pq.top().second;
	int mod = 100;
	while (route != 0)
	{
		int d = route / mod;
		route %= mod;
		mod /= 10;
		sr += sdr[d];
		sc += sdc[d];
		if (tmp_MAP[sr][sc][0] == 0) continue;
		for (int i = 0; i <= 8; i++)
		{
			tmp_MAP[sr][sc][i] = 0;
		}
		smell_MAP[sr][sc] = 3;
	}
}


// 물고기 냄새의 수명을 1씩 감소
void SmellFade()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (smell_MAP[i][j] == 0) continue;
			smell_MAP[i][j]--;
		}
	}
}


// 남은 물고기 수를 리턴하는 함수
int TotalFish()
{
	int val = 0;
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{
			val += MAP[r][c][0];
		}
	}
	return val;
}


// 전체적인 1회 싸이클을 진행하는 함수
void Process()
{
	// 이동 후의 상태를 저장할 tmp_MAP을 초기화 하고 물고기 수를 복사
	memset(tmp_MAP, 0, sizeof(tmp_MAP));
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{	
			tmp_MAP[r][c][0] = MAP[r][c][0];
		}
	}
	// 물고기 이동 수행
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{
			if (PossibleDir(r, c, 1) == 0)
			{
				// 현재 위치에서 이동할 수 있는 방향이 없을 경우, 현재 위치의 정보를 그대로 복사
				for (int d = 1; d <= 8; d++)
				{
					tmp_MAP[r][c][d] += MAP[r][c][d];
				}
			}
			else
			{
				for (int d = 1; d <= 8; d++)
				{
					// (r, c) 칸에 있는 각종 방향의 물고기들의 이동 수행
					if (MAP[r][c][d] == 0) continue;
					int nd = PossibleDir(r, c, d);
					int nr = r + dr[nd];
					int nc = c + dc[nd];
					tmp_MAP[nr][nc][nd] += MAP[r][c][d];
					tmp_MAP[r][c][0] -= MAP[r][c][d];
					tmp_MAP[nr][nc][0] += MAP[r][c][d];
				}
			}
		}
	}
	MaxSharkEatFish();  // 상어 이동 수행
	SmellFade();  // 냄새 감소 수행
	// 계산된 tmp_MAP을 MAP에 추가해줌으로써 물고기 복제 과정 완료
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{
			for (int i = 0; i <= 8; i++)
			{
				MAP[r][c][i] += tmp_MAP[r][c][i];
			}
		}
	}
} 


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> M >> S;
	memset(MAP, 0, sizeof(MAP));
	for (int i = 0; i < M; i++)
	{
		int r, c, d;
		cin >> r >> c >> d;
		MAP[r][c][0]++;
		MAP[r][c][d]++;
	}
	cin >> sr >> sc;

	for (int i = 0; i < S; i++)	Process();

	cout << TotalFish() << endl;

	return 0;
}