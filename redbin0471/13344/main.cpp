#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 50001

int N, M;
int K, L;
char symbol;
int parent[MAX_N];
int inDegree[MAX_N];
vector<pair<int, int>> Graph;
set<int> GraphSet[MAX_N];
set<int> ParentsSet;

int Find(int x) {
    if (parent[x] == x) return x;
    return (parent[x] = Find(parent[x]));
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
        parent[y] = x;
    }
}

int TopologySort() {
    queue<int> Q;
    for (int i : ParentsSet) {
        if (inDegree[i] == 0) Q.push(i);
    }
    for (int i = 0; i < ParentsSet.size(); i++) {
        if (Q.empty()) {
            return 0;
        }
        int x = Q.front();
        Q.pop();
        for (int j : GraphSet[x]) {
            if (--inDegree[j] == 0) {
                Q.push(j);
            }
        }
    }
    return 1;
}

int Solve() {
    // 위상 정렬을 위해 같은 순위의 선수들을 모두 같은 순위의 대표 선수(parent[x])로 교체하고 중복 그래프 제거
    for (pair<int, int> Temp : Graph) {
        int a = Find(Temp.first);
        int b = Find(Temp.second);
        // a == b 인 경우: 같은 순위끼리의 선수들 사이에 상하 입력이 주어진 경우 inconsistent
        if (a == b) return 0;
        ParentsSet.insert(a);
        ParentsSet.insert(b);
        if (!GraphSet[a].count(b)) {
            GraphSet[a].insert(b);
            inDegree[b]++;
        }
    }
    // 위상 정렬을 진행하여 정렬이 되면(그래프에 사이클이 없으면) consistent, 아니라면 inconsistent
    if (TopologySort()) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    // Disjoint Set 알고리즘을 위한 parent 배열 초기화
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }
    for (int i = 0; i < M; i++) {
        cin >> K >> symbol >> L;
        if (symbol == '=') {
            // 입력된 두 선수가 동일한 실력일 경우 Union
            Union(K, L);
        } else {
            // 실력에 순서를 갖고 있을 경우 Graph 벡터에 저장
            Graph.push_back(make_pair(K, L));
        }
    }

    if (Solve()) {
        cout << "consistent" << endl;
    } else {
        cout << "inconsistent" << endl;
    }
    return 0;
}