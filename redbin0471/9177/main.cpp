#include <cstring>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define endl '\n'
#define MAX_L 201

struct info {
    int first;
    int second;
    int third;
};

int N;
string Data[3];
int visited[MAX_L][MAX_L];

int bfs() {
    memset(visited, 0, sizeof(visited));
    queue<info> Q;
    Q.push({0, 0, 0});
    visited[0][0] = 1;
    while (!Q.empty()) {
        int first = Q.front().first;
        int second = Q.front().second;
        int third = Q.front().third;
        Q.pop();
        if (third == Data[2].length()) return 1;
		// third 인덱스에 해당하는 문자가 first 인덱스 문자, second 인덱스 문자와 동시에 일치할 경우 두가지 모두 큐에 넣어 탐색해준다.
        if (first < Data[0].length() && Data[0][first] == Data[2][third] && visited[first + 1][second] == 0) {
            Q.push({first + 1, second, third + 1});
            visited[first + 1][second] = 1;
        }
        if (second < Data[1].length() && Data[1][second] == Data[2][third] && visited[first][second + 1] == 0) {
            Q.push({first, second + 1, third + 1});
            visited[first][second + 1] = 1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> Data[0] >> Data[1] >> Data[2];
        string ans;
        if (bfs()) {
            ans = "yes";
        } else {
            ans = "no";
        }
        cout << "Data set " << i << ": " << ans << endl;
    }

    return 0;
}