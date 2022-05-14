#include <iostream>

using namespace std;

#define endl '\n'
#define MAX_N 100001

int G, P;
int Parent[MAX_N];

int Find(int x) {
    if (x == Parent[x]) return x;
    return Parent[x] = Find(Parent[x]);
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> G >> P;
    for (int i = 1; i <= G; i++) {
        Parent[i] = i;
    }
    int total = 0;
    int p;
    for (int i = 0; i < P; i++) {
        cin >> p;
        if (Find(p) == 0) break;
        total++;
        Parent[Find(p)] = Find(Find(p) - 1);
    }

    cout << total << endl;

    return 0;
}