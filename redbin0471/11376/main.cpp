#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 2001

int N, K, ans;
int visited[MAX_N];
int bm[MAX_N];
vector<vector<int>> grid(MAX_N);

int dfs(int now) {
    if (visited[now]) return 0;
    visited[now] = 1;
    for (int next : grid[now]) {
        if (bm[next] == 0 || dfs(bm[next])) {
            bm[next] = now;
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
    for (int i = 1; i <= N; i++) {
        int tn;
        cin >> tn;
        for (int j = 0; j < tn; j++) {
            int work;
            cin >> work;
            grid[i].push_back(work);
            grid[i + 1000].push_back(work);
        }
    }

    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i)) ans++;
        memset(visited, 0, sizeof(visited));
        if (dfs(i + 1000)) ans++;
    }
    cout << ans << endl;

    return 0;
}