#include <iostream>
#include <queue>
#include <set>
#include <string>

using namespace std;

#define endl '\n'

int N, K, L;
string NN;

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int BFS() {
    queue<string> Q;
    Q.push(NN);
    int MaxVal = 0;
    int Cur_K = 0;
    set<string> Visit;
    set<string>::iterator iter;

    while (Q.empty() == 0 && Cur_K < K) {
        int size = Q.size();
        Visit.clear();
        for (int s = 0; s < size; s++) {
            string Cur_S = Q.front();
            Q.pop();

            for (int i = 0; i < L - 1; i++) {
                for (int j = i + 1; j < L; j++) {
                    if (i == 0 and Cur_S[j] == '0') continue;
                    swap(Cur_S[i], Cur_S[j]);
                    if (Visit.find(Cur_S) == Visit.end()) {
                        Q.push(Cur_S);
                        Visit.insert(Cur_S);
                    }
                    swap(Cur_S[i], Cur_S[j]);
                }
            }
        }
        Cur_K++;
    }
    if (Cur_K != K) return 0;
    for (iter = Visit.begin(); iter != Visit.end(); iter++) {
        MaxVal = max(MaxVal, stoi(*iter));
    }
    return MaxVal;
}

int Solve() {
    L = NN.length();
    if (L == 1 || (L == 2 && N % 10 == 0)) {
        return 0;
    }
    return BFS();
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N >> K;
    NN = to_string(N);

    int ans = Solve();
    if (ans == 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}