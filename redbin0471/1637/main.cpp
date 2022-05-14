#include <algorithm>
#include <iostream>

using namespace std;

#define endl '\n'

struct ITEM {
    int a;
    int c;
    int b;
};

int N;
ITEM Item[20001];

long long Count(long long mid) {
    if (mid == 0) return 0;
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        long long num = 0;
        long long val = min((long long)Item[i].c, mid) - Item[i].a;
        num = val < 0 ? 0 : val / Item[i].b + 1;
        sum += num;
    }
    return sum;
}

void Solve() {
    int ans = -1;
    long long left = 0;
    long long right = 2147483647;
    while (left <= right) {
        long long mid = (left + right) / 2;
        if (Count(mid) % 2 == 0) {
            left = mid + 1;
        } else {
            ans = (int)mid;
            right = mid - 1;
        }
    }
    if (ans == -1) {
        cout << "NOTHING" << endl;
    } else {
        cout << ans << ' ' << Count(ans) - Count(ans - 1) << endl;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    int a, b, c;
    for (int i = 0; i < N; i++) {
        cin >> a >> c >> b;
        Item[i] = {a, c, b};
    }
    Solve();

    return 0;
}