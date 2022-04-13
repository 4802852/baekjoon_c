#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int N, K;
vector<vector<int>> board;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };


int max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}


int min(int a, int b)
{
	if (a >= b) return b;
	else return a;
}


// 어항 물고기 수의 최대값과 최소값을 구하여 종료 조건에 부합하는지 검사하는 함수
bool is_end()
{
	int MinVal = 987654321;
	int MaxVal = 0;
	for (int i = 0; i < N; i++)
	{
		MinVal = min(MinVal, board[0][i]);
		MaxVal = max(MaxVal, board[0][i]);
	}
	return ((MaxVal - MinVal) <= K);
}


// 배열된 어항에서 문제의 조건(칸 사이의 차 / 5를 전달)에 맞게 물고기를 이동시키고, 이를 한줄로 재배열하는 함수
void BowlArrange()
{
	// board를 복제한 후, 칸 사이의 차를 계산해줌으로써 물고기의 이동이 동시에 이루어질 수 있도록 진행
	vector<vector<int>> new_board = board;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (board[r][c] == -1) continue;
			for (int i = 0; i < 4; i++)
			{
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 0 || N <= nr || nc < 0 || N <= nc || board[r][c] == -1 || board[nr][nc] <= board[r][c]) continue;
				int val = (board[r][c] - board[nr][nc]) / 5;
				new_board[r][c] -= val;
				new_board[nr][nc] += val;
			}
		}
	}
	// 새로 vector를 만들어 조건에 맞는 순서대로 어항 추가
	vector<int> bowl;
	for (int c = 0; c < N; c++)
	{
		for (int r = 0; r < N; r++)
		{
			if (new_board[r][c] == -1) continue;
			bowl.push_back(new_board[r][c]);
		}
	}
	// board를 초기화하고 첫줄을 어항 배열로 대체
	board = vector<vector<int>>(N, vector<int>(N, -1));
	board[0] = bowl;
}


void Move()
{
	// 1. 물고기 수가 가장 작은 어항 물고기 추가
	int MinVal = 987654321;
	for (int i = 0; i < N; i++)
	{
		MinVal = min(MinVal, board[0][i]);
	}
	for (int i = 0; i < N; i++)
	{
		if (board[0][i] == MinVal) board[0][i]++;
	}
	// 2. 어항 공중부양 이동
	int lr = 1; 
	int lc = 1;
	int sc = 0;
	while (sc + lr + lc <= N)
	{
		for (int r = 0; r < lr; r++)
		{
			for (int c = 0; c < lc; c++)
			{
				board[lc - c][sc + lc + r] = board[r][sc + c];
				board[r][sc + c] = -1;
			}
		}
		sc += lc;
		if (lr == lc) lr++;
		else lc++;
	}
	// 3. 어항 바닥으로 재정렬
	BowlArrange();
	// 4. 어항 반 접어 이동 2회
	lr = 1;
	lc = N / 2;
	sc = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int r = 0; r < lr; r++)
		{
			for (int c = 0; c < lc; c++)
			{
				board[2 * lr - r - 1][2 * lc + sc - c - 1] = board[r][sc + c];
				board[r][sc + c] = -1;
			}
		}
		sc += lc;
		lr *= 2;
		lc /= 2;
	}
	// 5. 어항 바닥으로 재정렬
	BowlArrange();
}


void Solve()
{
	int ans = 0;
	while (!is_end())
	{
		ans++;
		Move();
	}
	cout << ans << endl;
}

int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> K;
	board = vector<vector<int>>(N, vector<int>(N, -1));
	for (int i = 0; i < N; i++)
	{
		cin >> board[0][i];
	}

	Solve();

	return 0;
}