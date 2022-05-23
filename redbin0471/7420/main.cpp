#include <math.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#define _USE_MATH_DEFINES
#define endl '\n'
#define MAX_N 1001

struct INFO {
    long long x;
    long long y;
};

int N, L;
vector<INFO> Info;
vector<INFO> s;
vector<INFO> Vertex;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

long double Dist(INFO a, INFO b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

long long ccw(INFO a, INFO b, INFO c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(INFO a, INFO b) {
    if (a.y == b.y) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

bool cmpccw(INFO a, INFO b) {
    long long res = ccw(Info[0], a, b);
    if (res) {
        return res > 0;
    } else if (a.y == b.y) {
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

    cin >> N >> L;
    int a, b;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        Info.push_back({a, b});
    }

    // 컨벡스헐 알고리즘 적용하여 볼록다각형을 이루는 도시들의 좌표 s 에 저장
    sort(Info.begin(), Info.end(), cmp);
    sort(Info.begin() + 1, Info.end(), cmpccw);
    INFO tmp1, tmp2;
    for (int i = 0; i < N; i++) {
        while (s.size() >= 2) {
            tmp2 = s.back();
            s.pop_back();
            tmp1 = s.back();
            if (ccw(tmp1, tmp2, Info[i]) > 0) {
                s.push_back(tmp2);
                break;
            }
        }
        s.push_back(Info[i]);
    }

    // 컨벡스헐을 이루는 도시들 사이의 거리 합
    long double ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += Dist(s[i], s[(i + 1) % s.size()]);
    }
    // 반지름이 L 인 원의 외경
    long double circle = M_PI * L * 2;

    cout << round(ans + circle) << endl;

    return 0;
}