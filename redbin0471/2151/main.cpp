#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 51
#define INF 987654321

struct Info {
    int r;
    int c;
};

int N, ans = -1;
char MAP[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
Info Door[2];

bool MapOut(int r, int c) {
    return (r < 0 || N <= r || c < 0 || N <= c);
}

void bfs() {
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> Q;
    Q.push(make_pair(Door[0].r, Door[0].c));
    visited[Door[0].r][Door[0].c] = 1;
    while (Q.empty() == 0) {
        int size = Q.size();
        ans++;
        for (int i = 0; i < size; i++) {
            int r = Q.front().first;
            int c = Q.front().second;
            Q.pop();
            for (int j = 0; j < 4; j++) {
                int dist = 1;
                while (1) {
                    // 처음 위치에서 직선으로 쭉 진행
                    int nr = r + dr[j] * dist;
                    int nc = c + dc[j] * dist;
                    if (MapOut(nr, nc) || MAP[nr][nc] == '*') {
                        // 벽을 만나거나 집 바깥으로 나갈 경우 중단
                        break;
                    } else if (MAP[nr][nc] == '!' && visited[nr][nc] == 0) {
                        // 도달하지 않았던 거울 위치가 나올 경우 큐에 추가
                        Q.push(make_pair(nr, nc));
                        visited[nr][nc] = 1;
                    } else if (MAP[nr][nc] == '#' && visited[nr][nc] == 0) {
                        // 다른 문에 도달할 경우 탐색 종료
                        return;
                    }
                    dist++;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == '#') {
                Door[k++] = {i, j};
            }
        }
    }
    bfs();
    cout << ans << endl;

    return 0;
}