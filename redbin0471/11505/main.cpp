#include <algorithm>
#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_N 1000002
#define MOD 1000000007

int N, M, K;
int NUM[MAX_N];
long long int SegmentTree[MAX_N * 4];

// NUM 배열에 저장된 정보를 가지고 세그먼트 트리를 초기화하는 함수
long long int Init(int start, int end, int node) {
    if (start == end) return SegmentTree[node] = NUM[start];
    int mid = (start + end) / 2;
    return (SegmentTree[node] = (Init(start, mid, node * 2) * Init(mid + 1, end, node * 2 + 1)) % MOD);
}

// left~right 까지 구간의 곱을 구하는 함수
long long int Multiply(int start, int end, int node, int left, int right) {
    if (end < left || right < start) return 1;
    if (left <= start && end <= right) return SegmentTree[node];
    int mid = (start + end) / 2;
    return ((Multiply(start, mid, node * 2, left, right) * Multiply(mid + 1, end, node * 2 + 1, left, right)) % MOD);
}

// index 번째 수를 new_num으로 바꾸는 함수
long long int Update(int start, int end, int node, int index, int new_num) {
    if (index < start || end < index) return SegmentTree[node];
    if (start == end) return SegmentTree[node] = new_num;
    int mid = (start + end) / 2;
    return SegmentTree[node] = (Update(start, mid, node * 2, index, new_num) * Update(mid + 1, end, node * 2 + 1, index, new_num)) % MOD;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> NUM[i];
    }
    Init(1, N, 1);
    int a, b, c;
    for (int i = 0; i < M + K; i++) {
        cin >> a >> b >> c;
        if (a == 1) {
            Update(1, N, 1, b, c);
        } else {
            cout << Multiply(1, N, 1, min(b, c), max(b, c)) << endl;
        }
    }

    return 0;
}