#include <iostream>

using namespace std;

#define endl '\n'

struct BLOCK {
    int r;
    int c;
};

char MAP[9][9];
int n_block = 0, ans = 0;

int dr[] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
int dc[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

// Block의 위치를 저장하는 배열, Block[a][b]: a번 이동했을 때 b번 블록의 위치
BLOCK Block[8][65];

bool MapOut(int r, int c) {
    return (r < 0 || 8 <= r || c < 0 || 8 <= c);
}

// (r, c)의 위치와 depth번 이동한 벽의 위치를 비교하여 벽의 위치에 있는지 아닌지를 판단
bool blocked(int r, int c, int depth) {
    for (int i = 0; i < n_block; i++) {
        if (r == Block[depth][i].r && c == Block[depth][i].c) {
            return true;
        }
    }
    return false;
}

void dfs(int r, int c, int depth) {
    if (8 < depth) {
        // 8번 이동하고도 욱제가 살아있다면 체스판 탈출 가능
        ans = 1;
        return;
    }
    if (ans == 1) return;
    // 벽에 맞으면 return
    if (blocked(r, c, depth)) return;
    for (int i = 0; i < 9; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (MapOut(nr, nc)) continue;
        // 다음 위치에 벽이 있다면 continue
        if (blocked(nr, nc, depth)) continue;
        dfs(nr, nc, depth + 1);
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == '#') {
                Block[0][n_block++] = {i, j};
            }
        }
    }
    for (int i = 0; i < n_block; i++) {
        for (int j = 1; j < 8; j++) {
            int nr = Block[0][i].r + j;
            int nc = Block[0][i].c;
            if (MapOut(nr, nc)) {
                nr = -1;
                nc = -1;
            }
            Block[j][i] = {nr, nc};
        }
    }
    dfs(7, 0, 0);

    cout << ans << endl;

    return 0;
}