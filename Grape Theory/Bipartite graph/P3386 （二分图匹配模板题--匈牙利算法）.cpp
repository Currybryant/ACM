
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 2e3+100;
int n, m, E;
int tot, ver[2000100], head[2000100], Next[2000100];
int match[maxn];
bool vis[maxn];

void addedge(int x, int y){
    ver[++ tot] = y; Next[tot] = head[x]; head[x] = tot;
}

bool dfs(int x){
    vis[x] = true;
    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i], w = match[y];
        if(w < 0 || (!vis[w] && dfs(w))){
            match[x] = y; match[y] = x; return true;
        }
    }
    return false;
}
int max_match(){
    mes(match, -1);
    int res = 0;
    for(int i = 1; i <= n; i ++){
        if(match[i] < 0){
            mes(vis, 0);
            if(dfs(i)){
                res ++;
            }
        }
    }
    return res;
}

int main()
{
    scanf("%d %d %d", &n, &m, &E);
    while(E --){
        int x, y; scanf("%d %d", &x, &y);
        if(x > n || y > m) continue;
        addedge(x, y + n); addedge(y + n, x);
    }
    printf("%d\n", max_match());
    return 0;
}

/**
4 4 7
1 1
2 1
2 3
2 4
3 2
3 4
4 3

**/
