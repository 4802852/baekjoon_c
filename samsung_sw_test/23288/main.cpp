#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_NM 21

int N, M, K;
int r = 1;
int c = 1;
int d = 0;
int MAP[MAX_NM][MAX_NM], qMAP[MAX_NM][MAX_NM];
int Dice[] = { 0, 1, 2, 3, 4, 5, 6 };
int ans = 0;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };


// 주사위가 지도 위에서 움직였을 때 주사위의 상태를 갱신하는 함수
void DiceMove(int d)
{
	int a[8];
	for (int i = 1; i < 7; i++)
	{
		a[i] = Dice[i];
	}
	switch (d)
	{
	case 0:
		Dice[6] = a[3];
		Dice[3] = a[1];
		Dice[1] = a[4];
		Dice[4] = a[6];
		break;
	case 1:
		Dice[6] = a[5];
		Dice[5] = a[1];
		Dice[1] = a[2];
		Dice[2] = a[6];
		break;
	case 2:
		Dice[6] = a[4];
		Dice[4] = a[1];
		Dice[1] = a[3];
		Dice[3] = a[6];
		break;
	case 3:
		Dice[6] = a[2];
		Dice[2] = a[1];
		Dice[1] = a[5];
		Dice[5] = a[6];
		break;
	}
}


// (rr, cc) 위치에서 연속해서 이동할 수 있는 칸의 갯수를 카운트하는 함수
void bfs(int rr, int cc)
{
	int visited[MAX_NM][MAX_NM];
	memset(visited, 0, sizeof(visited));
	int val = MAP[rr][cc];
	int cnt = 1;
	// Q1, Q2 두가지를 이용하며, Q1은 연속하는 칸들을 탐색할 때, Q2는 탐색이 끝난 후 카운트한 수를 qMAP이라는 별도의 배열에 저장할 때 사용한다.
	queue<pair<int, int>> Q1, Q2;
	Q1.push(make_pair(rr, cc));
	Q2.push(make_pair(rr, cc));
	visited[rr][cc] = 1;
	while (Q1.empty() == 0)
	{
		int now_r = Q1.front().first;
		int now_c = Q1.front().second;
		Q1.pop();
		for (int i = 0; i < 4; i++)
		{
			int nr = now_r + dr[i];
			int nc = now_c + dc[i];
			if (nr < 1 || N < nr || nc < 1 || M < nc || MAP[nr][nc] != val || visited[nr][nc] == 1) continue;
			Q1.push(make_pair(nr, nc));
			Q2.push(make_pair(nr, nc));
			visited[nr][nc] = 1;
			cnt++;
		}
	}
	// MAP과 동일한 크기를 가진 qMAP 배열의 위치에 카운트한 수를 저장해줌으로써 같은 위치에서 bfs 탐색을 여러번 하지 않도록 해준다.
	while (Q2.empty() == 0)
	{
		int now_r = Q2.front().first;
		int now_c = Q2.front().second;
		Q2.pop();
		qMAP[now_r][now_c] = cnt;
	}
}


// 주사위가 1회 움직일 때 일어나는 일들 처리하는 함수
void Move()
{
	// 이동하려는 방향이 벽일 경우 반대 방향으로 이동 처리
	int nr = r + dr[d];
	int nc = c + dc[d];
	if (nr < 1 || N < nr || nc < 1 || M < nc)
	{
		d = (d + 2) % 4;
	}
	// 주사위의 이동 및 주사위 변화 계산
	r += dr[d];
	c += dc[d];
	DiceMove(d);
	int A = Dice[6];
	int B = MAP[r][c];
	// qMAP[r][c]가 존재할 경우(이전에 계산했던 위치인 경우) 해당하는 값을 불러오고, 0이라면(이전에 계산하지 않았다면) bfs 탐색을 통해 값을 계산해준다.
	int C = qMAP[r][c];
	if (C == 0)
	{
		bfs(r, c);
		C = qMAP[r][c];
	}
	if (A > B)
	{
		d++;
		if (d == 4) d = 0;
	}
	else if (A < B)
	{
		d--;
		if (d == -1) d = 3;
	}
	ans += B * C;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> MAP[i][j];
		}
	}
	memset(qMAP, 0, sizeof(qMAP));
	for (int i = 0; i < K; i++) Move();
	cout << ans << endl;
	return 0;
}