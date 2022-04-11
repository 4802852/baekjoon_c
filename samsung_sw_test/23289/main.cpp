#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

#define endl '\n'
#define MAX_N 21

struct HEATER
{
	int r;
	int c;
	int d;
};

int N, M, K, W;
int MAP[MAX_N][MAX_N] = {};
int pre_MAP[MAX_N][MAX_N] = {};
int ans = 0;
int ThermoNum = 0;
pair<int, int> Thermo[MAX_N * MAX_N];
int HeaterNum = 0;
HEATER Heater[MAX_N * MAX_N];
// Wall 배열: (r, c) 위치에서 1, 2, 3, 4에 해당하는 방향에 벽의 유무를 표시, 1은 벽이 있음, 0은 벽이 없음.
int Wall[MAX_N][MAX_N][5] = {};

int dr[] = { 0, 0, 0, -1, 1 };
int dc[] = { 0, 1, -1, 0, 0 };


// n번 온풍기가 바람을 한번 불었을 때의 결과를 pre_MAP에 더해주는 함수
void HeaterWind(int n)
{
	queue<pair<int, int>> Q;
	int hr = Heater[n].r;
	int hc = Heater[n].c;
	int hd = Heater[n].d;
	int temp = 5;
	if (hd == 1 || hd == 2)
	{
		// 온풍기의 방향이 좌우 방향일 때
		Q.push(make_pair(hr + dr[hd], hc + dc[hd]));
		while (Q.empty() == 0 && 0 < temp)
		{
			int length = Q.size();
			for (int i = 0; i < length; i++)
			{
				int now_r = Q.front().first;
				int now_c = Q.front().second;
				Q.pop();
				MAP[now_r][now_c] = temp;
				// 현재 위치에서 온풍이 퍼질 수 있는 3방향에 대하여 벽에 가로막혀 있지 않다면 큐에 추가
				if (0 < now_c + dc[hd] && now_c + dc[hd] <= M)
				{
					if (0 < now_r - 1 && Wall[now_r][now_c][3] == 0 && Wall[now_r - 1][now_c][hd] == 0) Q.push(make_pair(now_r - 1, now_c + dc[hd]));
					if (Wall[now_r][now_c][hd] == 0) Q.push(make_pair(now_r, now_c + dc[hd]));
					if (now_r + 1 <= N && Wall[now_r][now_c][4] == 0 && Wall[now_r + 1][now_c][hd] == 0) Q.push(make_pair(now_r + 1, now_c + dc[hd]));
				}
			}
			temp--;
		}
	}
	else if (hd == 3 || hd == 4)
	{
		// 방향 제외 동일 메커니즘
		Q.push(make_pair(hr + dr[hd], hc + dc[hd]));
		while (Q.empty() == 0 && 0 < temp)
		{
			int length = Q.size();
			for (int i = 0; i < length; i++)
			{
				int now_r = Q.front().first;
				int now_c = Q.front().second;
				Q.pop();
				MAP[now_r][now_c] = temp;
				if (0 < now_r + dr[hd] && now_r + dr[hd] <= N)
				{
					if (0 < now_c - 1 && Wall[now_r][now_c][2] == 0 && Wall[now_r][now_c - 1][hd] == 0) Q.push(make_pair(now_r + dr[hd], now_c - 1));
					if (Wall[now_r][now_c][hd] == 0) Q.push(make_pair(now_r + dr[hd], now_c));
					if (now_c + 1 <= M && Wall[now_r][now_c][1] == 0 && Wall[now_r][now_c + 1][hd] == 0) Q.push(make_pair(now_r + dr[hd], now_c + 1));
				}
			}
			temp--;
		}
	}
	// 온풍기에서 나온 온도를 pre_MAP에 갱신해주고 초기화
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			pre_MAP[i][j] += MAP[i][j];
		}
	}
	memset(MAP, 0, sizeof(MAP));
}


// 과정 1회 진행하는 함수, 온도 측정 결과 추가 진행해야 할 경우 1 리턴, 정상 종료될 경우 0 리턴
int Process()
{
	// 이전 단계에서 최종 버전인 MAP을 pre_MAP으로 복제
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			pre_MAP[i][j] = MAP[i][j];
		}
	}
	memset(MAP, 0, sizeof(MAP));
	// Heater의 갯수만큼 온풍기 함수 호출
	for (int i = 0; i < HeaterNum; i++) HeaterWind(i);
	// 온도 조절 과정 진행
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			int the_val = pre_MAP[r][c];
			if (the_val == 0) continue;
			for (int i = 1; i <= 4; i++)
			{
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr < 1 || N < nr || nc < 1 || M < nc || Wall[r][c][i] == 1 || pre_MAP[r][c] <= pre_MAP[nr][nc]) continue;
				int trans = (pre_MAP[r][c] - pre_MAP[nr][nc]) / 4;
				MAP[nr][nc] += trans;
				the_val -= trans;
			}
			MAP[r][c] += the_val;
		}
	}
	// 가장자리 온도 감소 과정
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (r != 1 && r != N && c != 1 && c != M) continue;
			if (MAP[r][c] == 0) continue;
			MAP[r][c]--;
		}
	}
	ans++;  // 초콜렛 섭취
	// 온도 측정하여 모든 온도계에서 K값 이상의 온도라면 0 리턴하고 종료, 그렇지 않다면 1 리턴
	for (int i = 0; i < ThermoNum; i++)
	{
		int td = Thermo[i].first;
		int tc = Thermo[i].second;
		if (MAP[td][tc] < K)
		{
			return 1;
		}
	}
	return 0;
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
			int val;
			cin >> val;
			if (val == 0) continue;
			else if (val == 5)
			{
				Thermo[ThermoNum].first = i;
				Thermo[ThermoNum].second = j;
				ThermoNum++;
			}
			else
			{
				Heater[HeaterNum] = { i, j, val };
				HeaterNum++;
			}
			
		}
	}
	cin >> W;
	for (int i = 0; i < W; i++)
	{
		int x, y, t;
		cin >> x >> y >> t;
		if (t == 0)
		{
			Wall[x][y][3] = 1;
			Wall[x - 1][y][4] = 1;
		}
		else
		{
			Wall[x][y][1] = 1;
			Wall[x][y + 1][2] = 1;
		}
	}

	int flag = 1;
	while (flag)
	{
		flag = Process();
		if  (100 < ans) break;
	}
	cout << ans << endl;

	return 0;
}