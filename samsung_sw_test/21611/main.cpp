#include<iostream>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_N 50

int N, M;
int MAP[MAX_N][MAX_N];
int ans[4] = { 0, 0, 0, 0 };
int Coord[MAX_N * MAX_N], NextCoord[MAX_N * MAX_N * 2];

int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };


// Coord 배열의 1부터 끝까지 탐색하여 폭발 조건에 부합하는 칸들을 -1로 저장하고, 폭발이 일어났으면 1, 일어나지 않았으면 0 리턴
int Bomb()
{
	int flag = 0;
	int start = 1;
	while (Coord[start] == -1) start++;
	if (Coord[start] == 0) return flag;
	int val_old = Coord[start];
	int val_cnt = 1;
	int val;
	for (int i = start + 1; i < N * N; i++)
	{
		val = Coord[i];
		if (val == -1) continue;
		// 이전 값과 현재 값이 같으면 카운트++
		if (val_old == val) val_cnt++;
		else if (val_old != val && 4 <= val_cnt)
		{
			// 이전 값과 현재 값이 같지 않으면서 카운트가 4 이상이라면 폭발 발생
			flag = 1;
			ans[val_old] += val_cnt;
			// 폭발이 일어난 칸들을 -1로 저장
			int j = 0;
			while (0 < val_cnt)
			{
				j++;
				if (Coord[i - j] == -1) continue;
				Coord[i - j] = -1;
				val_cnt--;
			}
			// 폭발 후 새로 카운트 시작
			val_old = val;
			val_cnt = 1;
		}
		else
		{
			// 이전 값과 현재 값이 같지 않고 카운트가 4 미만이라면 폭발 없이 새로 카운트 시작
			val_old = val;
			val_cnt = 1;
		}
		if (val_old == 0) break;
	}
	return flag;
}


// 블리자드 마법을 수행하고, 폭발 후 구슬이 변화하는 단계까지 수행
void Blizard(int d, int s)
{
	memset(NextCoord, 0, sizeof(NextCoord));
	int r = N / 2;
	int c = N / 2;
	// 상어 위치에서 방향과 속도를 고려하여 구슬 파괴
	while (0 < s)
	{
		r += dr[d];
		c += dc[d];
		int sn = MAP[r][c];
		Coord[sn] = -1;
		s--;
	}
	// 폭발이 일어나지 않을 때까지 폭발 함수 계속 호출
	int flag = 1;
	while (flag != 0) flag = Bomb();
	// 구슬 변화 과정 수행
	int start = 1;
	int j = 1;
	while (Coord[start] == -1) start++;
	if (Coord[start] != 0)
	{
		int val_old = Coord[start];
		int val_cnt = 1;
		int val;
		for (int i = start + 1; i < N * N; i++)
		{
			if (Coord[i] == -1) continue;
			val = Coord[i];
			if (val_old == val) val_cnt++;
			else
			{
				NextCoord[j++] = val_cnt;
				NextCoord[j++] = val_old;
				val_old = val;
				val_cnt = 1;
			}
			if (val_old == 0) break;
		}
	}
	for (int i = 0; i < N * N; i++)
	{
		Coord[i] = NextCoord[i];
	}
}


// MAP을 이동 순서에 따라 번호 매기고, 해당 위치의 구슬값을 Coord 배열의 번호 인덱스에 저장
void MakeStructure()
{
	int r = N / 2;
	int c = N / 2;
	int dr2[] = { 0, 1, 0, -1 };
	int dc2[] = { -1, 0, 1, 0 };
	int step = 1;
	int dir = 0;
	int num = 0;
	Coord[0] = 0;
	while (!(r == 0 && c == 0))
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < step; j++)
			{
				r += dr2[dir];
				c += dc2[dir];

				Coord[++num] = MAP[r][c];
				MAP[r][c] = num;
			}
			dir++;
			if (dir == 4) dir = 0;
		}
		step++;
		if (step == N)
		{
			for (int j = 0; j < step - 1; j++)
			{
				r += dr2[dir];
				c += dc2[dir];

				Coord[++num] = MAP[r][c];
				MAP[r][c] = num;
			}
		}
	}
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
	MakeStructure();
	int d, s;
	for (int i = 0; i < M; i++)
	{
		cin >> d >> s;
		Blizard(d, s);
	}
	cout << ans[1] + ans[2] * 2 + ans[3] * 3 << endl;

	return 0;
}