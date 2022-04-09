#include<iostream>

using namespace std;

#define endl '\n'
#define MAX_N 21
#define MAX_S 401

// 학생의 친구를 저장하는 구조체
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


// n번 학생의 적절한 위치를 탐색하여 MAP에 저장하는 함수
void AssignStudent(int n)
{
	int ar, ac;  // n번 학생의 정답 위치 저장
	int bfn = 0;  // (ar, ac)에 n번 학생이 위치했을 때 주변에 있는 친한 친구의 수
	int etn = 0;  // (ar, ac)에 n번 학생이 위치했을 때 주변의 빈 자리 수
	// 가능한 위치 중 행과 열이 가장 작은 위치가 정답 위치가 되므로 가장 큰 수부터 탐색
	for (int r = N; 0 < r; r--)
	{
		for (int c = N; 0 < c; c--)
		{
			if (MAP[r][c] != 0) continue;
			int tmp_bfn = 0;
			int tmp_etn = 0;
			for (int i = 0; i < 4; i++)
			{
				// (r, c) 위치에서 주변의 친한 친구 및 빈자리의 수를 카운트
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
			// 기존 저장된 정답(ar, ac)에서보다 좋은 조건일 경우 갱신
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


// 전체를 탐색하여 학생들의 만족도를 계산하여 출력하는 함수
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