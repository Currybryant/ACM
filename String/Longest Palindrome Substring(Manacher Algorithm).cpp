#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)



const int maxn = 2*110000+10;
char str0[maxn], str[maxn];
int p[maxn], len;

void Pretreatment(){
    str[0] = '$'; str[1] = '#';
    for(int i = 0; i < len; i ++){
        str[i*2+2] = str0[i];
        str[i*2+3] = '#';
    }
    str[len*2+2] = '\0';
}
int Manacher(){
    mes(p, 0);
    int mx = 0, id, ans = 1;
    for(int i = 1; i < len*2+2; i ++){
        if(mx > 1) p[i] = min(p[2*id-i], mx-i);
        else p[i] = 1;
        for(; str[i-p[i]] == str[i+p[i]]; p[i] ++);
        if(p[i]+i > mx) mx = p[i]+i, id = i;
        ans = max(ans, p[i]);
    }
    return --ans;
}

int main(){

    while(scanf("%s", str0) != EOF){
        len = strlen(str0);
        Pretreatment();
        printf("%d\n", Manacher());
    }

}

