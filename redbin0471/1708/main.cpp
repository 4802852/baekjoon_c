#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define endl '\n'
#define MAX_N 100001

struct POINT {
    long long x;
    long long y;
};

int N;
vector<POINT> Point;
stack<POINT> s;

int ccw(POINT a, POINT b, POINT c) {
    long long res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (0 < res) {
        return 1;
    } else if (res < 0) {
        return -1;
    } else {
        return 0;
    }
}

bool cmp(POINT a, POINT b) {
    if (a.y == b.y) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

bool cmpccw(POINT a, POINT b) {
    int val = ccw(Point[0], a, b);
    if (val) {
        return val > 0;
    } else if (b.y == a.y) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    int a, b;
    for (int i = 1; i <= N; i++) {
        cin >> a >> b;
        Point.push_back({a, b});
    }
    sort(Point.begin(), Point.end(), cmp);
    sort(Point.begin() + 1, Point.end(), cmpccw);
    s.push(Point[0]);
    s.push(Point[1]);
    POINT tmp1, tmp2;
    for (int i = 2; i < N; i++) {
        while (s.size() >= 2) {
            tmp2 = s.top();
            s.pop();
            tmp1 = s.top();
            if (ccw(tmp1, tmp2, Point[i]) > 0) {
                s.push(tmp2);
                break;
            }
        }
        s.push(Point[i]);
    }
    cout << s.size() << endl;

    return 0;
}