#include <iostream>

using namespace std;

#define endl '\n'

struct INFO {
    int x;
    int y;
};

INFO Info[4];

int ccw(INFO a, INFO b, INFO c) {
    int res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (res > 0) {
        return 1;
    } else if (res < 0) {
        return -1;
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

    for (int i = 0; i < 4; i++) {
        cin >> Info[i].x >> Info[i].y;
    }

    if (ccw(Info[0], Info[1], Info[2]) * ccw(Info[0], Info[1], Info[3]) < 0) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}