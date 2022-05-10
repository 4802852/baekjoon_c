#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 1001
#define INF 1e9
#define nINF 100001

int N;
int M;
int MAP[MAX_N][MAX_N];
int dp[MAX_N][2];

int MinVal(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

void bfs(int a) {
    queue<int> Q;
    Q.push(a);
    dp[a][0] = 0;
    dp[a][1] = 0;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int i = 1; i <= N; i++) {
            if (MAP[now][i] == nINF) continue;
            if (dp[i][0] <= dp[now][0] + MAP[now][i]) continue;
            dp[i][0] = dp[now][0] + MAP[now][i];
            dp[i][1] = now;
            Q.push(i);
        }
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N >> M;
    int a, b, c;
    for (int i = 1; i <= N; i++) {
        dp[i][0] = INF;
        dp[i][1] = -1;
        for (int j = 1; j <= N; j++) {
            MAP[i][j] = nINF;
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        MAP[a][b] = MinVal(MAP[a][b], c);
    }
    cin >> a >> b;
    bfs(a);
    cout << dp[b][0] << endl;
    vector<int> path;
    path.push_back(b);
    while (b != a) {
        b = dp[b][1];
        path.push_back(b);
    }
    cout << path.size() << endl;
    for (int i = path.size() - 1; 0 <= i; i--) {
        cout << path[i] << ' ';
    }
    cout << endl;

    return 0;
}