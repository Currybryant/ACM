#include <bits/stdc++.h>
using namespace std;

#define mes(a, val) memset(a, val, sizeof(a))
#define mec(b, a) memcpy(b, a, sizeof(a))
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f

const int maxn = 1e3 + 10;
int n, m;
char s[maxn], str[maxn];
int nextn[maxn];
/**
    �� str �봮 s ƥ�䣬
    �Ȼ�ȡ�� str �� nextn���飬
    ���봮 s ����ƥ��

**/
void getnext(int len)
{
    mes(nextn, -1);
    int i = 0, j = -1;
    while(i < len)
    {
        if(j == -1 || str[i] == str[j])
        {
            i ++; j++;
            nextn[i] = j;
        }
        else j = nextn[j];
    }
}

int KMP(int n, int m)
{
    int res = 0;
    int i = 0, j = 0;
    while(i < n)
    {
        if(j == -1 || s[i] == str[j])
        {
            i ++; j ++;
        }
        else j = nextn[j];
        if(j == m){res ++; j = 0;};
    }
//    return j == m ? i - j + 1 : -1; ///�����״�ƥ��ɹ����±�
    return res ;///����ƥ��ɹ��Ĵ���
}

int main()
{
	while(scanf("%s", s))
    {
        if(s[0] == '#')break;
        scanf("%s", str);
        int n = strlen(s), m = strlen(str);
        getnext(m);
        printf("%d\n", KMP(n, m));
//        printf("%s   %s\n", s, str);
    }
	return 0;
}

