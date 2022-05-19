#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_N 1025

int N, M;
int MAP[MAX_N][MAX_N];
int tree[MAX_N][MAX_N];

void Update(int r, int c, int value) {
    int row = r;
    while (row <= N) {
        int col = c;
        while (col <= N) {
            tree[row][col] += value;
            col = col + (col & -col);
        }
        row = row + (row & -row);
    }
}

int Sum(int r, int c) {
    int res = 0;
    int row = r;
    while (0 < row) {
        int col = c;
        while (0 < col) {
            res += tree[row][col];
            col = col - (col & -col);
        }
        row = row - (row & -row);
    }
    return res;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> MAP[i][j];
            Update(i, j, MAP[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        int w;
        cin >> w;
        if (w == 0) {
            // Update
            int x, y, c;
            cin >> x >> y >> c;
            Update(x, y, c - MAP[x][y]);
            MAP[x][y] = c;
        } else {
            // GetSum
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << Sum(x2, y2) - Sum(x2, y1 - 1) - Sum(x1 - 1, y2) + Sum(x1 - 1, y1 - 1) << endl;
        }
    }

    return 0;
}