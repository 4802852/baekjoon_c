#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 102
#define INF 987654321

struct INFO {
    int r;
    int c;
};

int N, M;
int ans = INF, n1, n2;
int MAP[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
INFO Info[4];

// visited 배열에 방향을 0을 저장하지 않기 위하여 1~4로 방향을 표시하였다.
int dr[] = {0, 0, 1, 0, -1};
int dc[] = {0, 1, 0, -1, 0};

int MinVal(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

// 맵이 (N + 1) * (M + 1) 사이즈이므로 지도 밖으로 나가는 기준을 정하는데 주의한다.
bool OutMap(int r, int c) {
    return (r < 0 || N < r || c < 0 || M < c);
}

// (sc, sr)로 부터 (er, ec)까지의 경로를 visited 함수에 저장하면서 두 점 사이의 최단거리를 리턴하는 함수
int bfs(int sr, int sc, int er, int ec) {
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> Q;
    Q.push(make_pair(sr, sc));
    visited[sr][sc] = 5;
    int dist = 0;
    while (!Q.empty()) {
        int size = Q.size();
        for (int k = 0; k < size; k++) {
            int r = Q.front().first;
            int c = Q.front().second;
            Q.pop();
            for (int i = 1; i <= 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (OutMap(nr, nc) || 0 < visited[nr][nc]) continue;
                if (nr == er && nc == ec) {
                    visited[nr][nc] = i;
                    return (dist + 1);
                }
                if (MAP[nr][nc] == 1) continue;
                // visited[nr][nc] 에 해당 칸에 도달하는 방향을 저장해준다.
                visited[nr][nc] = i;
                Q.push(make_pair(nr, nc));
            }
        }
        dist++;
    }
    return INF;
}

// 첫번째 bfs 가 끝나고 해당 경로를 MAP에 표시해주는 함수
void DrawRoute(int r, int c) {
    int dir = (visited[r][c] + 1) % 4 + 1;
    while (visited[r][c] != 5) {
        r += dr[dir];
        c += dc[dir];
        MAP[r][c] = 1;
        dir = (visited[r][c] + 1) % 4 + 1;
    }
}

void init() {
    // MAP을 초기화하고 4개의 좌표를 1로 표시
    memset(MAP, 0, sizeof(MAP));
    for (int i = 0; i < 4; i++) {
        MAP[Info[i].r][Info[i].c] = 1;
    }
}

void Solve() {
    init();
    // A 루트의 최단거리를 n1에 저장하고 이 경로를 MAP에 표시
    n1 = bfs(Info[0].r, Info[0].c, Info[1].r, Info[1].c);
    DrawRoute(Info[1].r, Info[1].c);
    // A 루트를 우회하는 B 루트의 최단거리 구하여 이 둘의 합을 ans에 저장
    n2 = bfs(Info[2].r, Info[2].c, Info[3].r, Info[3].c);
    ans = MinVal(ans, n1 + n2);
    // B 루트 먼저 계산 진행하여 ans에 최단 거리의 최소값 저장
    init();
    n1 = bfs(Info[2].r, Info[2].c, Info[3].r, Info[3].c);
    DrawRoute(Info[3].r, Info[3].c);
    n2 = bfs(Info[0].r, Info[0].c, Info[1].r, Info[1].c);
    ans = MinVal(ans, n1 + n2);
    if (INF <= ans) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N >> M;
    int a, b;
    for (int i = 0; i < 4; i++) {
        cin >> a >> b;
        Info[i] = {a, b};
    }
    Solve();

    return 0;
}