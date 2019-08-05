#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)
/**
HDU-2196 经典树形dp
节点x是y的父亲节点
dp[y][0] 表示以y为根节点的子树中的最长距离
dp[y][1] 表示以y为根节点的子树中的次长距离
dp[y][2] 表示节点y向根节点x走的最长距离

dp[y][2] = max(dp[x][1] + z, dp[x][2] + z); 当以x为根的子树中的最长距离经过节点y
dp[y][2] = max(dp[x][0] + z, dp[x][2] + z); 当以x为根的子树中的最长距离不不不不经过节点y

**/
const int maxn = 1e4+10;
int n, tot, root;
int ver[maxn<<1], head[maxn<<1], Next[maxn<<1], edge[maxn<<1];
int dp[maxn][4];
int flag[maxn];

void init(){
    tot = 0; mes(dp, 0); mes(head, 0); mes(Next, 0);
}

void addedge(int x, int y, int z){
    ver[++tot] = y; edge[tot] = z;
    Next[tot] = head[x]; head[x] = tot;
}

void dfs1(int x, int fa){
    int m1 = 0, m2 = 0;

    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i], z = edge[i];
        if(y == fa) continue;
        dfs1(y, x);

        if(dp[y][0] + z >= m1) {
            m2 = m1; m1 = dp[y][0] + z; flag[x] = y;
        }
        else if(dp[y][0] + z > m2){
            m2 = dp[y][0] + z;
        }
        else if(dp[y][1] + z > m2){
            m2 = dp[y][1] + z;
        }
    }
    dp[x][0] = m1; dp[x][1] = m2;
}

void dfs2(int x, int fa){

    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i], z = edge[i];
        if(y == fa) continue;

        if(flag[x] == y){
            dp[y][2] = max(dp[x][1] + z, dp[x][2] + z);
        }
        else {
            dp[y][2] = max(dp[x][0] + z, dp[x][2] + z);
        }
        dfs2(y, x);
    }
}

int main()
{
    while(scanf("%d", &n) != EOF){
        init();

        for(int i = 2; i <= n; i ++){
            int y, z; scanf("%d %d", &y, &z);
            addedge(y, i, z); addedge(i, y, z);
        }
        root = 1;
        dfs1(root, root);
        dfs2(root, root);
        for(int i = 1; i <= n; i ++){
            printf("%d\n", max(dp[i][0], dp[i][2]));
        }
    }
    return 0;
}
/**
5
1 1
2 1
3 1
1 1


**/

