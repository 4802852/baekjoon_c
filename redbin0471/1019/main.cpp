#include <iostream>

using namespace std;

#define endl '\n'

int N;
long long ans[10];

void subcounting(int num, int increase) {
    while (num) {
        ans[num % 10] += increase;
        num /= 10;
    }
}

void counting(int start, int end, int digit) {
    while (start % 10 && start <= end) {
        subcounting(start, digit);
        start++;
    }
    if (end < start) return;
    while (end % 10 != 9 && start <= end) {
        subcounting(end, digit);
        end--;
    }
    long long cnt = end / 10 - start / 10 + 1;
    for (int i = 0; i < 10; i++) {
        ans[i] += cnt * digit;
    }
    counting(start / 10, end / 10, digit * 10);
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N;

    counting(1, N, 1);

    for (int i = 0; i < 10; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}