#include <iostream>
#include <string>

using namespace std;

#define endl '\n'

char MAP[3][3];
int xnum, onum;

// MAP을 탐색하여 연속3개 있는 문자를 체크하는 함수
int check() {
    int x = 0;
    int o = 0;
    for (int i = 0; i < 3; i++) {
        if (MAP[i][0] == MAP[i][1] && MAP[i][1] == MAP[i][2]) {
            if (MAP[i][0] == 'X') x = 1;
            if (MAP[i][0] == 'O') o = 1;
        };
        if (MAP[0][i] == MAP[1][i] && MAP[1][i] == MAP[2][i]) {
            if (MAP[0][i] == 'X') x = 1;
            if (MAP[0][i] == 'O') o = 1;
        };
    }
    if (MAP[0][0] == MAP[1][1] && MAP[1][1] == MAP[2][2]) {
        if (MAP[1][1] == 'X') x = 1;
        if (MAP[1][1] == 'O') o = 1;
    };
    if (MAP[0][2] == MAP[1][1] && MAP[1][1] == MAP[2][0]) {
        if (MAP[1][1] == 'X') x = 1;
        if (MAP[1][1] == 'O') o = 1;
    };
    if (x == 1 && o == 1) {
        // X와 O가 연속 3개 있는 경우
        return 3;
    } else if (x == 1) {
        // X만 연속 3개 있는 경우
        return 1;
    } else if (o == 1) {
        // Y만 연속 3개 있는 경우
        return 2;
    } else {
        // 비기는 경우
        return 0;
    }
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (1) {
        int valid = 0;
        string in;
        cin >> in;
        if (in == "end") break;
        int index = 0;
        xnum = 0;
        onum = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                MAP[i][j] = in[index++];
                switch (MAP[i][j]) {
                    case 'O':
                        onum++;
                        break;
                    case 'X':
                        xnum++;
                        break;
                }
            }
        }
        if (xnum - onum == 1 && check() == 1) {
            // X가 이기는 경우
            valid = 1;
        } else if (xnum - onum == 0 && check() == 2) {
            // O가 이기는 경우
            valid = 1;
        } else if (xnum == 5 && onum == 4 && check() == 0) {
            // 비기는 경우
            valid = 1;
        }
        if (valid) {
            cout << "valid" << endl;
        } else {
            cout << "invalid" << endl;
        }
    }

    return 0;
}