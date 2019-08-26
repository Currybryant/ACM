
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)

const int maxn = 1e5+100;
int n, m, pos, cnt = 0;
int a[maxn], b[maxn], root[maxn];
struct Seg{
    int l, r, sum;
}T[maxn*40];
int getid(int x){
    return lower_bound(b+1, b+pos, x) - b;
}
void change(int l, int r, int &x, int y, int pos){
    T[++cnt] = T[y]; T[cnt].sum ++; x = cnt;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(mid >= pos) change(l, mid, T[x].l, T[y].l, pos);
    else change(mid + 1, r, T[x].r, T[y].r, pos);
}
int query(int l, int r, int x, int y, int k){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int sum = (T[T[y].l].sum - T[T[x].l].sum);
    if(sum >= k) return query(l, mid, T[x].l, T[y].l, k);
    else return query(mid + 1, r, T[x].r, T[y].r, k - sum);
}
int main()
{
    int nCase; scanf("%d", &nCase);
    while(nCase --){

        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
        }
        mec(b, a);
        sort(b + 1, b + n + 1);
        pos = unique(b + 1, b + n + 1) - b;
        cnt = 0;
        for(int i = 1; i <= n; i ++){
            change(1, n, root[i], root[i-1], getid(a[i]));
        }
        while(m --){
            int x, y, k; scanf("%d %d %d", &x, &y, &k);
            int ans = query(1, n, root[x-1], root[y], k);
            printf("%d\n", b[ans]);
        }
    }
    return 0;
}

/**
500
10 5
3 4 5 6 7 8 9 10 34 2
1 2 1
1 4 2


**/
