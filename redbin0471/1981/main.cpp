#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'
#define MAX_N 101
#define INF 987654321

int N, MaxVal = INF, MinVal = 0;
int MAP[MAX_N][MAX_N];
int Visited[MAX_N][MAX_N];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

bool MapOut(int r, int c) {
    return (r < 0 || N <= r || c < 0 || N <= c);
}

// 간격이 mid 값일 때, MAP[0][0]에서 MAP[N - 1][N - 1]까지 이동할 수 있는지 경로를 탐색하는 함수
int bfs(int mid) {
    int start_val = MAP[0][0];
    int end_val = MAP[N - 1][N - 1];
    int low = max(MinVal, max(start_val, end_val) - mid);
    int high = min(MaxVal - mid, min(start_val, end_val));
    for (int i = low; i <= high ; i++) {
        memset(Visited, 0, sizeof(Visited));
        queue<pair<int, int>> Q;
        Q.push(make_pair(0, 0));
        Visited[0][0] = 1;
        while (Q.empty() == 0) {
            int r = Q.front().first;
            int c = Q.front().second;
            Q.pop();
            for (int j = 0; j < 4; j++) {
                int nr = r + dr[j];
                int nc = c + dc[j];
                if (MapOut(nr, nc) || MAP[nr][nc] < i || i + mid < MAP[nr][nc] || Visited[nr][nc] == 1) continue;
                if (nr == N - 1 && nc == N - 1) return 1;
                Visited[nr][nc] = 1;
                Q.push(make_pair(nr, nc));
            }
        }
    }
    return 0;
}

// 이분탐색을 통해 (최대-최소) 값을 구하는 함수
int Solve() {
    int Start = 0;
    int End = MaxVal - MinVal;
    int Mid;

    while (Start <= End) {
        Mid = (Start + End) / 2;
        if (bfs(Mid)) {
            End = Mid - 1;
        } else {
            Start = Mid + 1;
        }
    }
    return End + 1;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
            MaxVal = max(MaxVal, MAP[i][j]);
            MinVal = min(MinVal, MAP[i][j]);
        }
    }

    cout << Solve() << endl;

    return 0;
}