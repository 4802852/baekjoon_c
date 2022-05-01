#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_N 51
#define INF 987654321

struct Info {
    int r;
    int c;
};

int N, ans = INF;
char MAP[MAX_N][MAX_N];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
Info Door[2];

bool MapOut(int r, int c) {
    return (r < 0 || N <= r || c < 0 || N <= c);
}

void dfs(int r, int c, int dir, int mirror) {
    if (ans <= mirror) return;
    if (MAP[r][c] == '*') {
        return;
    } else if (r == Door[1].r && c == Door[1].c) {
        ans = mirror;
        return;
    } else if (r == Door[0].r && c == Door[0].c) {
        return;
    } else if (MAP[r][c] == '!') {
        MAP[r][c] = '.';
        dfs(r, c, dir, mirror);
        MAP[r][c] = '/';
        dfs(r, c, dir, mirror + 1);
        MAP[r][c] = '|';
        dfs(r, c, dir, mirror + 1);
        MAP[r][c] = '!';
    } else if (MAP[r][c] == '.') {
        if (MapOut(r + dr[dir], c + dc[dir])) return;
        dfs(r + dr[dir], c + dc[dir], dir, mirror);
    } else if (MAP[r][c] == '/') {
        int nd;
        if (dir == 0) {
            nd = 3;
        } else if (dir == 1) {
            nd = 2;
        } else if (dir == 2) {
            nd = 1;
        } else if (dir == 3) {
            nd = 0;
        }
        if (MapOut(r + dr[nd], c + dc[nd])) return;
        dfs(r + dr[nd], c + dc[nd], nd, mirror);
    } else if (MAP[r][c] == '|') {
        int nd;
        if (dir == 0) {
            nd = 1;
        } else if (dir == 1) {
            nd = 0;
        } else if (dir == 2) {
            nd = 3;
        } else if (dir == 3) {
            nd = 2;
        }
        if (MapOut(r + dr[nd], c + dc[nd])) return;
        dfs(r + dr[nd], c + dc[nd], nd, mirror);
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
    for (int i = 0; i < 4; i++) {
        int nr = Door[0].r + dr[i];
        int nc = Door[0].c + dc[i];
        if (MapOut(nr, nc)) continue;
        dfs(nr, nc, i, 0);
    }

    cout << ans << endl;

    return 0;
}