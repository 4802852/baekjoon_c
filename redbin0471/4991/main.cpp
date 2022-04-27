#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 21
#define MAX_T 11
#define INF (int)1e9

struct INFO {
    int r;
    int c;
    int dist;
};

int R, C, ans, t_num;
char MAP[MAX_N][MAX_N];
int m_visited[MAX_N][MAX_N];  // BFS 탐색할 때 사용하는 visited 배열
INFO Start;
INFO Trash[MAX_T];
int visited[MAX_T];  // DFS 탐색할 때 사용하는 visited 배열
int DistMap[MAX_T][MAX_T];  // DistMap[a][b]: a노드에서 b노드로 가는 간선의 길이(이동 거리)

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

bool MapOut(int r, int c) { return (r < 0 || R <= r || c < 0 || C <= c); }

// s 지점에서 시작하는 bfs 탐색으로 각 지점까지의 거리를 적당한 배열에 저장해준다.
void bfs(int s) {
    memset(m_visited, 0, sizeof(m_visited));
    queue<pair<int, int>> Q;
    if (s == t_num) {
        // s가 t_num일 경우 시작지점에서 출발하는 경우
        Q.push(make_pair(Start.r, Start.c));
        m_visited[Start.r][Start.c] = 1;
    } else {
        Q.push(make_pair(Trash[s].r, Trash[s].c));
        m_visited[Trash[s].r][Trash[s].c] = 1;
    }
    int distance = 0;
    while (Q.empty() == 0) {
        int size = Q.size();
        for (int i = 0; i < size; i++) {
            int nowr = Q.front().first;
            int nowc = Q.front().second;
            Q.pop();
            for (int j = 0; j < 4; j++) {
                int nr = nowr + dr[j];
                int nc = nowc + dc[j];
                if (MapOut(nr, nc) || m_visited[nr][nc] == 1 || MAP[nr][nc] == 'x')
                    continue;
                if (s == t_num) {
					// 시작지점에서 출발하는 경우 Trash 구조체에 저장
                    for (int k = 0; k < t_num; k++) {
                        if (Trash[k].r == nr && Trash[k].c == nc) {
                            Trash[k].dist = distance + 1;
                        }
                    }
                } else {
					// 쓰레기 간의 거리일 경우 DistMap에 저장
                    for (int k = s + 1; k < t_num; k++) {
                        if (Trash[k].r == nr && Trash[k].c == nc) {
                            DistMap[s][k] = distance + 1;
                            DistMap[k][s] = distance + 1;
                        }
                    }
                }
                Q.push(make_pair(nr, nc));
                m_visited[nr][nc] = 1;
            }
        }
        distance++;
    }
}

void dfs(int depth, int now, int total) {
    if (depth == t_num) {
		// 모든 노드를 탐색 완료했을 경우 ans 갱신
        if (total < ans) ans = total;
        return;
    }
	// 가장 최신의 ans보다 total 값이 커질 경우 탐색 중단
    if (ans < total) return;
    for (int i = 0; i < t_num; i++) {
        if (visited[i] == 1) continue;
        visited[i] = 1;
        dfs(depth + 1, i, total + DistMap[now][i]);
        visited[i] = 0;
    }
}

void Solve() {
	// 시작지점에서 각 쓰레기까지의 거리 저장
    bfs(t_num);
    for (int i = 0; i < t_num; i++) {
        if (Trash[i].dist == INF) {
			// 시작 지점에서 쓰레기까지 도달할 수 없는 경우, 해당 쓰레기는 고립되어 있으므로 절대 탐색을 완료할 수 없다.
            return;
        }
    }
	// 각 쓰레기에서 다른 쓰레기까지의 거리 저장
    for (int i = 0; i < t_num; i++) {
        bfs(i);
    }
    for (int i = 0; i < t_num; i++) {
        memset(visited, 0, sizeof(visited));
        visited[i] = 1;
        dfs(1, i, Trash[i].dist);
    }
    return;
}

int main(int argc, char **argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    while (1) {
        memset(MAP, 0, sizeof(MAP));
        memset(Trash, 0, sizeof(Trash));
        ans = INF;
        t_num = 0;

        cin >> C >> R;
        if (R == 0 && C == 0) break;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> MAP[i][j];
                switch (MAP[i][j]) {
                    case 'o':
                        Start = {i, j, 0};
                        break;
                    case '*':
                        Trash[t_num++] = {i, j, INF};
                        break;
                }
            }
        }
        Solve();
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}