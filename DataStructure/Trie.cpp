//####################################################################
//#####In the Name Of Allah,the Most Gracious,the Most Merciful.######
//####################################################################

#include <bits/stdc++.h>
using namespace std;

#define maxn            1000010
#define esp             1e-6
#define mod             1000000007
#define ll              long long
#define inf             1061109567
#define ff  first
#define ss  second

int Set(int N, int pos) {return N = N | (1 << pos);}
int reset(int N, int pos) {return N = N & ~ (1 << pos);}
bool check(ll N, int pos) {return (bool) (N & (1LL << pos));}

int n;
char s[4010][1010];

struct Node{
        ll next, endmark, cnt;
        int nxt[64];
} node[4 * maxn];
int last = 0;

void newNode(bool f = false)
{
        if(f) last = 0;
        else last ++;
        node[last].cnt = 0, node[last].next = 0, node[last].endmark = 0;
}


int get_v(char ch)
{
        if(ch >= '0' && ch <= '9') return ch - '0';

        if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;

        if(ch >= 'a' && ch <= 'z') return ch - 'a' + 36;
}

void insert(string r, int len)
{
        int cur = 0;
        for(int i = 0; i < len; i++){
                int word = get_v(r[i]);
                if(!check(node[cur].next , word)){
                        node[cur].next |= (1LL << word);
                        newNode();
                        node[cur].nxt[word] = last;
                }
                cur = node[cur].nxt[word];
                node[cur].cnt ++;
        }
        node[cur].endmark ++;
}
ll query(int from, int last)
{
        ll ret = 0;

        for(int i = 0; i < 63; i ++){
                if(check(node[from].next , i)){
                        int cur = node[from].nxt[i];
                        ret += node[cur].cnt * (node[cur].cnt - 1);
                        ret += node[cur].cnt * node[from].endmark;
                        ret += (last - node[cur].cnt) * node[cur].cnt;
                        ret += query(cur, node[cur].cnt - node[cur].endmark);
                        last -= node[cur].cnt;
                }
        }
        ret += node[from].endmark * (node[from].endmark - 1);

        return ret;
}

int main()
{

        int tt = 1;
        while(scanf("%d", &n)){
                if(n == 0) break;

                newNode(true);
                ll ans = 0;
                for(int i = 0; i < n; i ++){
                        scanf("%s", s[i]);
                }
                for(int i = 0; i < n; i ++){
                        insert(s[i], strlen(s[i]));
                }

                ans = query(0, n);

                printf("Case %d: %lld\n", tt ++, ans);

        }

        return 0;
}

