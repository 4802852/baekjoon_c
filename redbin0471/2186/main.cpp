#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define endl '\n'
#define MAX_N 101

int N, M, K;
char MAP[MAX_N][MAX_N];
int DP[MAX_N][MAX_N][81];
string word;
int word_len;

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int dfs(int r, int c, int idx) {
	// 이미 탐색이 완료된 문자라면 리턴
    if (DP[r][c][idx] != -1) return DP[r][c][idx];
	// 단어의 마지막 알파벳의 DP 값은 1
    if (word_len <= idx) return 1;
    DP[r][c][idx] = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= K; j++) {
            int nr = r + dr[i] * j;
            int nc = c + dc[i] * j;
            if (nr < 0 || N <= nr || nc < 0 || M <= nc) continue;
            if (MAP[nr][nc] != word[idx]) continue;
            DP[r][c][idx] += dfs(nr, nc, idx + 1);
        }
    }
    return DP[r][c][idx];
}

int main(int argc, char** argv) {
    // freopen 주석 처리
    freopen("input.txt", "r", stdin);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
        }
    }
    cin >> word;
    word_len = word.length();
    memset(DP, -1, sizeof(DP));

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (MAP[i][j] == word[0]) {
                ans += dfs(i, j, 1);
            }
        }
    }
    cout << ans << endl;
    return 0;
}