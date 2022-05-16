#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define endl '\n'

string word;

vector<int> GetPi(string p) {
    vector<int> Pi(p.length());
    for (int i = 1, j = 0; i < p.length(); i++) {
        while (j > 0 && p[i] != p[j]) j = Pi[j - 1];
        if (p[i] == p[j]) Pi[i] = ++j;
    }
    return Pi;
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> word;

    int Max = 0;
    for (int i = 0; i < word.length(); i++) {
        vector<int> Pi = GetPi(word.substr(i, word.length() - i));
        for (int j = 0; j < word.length() - i; j++) {
            if (Pi[j] > Max) Max = Pi[j];
        }
    }
    cout << Max << endl;

    return 0;
}