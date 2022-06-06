#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 501

int N, K, ans;
int visited[MAX_N];
int bm[MAX_N];
vector<vector<int>> grid(501);

int dfs(int row) {
    if (visited[row]) return 0;
    visited[row] = 1;
    for (int col : grid[row]) {
        if (bm[col] == 0 || dfs(bm[col])) {
            bm[col] = row;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    int a, b;
    for (int i = 0; i < K; i++) {
        cin >> a >> b;
        grid[a].push_back(b);
    }
    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i)) ans++;
    }

    cout << ans << endl;

    return 0;
}