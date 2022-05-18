#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 500002

// Input
int N, M, S, P;
vector<int> Path[MAX_N];
int Cash[MAX_N];
int Restaurant[MAX_N];
// SCC
int id_arr[MAX_N];
int scc_finished[MAX_N];
stack<int> scc_stack;
int id;
// Disjoint Set
int Parent[MAX_N];
set<int> TPath[MAX_N];
// DP
set<int> ParentsSet;
int dp[MAX_N];

// Disjoint Set 알고리즘을 이용하여 같은 SCC로 묶인 교차로들을 한개의 대표 교차로로 묶어준다.
int Find(int x) {
    if (Parent[x] == x) return x;
    return (Parent[x] = Find(Parent[x]));
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
        Parent[y] = x;
    }
}

// SCC 를 찾는 알고리즘을 이용하여 SCC 끼리 Union 을 해주고 한개의 대표 교차로로 묶어준다.
int dfs(int c) {
    id_arr[c] = ++id;
    scc_stack.push(c);
    int res = id_arr[c];
    for (int next : Path[c]) {
        if (id_arr[next] == 0) {
            res = min(res, dfs(next));
        } else if (!scc_finished[next]) {
            res = min(res, id_arr[next]);
        }
    }
    if (res == id_arr[c]) {
        // 같은 SCC끼리 Union하여 대표 교차로 묶고, 레스토랑의 유무, 현금 보유량도 모두 대표 교차로에 더해준다.
        while (1) {
            int t = scc_stack.top();
            scc_stack.pop();
            scc_finished[t] = 1;
            if (t == c) break;
            if (Restaurant[t]) Restaurant[c] = 1;
            Union(c, t);
            Cash[c] += Cash[t];
        }
        // 대표 교차로 1개를 BFS를 위한 교차로 목록에 추가해준다.
        ParentsSet.insert(c);
    }
    return res;
}

int Solve() {
    // Union-Find 를 위한 배열 초기화
    for (int i = 1; i <= N; i++) {
        Parent[i] = i;
    }
    // SCC 탐색하여 같은 SCC 끼리 Union 하면서 레스토랑의 유무, 현금 보유량도 대표 교차로에 추가
    for (int i = 1; i <= N; i++) {
        if (id_arr[i] == 0) dfs(i);
    }
    // 유니언한 교차로들을 대표 교차로로 묶은 후, 중복되는 도로를 제거
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < Path[i].size(); j++) {
            int a = Find(i);
            int b = Find(Path[i][j]);
            if (a != b && !TPath[a].count(b)) {
                TPath[a].insert(b);
            }
        }
    }
    // BFS를 진행하면서 최대 현금 인출량 체크
    int ans = 0;
    S = Find(S);
    queue<int> Q;
    Q.push(S);
    dp[S] = Cash[S];
    if (Restaurant[Find(S)]) ans = dp[Find(S)];
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int next : TPath[now]) {
            // 현재 위치에서 갈 수 있는 다음 위치 중, 현재 dp 현금 보유량 + 다음 ATM 현금 보유량 > 다음 dp 현금 보유량 일때만 탐색을 진행한다.
            if (dp[next] < dp[now] + Cash[next]) {
                dp[next] = dp[now] + Cash[next];
                // 다음 위치에 레스토랑이 있으면 ans의 최대값을 갱신한다
                if (Restaurant[next]) ans = max(ans, dp[next]);
                Q.push(next);
            }
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        Path[a].push_back(b);
    }
    for (int i = 1; i <= N; i++) {
        cin >> Cash[i];
    }
    cin >> S >> P;
    for (int i = 0; i < P; i++) {
        cin >> a;
        Restaurant[a] = 1;
    }

    cout << Solve() << endl;

    return 0;
}