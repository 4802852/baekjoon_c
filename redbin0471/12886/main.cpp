#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

#define endl '\n'

int A, B, C;
int visited[1501][1501];

int Solve() {
    int sum = A + B + C;
    if (sum % 3 != 0) {
        // 세 숫자의 합이 3의 배수가 아닐 경우, 동일한 숫자로 만들기 불가능
        return 0;
    }
    queue<pair<int, int>> Q;
    Q.push(make_pair(A, B));
    visited[A][B] = 1;
    int a, b;

    while (!Q.empty()) {
        a = Q.front().first;
        b = Q.front().second;
        int tmp[3] = {a, b, sum - a - b};
        Q.pop();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tmp[i] < tmp[j]) {
                    int num1 = tmp[i] * 2;
                    int num2 = tmp[j] - tmp[i];
                    if (visited[num1][num2]) continue;
                    visited[num1][num2] = 1;
                    Q.push(make_pair(num1, num2));
                }
            }
        }
    }
    return visited[sum / 3][sum / 3];
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> A >> B >> C;

    cout << Solve() << endl;

    return 0;
}