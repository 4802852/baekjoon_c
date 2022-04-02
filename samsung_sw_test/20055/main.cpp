#include<iostream>

using namespace std;

#define endl '\n'

int N, K;
int ARR[201];
int ROBOT[201];
int up, down, cnt;
int i, j, ans;


int main(int argc, char** argv)
{
    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> K;
	for (int k = 0; k < 2 * N; k++)
	{
		cin >> ARR[k];
	}

	up = 0;  // 로봇 올리는 위치
	down = N - 1;  // 로봇 내리는 위치
	ans = 0;  // 컨베이어 이동 횟수
	while (1)
	{
		ans++;
		// 1. 내리는 위치의 로봇을 내리고, 컨베이어를 한칸씩 이동하며, 다시 내리는 위치의 로봇을 내린다.
		ROBOT[down] = 0;
		up--;
		down--;
		if (up == -1) up = 2 * N - 1;
		if (down == -1) down = 2 * N - 1;
		i = up;
		while (i != down)
		{
			i++;
			if (i == 2 * N) i = 0;
		}
		ROBOT[i] = 0;
		// 2. 내리는 위치부터 거꾸로 탐색하여 조건을 만족할 경우 로봇이 한칸 이동하고 내구도를 1 감소
		j = i;
		while (i != up)
		{
			i--;
			if (i == -1) i = 2 * N - 1;
			if (ROBOT[i] == 1 && ROBOT[j] == 0 && 0 < ARR[j])
			{
				ROBOT[i] = 0;
				ROBOT[j] = 1;
				ARR[j]--;
				if (ARR[j] == 0) cnt++;
			}
			j = i;
		}
		// 3. 올리는 위치의 내구도가 1 이상이라면 로봇을 올리고 내구도를 1 감소
		if (0 < ARR[i])
		{
			ROBOT[i] = 1;
			ARR[i]--;
			if (ARR[j] == 0) cnt++;
		}
		// 4. 내구도 0인 칸의 갯수가 K개 이상이라면 break
		if (K <= cnt) break;
	}

	cout << ans << endl;
	return 0;
}