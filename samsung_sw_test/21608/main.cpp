#include<iostream>

using namespace std;

#define endl '\n'
#define MAX_N 21
#define MAX_S 401

struct STUDENT
{
	int bf[4];
};


int N;
int MAP[MAX_N][MAX_N];
STUDENT Student[MAX_S];

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

int score[] = { 0, 1, 10, 100, 1000 };


void AssignStudent(int n)
{
	int ar, ac;
	int bfn = 0;
	int etn = 0;
	for (int r = N; 0 < r; r--)
	{
		for (int c = N; 0 < c; c--)
		{
			if (MAP[r][c] != 0) continue;
			int tmp_bfn = 0;
			int tmp_etn = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 1 || N < nr || nc < 1 || N < nc) continue;
				if (MAP[nr][nc] == 0) 
				{
					tmp_etn++;
					continue;
				}
				for (int j = 0; j < 4; j++)
				{
					if (MAP[nr][nc] == Student[n].bf[j])
					{
						tmp_bfn++;
						break;
					}
				}
			}
			if (tmp_bfn < bfn) continue;
			if (bfn < tmp_bfn)
			{
				bfn = tmp_bfn;
				etn = tmp_etn;
				ar = r;
				ac = c;
			}
			else if (etn <= tmp_etn)
			{
				etn = tmp_etn;
				ar = r;
				ac = c;
			}
		}
	}
	MAP[ar][ac] = n;
}


void CheckCond()
{
	int ans = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int tmp_cnt = 0;
			int now = MAP[r][c];
			for (int i = 0; i < 4; i++)
			{
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 1 || N < nr || nc < 1 || N < nc) continue;
				
				for (int j = 0; j < 4; j++)
				{
					if (MAP[nr][nc] == Student[now].bf[j])
					{
						tmp_cnt++;
						break;
					}
				}
			}
			ans += score[tmp_cnt];
		}
	}
	cout << ans << endl;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N;
	for (int i = 1; i <= N * N; i++)
	{
		int sn;
		cin >> sn;
		for (int j = 0; j < 4; j++)
		{
			cin >> Student[sn].bf[j];
		}
		AssignStudent(sn);
	}
	CheckCond();
	return 0;
}