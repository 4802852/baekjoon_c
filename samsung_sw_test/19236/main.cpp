#include<iostream>

using namespace std;

// 물고기의 좌표값, 방향, 생존 여부를 저장하는 구조체
struct FISH
{
    int r;
    int c;
    int Dir;
    bool Live;
};

int Answer;
int MAP[4][4];
FISH Fish[20];

int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int Max(int a, int b)
{
    if (a >= b)
    {
        return (a);
    }
    else
    {
        return (b);
    }
}


void CopyState(int A[][4], int B[][4], FISH C[], FISH D[])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            A[i][j] = B[i][j];
        }
    }
    for (int i = 1; i <= 16; i++)
    {
        C[i] = D[i];
    }
}


// 규칙에 의해 물고기를 움직여주는 함수
void MoveFish()
{
    for (int i = 1; i <= 16; i++)
    {
        if (Fish[i].Live == false) continue;
        int r = Fish[i].r;
        int c = Fish[i].c;
        int Dir = Fish[i].Dir;

        int nr = r + dr[Dir];
        int nc = c + dc[Dir];
        while (nr < 0 || 4 <= nr || nc < 0 || 4 <= nc || MAP[nr][nc] == -1)
        {
            Dir++;
            if (Dir == 8) Dir = 0;
            nr = r + dr[Dir];
            nc = c + dc[Dir];
        }
        int fish_to_change = MAP[nr][nc];
        if (fish_to_change != 0)
        {
            Fish[fish_to_change].r = r;
            Fish[fish_to_change].c = c;
            MAP[r][c] = fish_to_change;
        }
        else
        {
            MAP[r][c] = 0;
        }
        Fish[i].r = nr;
        Fish[i].c = nc;
        Fish[i].Dir = Dir;
        MAP[nr][nc] = i;
    }
}


// DFS 알고리즘으로 물고기와 상어의 움직임 중에 상어가 먹은 물고기의 가장 큰 갯수를 저장
void dfs(int sr, int sc, int sDir, int Sum)
{
    Answer = Max(Answer, Sum);
    
    // 새로운 임시 MAP과 Fish 구조체들을 생성하여 변경전의 데이터 복제
    int tmp_MAP[4][4];
    FISH tmp_Fish[20];
    CopyState(tmp_MAP, MAP, tmp_Fish, Fish);

    // 물고기 이동
    MoveFish();

    //상어 이동
    for (int i = 1; i <= 3; i++)
    {
        int nsr = sr + dr[sDir] * i;
        int nsc = sc + dc[sDir] * i;

        if (nsr < 0 || 4 <= nsr || nsc < 0 || 4 <= nsc || MAP[nsr][nsc] == 0) continue;

        // 상어에게 먹히는 물고기를 죽음처리 해주고, 해당 물고기의 위치, 방향을 저장하고, 물고기의 번호를 더해준 후 DFS 탐색
        int eaten = MAP[nsr][nsc];
        Fish[eaten].Live = false;
        int nsDir = Fish[eaten].Dir;
        MAP[nsr][nsc] = -1;
        MAP[sr][sc] = 0;
        dfs(nsr, nsc, nsDir, Sum + eaten);
        // 탐색 후 상어가 이동하기 전 모습으로 복원
        MAP[sr][sc] = -1;
        MAP[nsr][nsc] = eaten;
        Fish[eaten].Live = true;
    }

    // 탐색 후 물고기 이동 전 모습으로 복구
    CopyState(MAP, tmp_MAP, Fish, tmp_Fish);
}


int main(int argc, char** argv)
{
	// freopen("input.txt", "r", stdin);
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            MAP[i][j] = a;
            Fish[a] = { i, j, b - 1, true };
        }
    }
    
    int first_eaten = MAP[0][0];
    int Dir = Fish[first_eaten].Dir;
    Fish[first_eaten].Live = false;
    MAP[0][0] = -1;
    dfs(0, 0, Dir, first_eaten);
    printf("%d\n", Answer);
	return 0;
}