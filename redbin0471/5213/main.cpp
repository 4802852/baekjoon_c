#include <cstring>
#include <deque>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 501

struct BLOCK {
    int a;
    int b;
};

int N;
BLOCK Block[MAX_N * MAX_N];
int prior_Block[MAX_N * MAX_N];  // n번 블록의 이전 경로 블록의 숫자를 저장해주는 배열

int dn[6];  // 오른쪽 위 방향을 0으로 시작하여 시계방향으로 index

// n번 블록에서 d번 방향으로 이동이 가능한지를 판단하는 함수
bool isPossilble(int n, int d) {
    // 블록 범위 바깥으로 나가면 false
    int nn = n + dn[d];
    if (nn < 0 || (int)(N * N - N / 2) <= nn) return false;
    // 벽에서 이동이 제한되는 방향 false
    int tn = n % (2 * N - 1);
    if (tn == 0 && 3 <= d) return false;
    if (tn == N - 1 && d < 3) return false;
    if (tn == N && d == 4) return false;
    if (tn == 2 * N - 2 && d == 1) return false;
    // 블록과 블록의 숫자가 일치하는지 확인하여 true
    if (d < 3 && Block[n].b == Block[nn].a) return true;
    if (3 <= d && Block[n].a == Block[nn].b) return true;
    return false;
}

void Solve() {
    memset(prior_Block, -1, sizeof(prior_Block));
    queue<int> Q;
    Q.push(0);
    prior_Block[0] = 0;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int i = 0; i < 6; i++) {
            int nn = now + dn[i];
            // 이전에 갔던 위치이거나 연결되지 않았으면 continue
            if (prior_Block[nn] != -1 || !isPossilble(now, i)) continue;
            Q.push(nn);
            prior_Block[nn] = now;
        }
    }
    // 맨 아랫줄 맨 오른쪽 블럭 혹은 번호가 가장 큰 블럭을 num에 저장
    int num;
    for (int i = (int)(N * N - N / 2) - 1; 0 <= i; i--) {
        if (prior_Block[i] == -1) continue;
        num = i;
        break;
    }
    // num부터 시작하여 경로를 따라가며 path 큐에 저장
    int val = 1;
    deque<int> path = {num + 1};
    while (num != 0) {
        num = prior_Block[num];
        path.push_front(num + 1);
        val++;
    }
    cout << val << endl;
    for (int i = 0; i < val; i++) {
        cout << path[i] << ' ';
    }
    cout << endl;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < (int)(N * N - N / 2); i++) {
        int a, b;
        cin >> a >> b;
        Block[i] = {a, b};
    }
    dn[0] = -N + 1;
    dn[1] = 1;
    dn[2] = N;
    dn[3] = N - 1;
    dn[4] = -1;
    dn[5] = -N;

    Solve();

    return 0;
}