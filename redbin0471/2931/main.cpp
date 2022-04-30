#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_RC 26

struct Info {
    int r;
    int c;
};

int R, C;
int mr, mc;
char MAP[MAX_RC][MAX_RC];
Info city[2];

// 1: 오른쪽, 2: 아래, 3: 왼쪽, 4: 위
int dr[] = {0, 0, 1, 0, -1};
int dc[] = {0, 1, 0, -1, 0};

// '|': 0, '-': 1, '+': 2, '1': 3, '2': 4, '3': 5, '4': 6
// dirmap1[a][b]: a 형태 통로에 b 방향으로 진입했을 때 나가는 방향
// dirmap2[a]: a 형태 통로에 나가는 방향 표시
int dirmap1[8][5] = {{0, 0, 2, 0, 4}, {0, 1, 0, 3, 0}, {0, 1, 2, 3, 4}, {0, 0, 0, 2, 1}, {0, 0, 1, 4, 0}, {0, 4, 3, 0, 0}, {0, 2, 0, 0, 3}, {0, 0, 0, 0, 0}};
int dirmap2[8][5] = {{0, 0, 1, 0, 1}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 1}, {0, 1, 1, 0, 0}, {0, 1, 0, 0, 1}, {0, 0, 0, 1, 1}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}};

int ctoi(char a) {
    switch (a) {
        case '|':
            return 0;
        case '-':
            return 1;
        case '+':
            return 2;
        case '1':
            return 3;
        case '2':
            return 4;
        case '3':
            return 5;
        case '4':
            return 6;
    }
    return 7;
}

char itoc(int a) {
    switch (a) {
        case 0:
            return '|';
        case 1:
            return '-';
        case 2:
            return '+';
        case 3:
            return '1';
        case 4:
            return '2';
        case 5:
            return '3';
        case 6:
            return '4';
    }
    return '5';
}

void Solve() {
    // M위치에서 나가는 방향 판단
    mr = city[0].r;
    mc = city[0].c;
    int dir = 5;
    for (int i = 1; i <= 4; i++) {
        int nr = mr + dr[i];
        int nc = mc + dc[i];
        if (nr < 0 || R <= nr || nc < 0 || C <= nc || MAP[nr][nc] == '.' || MAP[nr][nc] == 'Z') continue;
        dir = i;
    }
    // 끊어지는 위치, 즉 수로를 따라가다가 '.'이 나타나는 위치까지 이동
    while (1) {
        mr += dr[dir];
        mc += dc[dir];
        if (MAP[mr][mc] == '.') break;
        dir = dirmap1[ctoi(MAP[mr][mc])][dir];
    }
    cout << mr + 1 << ' ' << mc + 1 << ' ';
    // 끊어진 위치에서 상하좌우 탐색하여 수로가 이어진 방향 탐색
    int next_dir[5] = {0, 0, 0, 0, 0};
    for (int i = 1; i <= 4; i++) {
        int nr = mr + dr[i];
        int nc = mc + dc[i];
        if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
        if (dirmap1[ctoi(MAP[nr][nc])][i] != 0) {
            next_dir[i] = 1;
        }
    }
    // 수로가 이어진 방향들에 해당하는 수로 형태 탐색
    int ans;
    for (int i = 0; i < 7; i++) {
        int flag = 1;
        for (int j = 1; j <= 4; j++) {
            int a = 0, b = 0;
            if (dirmap2[i][j]) a = 1;
            if (next_dir[j]) b = 1;
            if (a ^ b) flag = 0;
        }
        if (flag) {
            ans = i;
            break;
        };
    }
    cout << itoc(ans) << endl;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> MAP[i][j];
            switch (MAP[i][j]) {
                case 'M':
                    city[0].r = i;
                    city[0].c = j;
                    break;
                case 'Z':
                    city[1].r = i;
                    city[1].c = j;
                    break;
            }
        }
    }
    Solve();
    return 0;
}