#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 10002
#define INF 10000001

int T, n, d, c, a, b, s, anum, atime;
int visited[MAX_N];
vector<pair<int, int>> dependency[MAX_N];

int MaxVal(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

void bfs() {
    for (int i = 1; i <= n; i++) {
        visited[i] = INF;
    }
    queue<int> Q;
    Q.push(c);
    visited[c] = 0;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int i = 0; i < dependency[now].size(); i++) {
            int next = dependency[now][i].first;
            int time = dependency[now][i].second;
            if (visited[now] + time < visited[next]) {
                Q.push(next);
                visited[next] = visited[now] + time;
            }
        }
    }
    anum = 0;
    atime = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i] < INF) {
            anum++;
            atime = MaxVal(atime, visited[i]);
        }
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for (int k = 0; k < T; k++) {
        cin >> n >> d >> c;
        for (int i = 0; i < d; i++) {
            cin >> a >> b >> s;
            dependency[b].push_back(make_pair(a, s));
        }
        bfs();
        cout << anum << ' ' << atime << endl;
        for (int i = 1; i <= n; i++) {
            dependency[i].clear();
        }
    }

    return 0;
}