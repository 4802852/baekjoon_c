#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 401

int N, P, ans;
int flow[MAX_N][MAX_N];
int cap[MAX_N][MAX_N];
vector<vector<int>> grid(MAX_N);

void edmonds_karp() {
    while (1) {
        queue<int> Q;
        Q.push(1);
        vector<int> parent(N + 1, -1);
        int minflow = 987654321;

        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            for (int next : grid[cur]) {
                if (cap[cur][next] - flow[cur][next] > 0 && parent[next] == -1) {
                    Q.push(next);
                    parent[next] = cur;
                    if (next == 2) break;
                }
            }
        }
        if (parent[2] == -1) break;
        for (int i = 2; i != 1; i = parent[i]) {
            minflow = min(minflow, cap[parent[i]][i] - flow[parent[i]][i]);
        }
        for (int i = 2; i != 1; i = parent[i]) {
            flow[parent[i]][i] += minflow;
            flow[i][parent[i]] -= minflow;
        }
        ans += minflow;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> P;
    int a, b;
    for (int i = 0; i < P; i++) {
        cin >> a >> b;
        grid[a].push_back(b);
        grid[b].push_back(a);
        cap[a][b] = 1;
    }

    edmonds_karp();

    cout << ans << endl;

    return 0;
}