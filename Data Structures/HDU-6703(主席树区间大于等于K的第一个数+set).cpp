#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)

const int maxn = 1e5+100;
int n, m, pos, cnt = 0;
int root[maxn], a[maxn];
set<int>st;
struct Seg{
    int l, r, sum;
}T[maxn<<5];
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
    int sum_l = T[T[y].l].sum - T[T[x].l].sum;
    int sum_r = T[T[y].r].sum - T[T[x].r].sum;
    int ans = inf;
    if(mid >= k && sum_l) ans = query(l, mid, T[x].l, T[y].l, k);
    if(ans != inf) return ans;
    if(sum_r) ans = query(mid + 1, r, T[x].r, T[y].r, k);
    return ans;
}
int main()
{
    int nCase; scanf("%d", &nCase);
    int Ans = 0;
    while(nCase --){
        Ans = 0;
        st.clear();
        set<int>::iterator it;
        cnt = 0;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i ++){
            int x;scanf("%d", &a[i]);
        }
        a[n+1] = n+1;
        for(int i = 1; i <= n+1; i ++){
            change(1, n+1, root[i], root[i-1], a[i]);
        }
        while(m --){
            int op, t1, t2;
            scanf("%d", &op);
            if(op == 1){
                scanf("%d", &t1);
                int pos = t1 ^ Ans;
                st.insert(a[pos]);
            }
            else if(op == 2){
                scanf("%d %d", &t1, &t2);
                int r = t1 ^ Ans, k = t2 ^ Ans;
                int y = n + 1;
                Ans = query(1, n+1, root[r], root[y], k);
                if(st.size()){
                    it = st.lower_bound(k);
                    if(it != st.end()) Ans = min(Ans, *it);
                }
                printf("%d\n", Ans);
            }
        }
    }
    return 0;
}
/**
500
5 9
4 3 1 2 5
2 1 1
2 2 2
2 6 7
2 1 3
2 6 3
2 0 4
1 5
2 3 7
2 4 3
**/
