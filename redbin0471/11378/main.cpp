#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 2001

int N, M, K, ans;
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

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        int tn;
        cin >> tn;
        for (int j = 0; j < tn; j++) {
            int work;
            cin >> work;
            grid[i].push_back(work);
        }
    }
    // 1번부터 N번 직원까지 일을 1개씩 지정
    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i)) ans++;
    }
    // 1번부터 벌점을 가하면서 일을 지정
    int index = 1;
    int k_index = N + 1;
    // 가할 수 있는 벌점이 0이 되거나 N번 직원까지 모두 탐색이 완료되면 종료
    while (0 < K && index <= N) {
        memset(visited, 0, sizeof(visited));
        grid[k_index] = grid[index];
        if (dfs(k_index)) {
            // index 번째 직원에게 일을 지정할 수 있을 때, index 번째 직원에게 벌점을 가하고 일을 지정
            ans++;
            k_index++;
            K--;
        } else {
            // index 번째 직원에게 일을 지정할 수 없을 때, index + 1 번째 직원 탐색
            index++;
        }
    }
    cout << ans << endl;

    return 0;
}