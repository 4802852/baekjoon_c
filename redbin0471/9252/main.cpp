#include <iostream>
#include <string>

using namespace std;

#define endl '\n'
#define MAX_L 1001

string str1, str2, ans_str;
int dp[MAX_L][MAX_L];

int MaxVal(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> str1 >> str2;
    str1 = ' ' + str1;
    str2 = ' ' + str2;

    // 기본 LCS와 동일하게 공통최대문자열 길이 dp에 저장
    for (int i = 1; i < str1.size(); i++) {
        for (int j = 1; j < str2.size(); j++) {
            if (str1[i] == str2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = MaxVal(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // dp의 맨아래 오른쪽칸에서부터 역추적하여 공통 문자열을 탐색
    int row = str1.size() - 1;
    int col = str2.size() - 1;
    while (dp[row][col]) {
        if (dp[row][col] == dp[row - 1][col]) {
            row--;
        } else if (dp[row][col] == dp[row][col - 1]) {
            col--;
        } else {
            ans_str = str1[row] + ans_str;
            row--;
            col--;
        }
    }

    cout << dp[str1.size() - 1][str2.size() - 1] << endl;
    if (dp[str1.size() - 1][str2.size() - 1] != 0) cout << ans_str << endl;

    return 0;
}