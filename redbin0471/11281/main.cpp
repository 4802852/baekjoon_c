#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 10001
#define MAX_M 100001

int N, M;
vector<int> Path[MAX_N * 2];
int id, sccNum;
int scc_id[MAX_N * 2];
int scc_finished[MAX_N * 2];
int sn[MAX_N * 2];
stack<int> scc_stack;
vector<vector<int>> SCC;
int ans[MAX_N];
int visited[MAX_N];

int Not(int a) {
    return (N < a ? a - N : a + N);
}

// SCC 알고리즘
int dfs(int c) {
    scc_id[c] = ++id;
    scc_stack.push(c);
    int res = scc_id[c];
    for (int next : Path[c]) {
        if (scc_id[next] == 0) {
            res = min(res, dfs(next));
        } else if (!scc_finished[next]) {
            res = min(res, scc_id[next]);
        }
    }
    if (res == scc_id[c]) {
        vector<int> scc;
        while (1) {
            int t = scc_stack.top();
            scc_stack.pop();
            scc.push_back(t);
            scc_finished[t] = 1;
            // 같은 SCC 끼리는 같은 숫자의 sn[x] 값을 갖게 된다.
            sn[t] = sccNum;
            if (t == c) break;
        }
        SCC.push_back(scc);
        sccNum++;
    }
    return res;
}

// 같은 SCC 에 x 와 ~x 가 동시에 있는지 체크하는 함수
int Check() {
    for (int i = 1; i <= N; i++) {
        if (sn[i] == sn[i + N]) return 0;
    }
    return 1;
}

// 변수들의 true/false 값을 저장하여 출력하는 함수
void PrintX() {
    for (vector<int> Temp : SCC) {
        for (int comp : Temp) {
            if (visited[comp <= N ? comp : Not(comp)]) continue;
            // comp 값이 N보다 크다면 그에 해당하는 순서의 변수를 false로, 그렇지 않다면 true 로 지정
            if (N < comp) {
                ans[Not(comp)] = 0;
                visited[Not(comp)] = 1;
            } else {
                ans[comp] = 1;
                visited[comp] = 1;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
        if (a < 0) a = -a + N;
        if (b < 0) b = -b + N;
        Path[Not(a)].push_back(b);
        Path[Not(b)].push_back(a);
    }
    for (int i = 1; i <= 2 * N; i++) {
        if (scc_id[i] == 0) dfs(i);
    }
    if (Check()) {
        cout << 1 << endl;
        PrintX();
    } else {
        cout << 0 << endl;
    }

    return 0;
}