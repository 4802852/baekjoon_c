#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 801
#define out 400

int N, P, ans;
int flow[MAX_N][MAX_N];
int cap[MAX_N][MAX_N];
vector<int> grid[MAX_N];

void edmond_karp() {
    while (1) {
        queue<int> Q;
        Q.push(1);
        int parent[MAX_N];
        fill(parent, parent + MAX_N, -1);
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
        for (int i = 2; i != 401; i = parent[i]) {
            minflow = min(minflow, cap[parent[i]][i] - flow[parent[i]][i]);
        }
        for (int i = 2; i != 401; i = parent[i]) {
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
    // 마을 내부를 in 정점(i) 와 out 정점(i + out) 으로 나누어 두 정점 사이의 cap을 1로 지정한다.
    for (int i = 1; i <= N; i++) {
        grid[i].push_back(i + out);
        grid[i + out].push_back(i);
        cap[i][i + out] = 1;
    }
    // 입력 받은 마을 사이의 관계를 in 정점과 out 정점으로 나누어 서로 연결해준다.
    int from, to;
    for (int i = 0; i < P; i++) {
        cin >> from >> to;
        grid[from + out].push_back(to);
        grid[to].push_back(from + out);
        cap[from + out][to] = 1;
        grid[to + out].push_back(from);
        grid[from].push_back(to + out);
        cap[to + out][from] = 1;
    }
    edmond_karp();
    cout << ans << endl;

    return 0;
}