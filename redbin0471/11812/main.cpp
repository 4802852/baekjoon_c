#include <algorithm>
#include <iostream>

using namespace std;

#define endl '\n'

long long int N;
int K, Q;
long long int d1, d2;

// d1, d2에 a, b 의 깊이를 저장해주는 함수
void FindDepth(long long int a, long long int b) {
    long long int d = 0;
    long long int val = 1;
    while (d1 == -1 || d2 == -1) {
        a -= val;
        b -= val;
        if (a <= 0 && d1 == -1) d1 = d;
        if (b <= 0 && d2 == -1) d2 = d;
        val *= K;
        d++;
    }
}

// a, b의 공통 부모까지의 거리를 카운트하여 dist 계산하는 함수
long long int Solve(long long int a, long long int b) {
    if (K == 1) return abs(a - b);
    d1 = -1;
    d2 = -1;
    FindDepth(a, b);
    long long int dist = 0;
    // 둘의 깊이가 같아질 때까지 더 깊은 쪽을 한칸씩 올린다.
    while (d1 != d2) {
        if (d1 > d2) {
            a = (a - 2) / K + 1;
            dist++;
            d1--;
        } else {
            b = (b - 2) / K + 1;
            dist++;
            d2--;
        }
    }
    // 공통 부모를 만날때까지 양쪽을 한칸씩 올린다.
    while (a != b) {
        a = (a - 2) / K + 1;
        b = (b - 2) / K + 1;
        dist += 2;
    }
    return dist;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    cin >> N >> K >> Q;
    long long int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        cout << Solve(a, b) << endl;
    }

    return 0;
}