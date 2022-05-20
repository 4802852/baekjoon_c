#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 100001

struct ARROW {
    int x;
    int y;
};
ARROW operator-(ARROW a, ARROW b) {
    ARROW c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

int N;
vector<ARROW> Arrow;
vector<ARROW> s;

long long ccw(ARROW a, ARROW b, ARROW c) {
    long long res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return res;
}

bool cmp(ARROW a, ARROW b) {
    if (a.y == b.y) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

bool cmpccw(ARROW a, ARROW b) {
    long long val = ccw(Arrow[0], a, b);
    if (val) {
        return val > 0;
    } else if (a.y == b.y) {
        return a.x < b.x;
    } else {
        return (a.y < b.y);
    }
}

int dist(ARROW a, ARROW b) {
    int res = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    return res;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed;
    cout.precision(8);

    cin >> N;
    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        Arrow.push_back({a, b});
    }
    if (N == 2) {
        cout << sqrt(dist(Arrow[0], Arrow[1])) << endl;
        return 0;
    }
    sort(Arrow.begin(), Arrow.end(), cmp);
    sort(Arrow.begin() + 1, Arrow.end(), cmpccw);
    ARROW tmp1, tmp2;
    for (int i = 0; i < N; i++) {
        while (s.size() >= 2) {
            tmp2 = s.back();
            s.pop_back();
            tmp1 = s.back();
            if (ccw(tmp1, tmp2, Arrow[i]) > 0) {
                s.push_back(tmp2);
                break;
            }
        }
        s.push_back(Arrow[i]);
    }
    int Size = s.size();

    // Brute Force 문제 풀이

    // int ans = 0;
    // for (int i = 0; i < Size - 1; i++) {
    //     for (int j = i + 1; j < Size; j++) {
    //         ans = max(ans, dist(s[i], s[j]));
    //     }
    // }
    // cout << sqrt(ans) << endl;

    // Rotating Callipers 문제 풀이

    int lp = 0, rp = 0;
    for (int i = 0; i < Size; i++) {
        if (s[i].x < s[lp].x) lp = i;
        if (s[i].x > s[rp].x) rp = i;
    }
    int ans = dist(s[lp], s[rp]);
    ARROW Origin = {0, 0};
    for (int i = 0; i < Size; i++) {
        if (ccw(Origin, s[(lp + 1) % Size] - s[lp], s[(rp + 1) % Size] - s[rp]) < 0) {
            lp = (lp + 1) % Size;
        } else {
            rp = (rp + 1) % Size;
        }
        ans = max(ans, dist(s[lp], s[rp]));
    }
    cout << sqrt(ans) << endl;

    return 0;
}