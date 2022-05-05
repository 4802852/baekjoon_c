#include <iostream>
#include <set>

using namespace std;

#define endl '\n'
#define MAX_N 1001

struct RECTANGLE {
    int x1;
    int y1;
    int x2;
    int y2;
};

int N;
RECTANGLE Rectangle[MAX_N];
int parents[MAX_N];
int ranks[MAX_N];

int Find(int x) {
    if (parents[x] == x) {
        return x;
    } else {
        return parents[x] = Find(parents[x]);
    }
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (ranks[x] < ranks[y]) {
        parents[x] = y;
    } else {
        parents[y] = x;
        if (ranks[x] == ranks[y]) {
            ranks[x]++;
        }
    }
}

bool isConnected(RECTANGLE a, RECTANGLE b) {
    int ax1 = a.x1, ay1 = a.y1, ax2 = a.x2, ay2 = a.y2;
    int bx1 = b.x1, by1 = b.y1, bx2 = b.x2, by2 = b.y2;
	// b 사각형 안에 a 사각형이 완전히 들어가는 경우
    if (bx1 < ax1 && ax2 < bx2 && by1 < ay1 && ay2 < by2) return false;
	// a 사각형 안에 b 사각형이 완전히 들어가는 경우
    if (ax1 < bx1 && bx2 < ax2 && ay1 < by1 && by2 < ay2) return false;
	// 두 사각형이 외곽 방향으로 완전히 겹치지 않는 경우
    if (bx2 < ax1 || ax2 < bx1 || by2 < ay1 || ay2 < by1) return false;
    return true;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
	// 처음 위치에서 펜을 내리고 시작하므로 원점과 겹치는 사각형의 존재를 확인하기 위해 원점을 먼저 추가
    parents[0] = 0;
    ranks[0] = 0;
    Rectangle[0] = {0, 0, 0, 0};
    for (int i = 1; i <= N; i++) {
        parents[i] = i;
        ranks[i] = 0;
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        Rectangle[i] = {a, b, c, d};
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
			// 사각형끼리 연결되어있을 경우 유니언
            if (isConnected(Rectangle[i], Rectangle[j])) {
                Union(i, j);
            }
        }
    }
    set<int> ans;
    for (int i = 0; i <= N; i++) {
        ans.insert(Find(i));
    }
    cout << ans.size() - 1 << endl;

    return 0;
}