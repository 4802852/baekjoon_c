#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'
#define MAX_N 1001

int N, M;
int MAP[MAX_N][MAX_N];
int vMAP[MAX_N][MAX_N];
int nMAP[MAX_N][MAX_N];
int num = 1;

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

bool MapOut(int r, int c) {
    return (r < 0 || N <= r || c < 0 || M <= c);
}

void bfs(int r, int c) {
    queue<pair<int, int>> Q1, Q2;
    Q1.push(make_pair(r, c));
    Q2.push(make_pair(r, c));
    nMAP[r][c] = num;
    while (!Q1.empty()) {
        int nowr = Q1.front().first;
        int nowc = Q1.front().second;
        Q1.pop();
        for (int i = 0; i < 4; i++) {
            int nr = nowr + dr[i];
            int nc = nowc + dc[i];
            if (MapOut(nr, nc) || MAP[nr][nc] == 1 || nMAP[nr][nc] > 0) continue;
            Q1.push(make_pair(nr, nc));
            Q2.push(make_pair(nr, nc));
            nMAP[nr][nc] = num;
        }
    }
    int n_val = Q2.size();
    while (!Q2.empty()) {
        int r = Q2.front().first;
        int c = Q2.front().second;
        Q2.pop();
        vMAP[r][c] = n_val;
    }
}

void Solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (MAP[i][j] == 1) continue;
            if (nMAP[i][j] > 0) continue;
            bfs(i, j);
            num++;
        }
    }
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (MAP[r][c] == 0) {
                cout << 0;
            } else {
                int val = 1;
                vector<int> tmp;
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (MapOut(nr, nc)) continue;
                    if (find(tmp.begin(), tmp.end(), nMAP[nr][nc]) != tmp.end()) continue;
                    tmp.push_back(nMAP[nr][nc]);
                    val += vMAP[nr][nc];
                }
                cout << val % 10;
            }
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string tmp_input;
        cin >> tmp_input;
        for (int j = 0; j < M; j++) {
            MAP[i][j] = tmp_input[j] - '0';
        }
    }
    Solve();

    return 0;
}