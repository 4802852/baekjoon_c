#include<iostream>

using namespace std;

#define endl '\n'
#define MAX_N 500

int N;
int MAP[MAX_N][MAX_N];
int out_sand = 0;  // MAP 배열 바깥으로 나가는 모래 저장

// [ r좌표 변화, c좌표 변화, 모래 % ] 좌우 이동, 상하 이동에 따라 각각 배열 제작
double LR[10][3] = { { -1, -1, 0.01 }, { -1, 0, 0.07, }, { -2, 0, 0.02 }, { -1, 1, 0.1 }, { 0, 2, 0.05 }, { 1, -1, 0.01 }, { 1, 0, 0.07 }, { 2, 0, 0.02 }, { 1, 1, 0.1 }, {0, 1, 0} };
double DU[10][3] = { { -1, -1, 0.01 }, { 0, -1, 0.07, }, { 0, -2, 0.02 }, { 1, -1, 0.1 }, { 2, 0, 0.05 }, { -1, 1, 0.01 }, { 0, 1, 0.07 }, { 0, 2, 0.02 }, { 1, 1, 0.1 }, {1, 0, 0} };


// 토네이도 좌우 이동 시 모래 이동 함수, dir가 1일 때 오른쪽, dir가 -1일 때 왼쪽으로 이동
void WindLR(int er, int ec, int dir)
{
	int mr, mc, tmp_sand;
	int to_move = MAP[er][ec];
	int not_moved = to_move;
	MAP[er][ec] = 0;
	for (int i = 0; i < 10; i++)
	{
		mr = er + LR[i][0];
		mc = ec + LR[i][1] * dir;
		if (i == 9)
		{
			// i == 9: 남은 모래를 다음칸(알파칸)으로 이동 시키는 경우
			tmp_sand = not_moved;
		}
		else
		{
			// 남은 모래를 다음칸(알파칸)이 아닌 다른 위치로 이동시키는 경우
			tmp_sand = to_move * LR[i][2];
			not_moved -= tmp_sand;
		}
		if (mr < 0 || N <= mr || mc < 0 || N <= mc)
		{
			// 다음 위치가 배열 바깥으로 나갔을 때 out_sand 갱신
			out_sand += tmp_sand;
		}
		else
		{
			// 다음 위치가 배열 안쪽인 경우 모래양 갱신
			MAP[mr][mc] += tmp_sand;
		}
	}
}


// 토네이도 상하 이동 시 모래 이동 함수, dir가 1일 때 아래쪽, dir가 -1일 때 위쪽으로 이동
void WindDU(int er, int ec, int dir)
{
	int mr, mc, tmp_sand;
	int to_move = MAP[er][ec];
	int not_moved = to_move;
	MAP[er][ec] = 0;
	for (int i = 0; i < 10; i++)
	{
		mr = er + DU[i][0] * dir;
		mc = ec + DU[i][1];
		if (i == 9)
		{
			tmp_sand = not_moved;
		}
		else
		{
			tmp_sand = to_move * DU[i][2];
			not_moved -= tmp_sand;
		}
		if (mr < 0 || N <= mr || mc < 0 || N <= mc)
		{
			out_sand += tmp_sand;
		}
		else
		{
			MAP[mr][mc] += tmp_sand;
		}
	}
}


void Solve()
{
	int r, c;
	r = N / 2;
	c = N / 2;

	int step = 1;
	int z = -1;

	// 토네이도가 왼쪽1, 아래1, 오른쪽2, 위쪽2, 왼쪽3, 아래3...으로 이어지는 규칙성을 이용하여 반복하고, (0,0) 도달시 정지
	while (1)
	{
		for (int i = 1; i <= step; i++)
		{
			c += z;
			WindLR(r, c, z);
			if (r == 0 && c == 0) break;
		}
		if (r == 0 && c == 0) break;
		z *= -1;
		for (int i = 1; i <= step; i++)
		{
			r += z;
			WindDU(r, c, z);
		}
		step += 1;
	}

	cout << out_sand << endl;
}


int main(int argc, char** argv)
{
    // freopen 주석 처리
	// freopen("input.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}

	Solve();

	return 0;
}