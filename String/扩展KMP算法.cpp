#include <bits/stdc++.h>
using namespace std;

#define mes(a, val) memset(a, val, sizeof(a))
#define mec(b, a) memcpy(b, a, sizeof(a))
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f

const int MAX=100010; //�ַ����������ֵ
int Next[MAX],extend[MAX];
/**
    ��չ KMP ����Ƕ���ԭ�� S1 ��ÿһ����׺�Ӵ���ģʽ�� S2 �������ǰ׺
    Next[i] �����ʾģʽ�� s2 ���� i Ϊ���ĺ�׺�ַ�����ģʽ�� s2 �������ǰ׺����
    extend[i] ��ʾΪ���ַ��� S1 ����iΪ���ĺ�׺�ַ�����ģʽ��S2�������ǰ׺����.
**/
//Ԥ�������Next����
void getNext(char str[])
{
    int i=0,j,po,len=strlen(str);
    next[0]=len; //��ʼ��next[0]
    while(str[i]==str[i+1] && i+1<len) i++; next[1]=i; //����next[1]
    po=1; //��ʼ��po��λ��
    for(i=2;i<len;i++)
    {
        if(next[i-po]+i < next[po]+po) //��һ�����������ֱ�ӵõ�next[i]��ֵ
            next[i]=next[i-po];
        else //�ڶ��������Ҫ����ƥ����ܵõ�next[i]��ֵ
        {
            j = next[po]+po-i;
            if(j<0) j=0; //���i>po+next[po],��Ҫ��ͷ��ʼƥ��
            while(i+j<len && str[j]==str[j+i]) j++; next[i]=j;
            po=i; //����po��λ��
        }
    }
}

//����extend����
void EXKMP(char s1[],char s2[])
{
    int i=0,j,po,len=strlen(s1),l2=strlen(s2);
    getNext(s2); //�����Ӵ���next����
    while(s1[i]==s2[i] && i<l2 && i<len) i++; extend[0]=i;
    po=0; //��ʼ��po��λ��
    for(i=1;i<len;i++)
    {
        if(next[i-po]+i < extend[po]+po) //��һ�������ֱ�ӿ��Եõ�extend[i]��ֵ
            ex[i]=next[i-po];
        else //�ڶ��������Ҫ����ƥ����ܵõ�extend[i]��ֵ
        {
            j = extend[po]+po-i;
            if(j<0) j=0; //���i>extend[po]+po��Ҫ��ͷ��ʼƥ��
            while(i+j<len && j<l2 && s1[j+i]==s2[j]) j++; extend[i]=j;
            po=i; //����po��λ��
        }
    }
}

int main()
{

}

