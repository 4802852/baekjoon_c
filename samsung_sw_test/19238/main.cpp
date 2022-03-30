#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>

using namespace std;

#define MAX_N 21
#define MAX_M 401
#define endl '\n'
#define MAX_VAL 987654321

// 손님의 출발위치, 도착위치, 출발-도착 거리 저장
struct CUSTOMER
{
	int sr;
	int sc;
	int er;
	int ec;
	int distance;
};


int N, M, F;
int MAP[MAX_N][MAX_N];
int CUSTOMER_MAP[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int next_distance;
CUSTOMER Customer[MAX_M + 1];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};


// (sr, sc) -> (er, ec) 로 이동하는 가장 최단거리 리턴해주는 함수
int FastestWay(int sr, int sc, int er, int ec)
{
	memset(visited, 0, sizeof(visited));
	queue <tuple<int, int, int>> Q;  // Q: tuple<r 좌표, c 좌표, distance> 저장하는 queue
	Q.push(make_tuple(sr, sc, 0));
	visited[sr][sc] = 1;
	while (Q.empty() == 0)
	{
		int now_r = get<0>(Q.front());
		int now_c = get<1>(Q.front());
		int now_d = get<2>(Q.front());
		Q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];

			if (next_r < 0 || N <= next_r || next_c < 0 || N <= next_c || MAP[next_r][next_c] == 1 || visited[next_r][next_c] == 1) continue;

			if (next_r == er && next_c == ec) return (now_d + 1);

			visited[next_r][next_c] = 1;
			Q.push(make_tuple(next_r, next_c, now_d + 1));
		}
	}
	// 도착할 수 없을 경우 -1 리턴
	return (-1);
}


// 현재 위치에서 가장 가까운 위치에 있는 손님 번호 리턴
int FindNextCustomer(int sr, int sc)
{
	// 현재 위치에 손님 있을 경우, 다음 손님까지의 거리 0, 다음 손님 번호 리턴
	if (CUSTOMER_MAP[sr][sc] != 0)
	{
		next_distance = 0;
		return (CUSTOMER_MAP[sr][sc]);
	}
	next_distance = MAX_VAL;
	memset(visited, 0, sizeof(visited));
	// BFS 탐색을 위한 queue 1개, 같은 거리에 있는 손님들 중 우선순위를 결정하기 위한 priority queue 1개 이용
	queue <tuple<int, int, int>> Q;  // Q: tuple<r 좌표, c 좌표, distance> 저장하는 queue
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Possible;
	Q.push(make_tuple(sr, sc, 0));
	visited[sr][sc] = 1;
	while (Q.empty() == 0)
	{
		int now_r = get<0>(Q.front());
		int now_c = get<1>(Q.front());
		int now_d = get<2>(Q.front());
		Q.pop();

		if (next_distance <= now_d) continue;

		for (int i = 0; i < 4; i++)
		{
			int next_r = now_r + dr[i];
			int next_c = now_c + dc[i];
			
			if (next_r < 0 || N <= next_r || next_c < 0 || N <= next_c || MAP[next_r][next_c] == 1 || visited[next_r][next_c] == 1) continue;
			
			visited[next_r][next_c] = 1;
			if (CUSTOMER_MAP[next_r][next_c] == 0)
			{
				Q.push(make_tuple(next_r, next_c, now_d + 1));
			}
			else
			{
				// 다음 위치에 손님이 있을 경우, 손님 거리를 저장하고, 손님들의 우선순위를 저장하기 위한 우선순위큐에 추가
				next_distance = now_d + 1;
				Possible.push(make_pair(next_r, next_c));
			}
		}
	}

	// 도달 가능한 손님이 없을 경우 -1 리턴, 있을 경우 우선 순위 큐 가장 앞 요소의 손님번호 리턴
	if (Possible.empty() == 0)
	{
		int a = Possible.top().first;
		int b = Possible.top().second;
		return (CUSTOMER_MAP[a][b]);
	}
	else return (-1);
}


void Solve(int sr, int sc)
{
	int cnt = 0;
	while (cnt < M)
	{
		int next_customer = FindNextCustomer(sr, sc);
		if (next_customer == -1 || F < next_distance + Customer[next_customer].distance)
		{
			// 다음 손님에 경로상 이유로 도달할 수 없거나, 손님을 태우고 목적지에 도달하기에 연료가 모자를 경우
			break;
		}
		else
		{
			// 목적지 도달 연료를 계산해주고, 손님 지도에서 손님 삭제, 택시 위치를 손님의 목적지로 갱신
			F = F - next_distance + Customer[next_customer].distance;
			CUSTOMER_MAP[Customer[next_customer].sr][Customer[next_customer].sc] = 0;
			sr = Customer[next_customer].er;
			sc = Customer[next_customer].ec;
		}
		cnt++;
	}
	// 위의 while에서 break로 빠져나왔을 경우 -1 출력, 그렇지 않을 경우 남은 연료량 출력
	if (cnt < M)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << F << endl;
	}
}


int main(int argc, char** argv)
{
	int r, c;
	int ta, tb, tc, td;

    // freopen 주석 처리
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> F;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}

	memset(CUSTOMER_MAP, 0, sizeof(CUSTOMER_MAP));
	cin >> r >> c;
	for (int i = 1; i <= M; i++)
	{
		cin >> ta >> tb >> tc >> td;
		// 손님이 출발지에서 도착지까지 이동하는 최단거리를 계산
		int fd = FastestWay(ta - 1, tb - 1, tc - 1, td - 1);
		if (fd == -1)
		{
			// 손님이 출발지에서 도착지까지 도달할 수 없을 경우 이후 계산은 모두 생략하고 -1 출력
			cout << -1 << endl;
			return 0;
		}
		Customer[i] = { ta - 1, tb - 1, tc - 1, td - 1, fd };
		CUSTOMER_MAP[ta - 1][tb - 1] = i;
	}

	Solve(r - 1, c - 1);

	return 0;
}