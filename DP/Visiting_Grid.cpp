//####################################################################
//#####In the Name Of Allah,the Most Gracious,the Most Merciful.######
//####################################################################

#include <bits/stdc++.h>
using namespace std;

#define maxn            100010
#define esp             1e-6
#define mod             1000000007
#define ll              long long
#define inf             1061109567
#define ff  first
#define ss  second

typedef pair<int, int> ii;

int Set(int N, int pos) {return N = N | (1 << pos);}
int reset(int N, int pos) {return N = N & ~ (1 << pos);}
bool check(ll N, int pos) {return (bool) (N & (1LL << pos));}


int n, m, k, block[8][8], x, y;
int pw[] = {1, 5, 25, 125, 625, 3125, 15625, 78125};
ll dp[8][8][2000000];
int grid[8][8], visited[8][8][2000000], tc = 0;

bool ok(int i, int j, int clr)
{
        if(grid[i - 1][j] == clr) return false;
        if(grid[i][j - 1] == clr) return false;
        return true;
}

ll dpfun(int r, int c, int val)
{
        if(c > m + 1){
                r ++;
                c = 1;
        }
        if(r > n + 1) return 1;

        if(visited[r][c][val] == tc) return dp[r][c][val];

        ll ret = 0;
        ll tmp = val - pw[c] * grid[r - 1][c];

        if(block[r][c]){
                grid[r][c] = 0;
                ret = (ret  + dpfun(r, c + 1, tmp + pw[c] * 0)) % mod;
        }
        else{
                if(ok(r, c, 1)){
                        grid[r][c] = 1;
                        ret = (ret + dpfun(r, c + 1, tmp + pw[c] * 1)) % mod;
                }
                if(ok(r, c, 2)){
                        grid[r][c] = 2;
                        ret = (ret + dpfun(r, c + 1, tmp + pw[c] * 2)) % mod;
                }
                if(ok(r, c, 3)){
                        grid[r][c] = 3;
                        ret = (ret  + dpfun(r, c + 1, tmp + pw[c] * 3)) % mod;
                }
                if(ok(r, c, 4)){
                        grid[r][c] = 4;
                        ret = (ret + dpfun(r, c + 1, tmp + pw[c] * 4)) % mod;
                }
        }
        visited[r][c][val] = tc;
        return dp[r][c][val] = ret;


}

int main()
{

        int t, tt = 1;
        scanf("%d", &t);
        while(t --){

                scanf("%d %d", &n, &m);
                scanf("%d", &k);

                memset(block, 0, sizeof block);
                memset(grid, 0, sizeof grid);

                for(int i = 0; i < k; i ++){
                        scanf("%d %d", &x, &y);
                        block[x][y] = 1;
                }
                tc ++;
                ll ans = dpfun(1, 1, 0);

                printf("Case %d: %lld\n", tt++, ans);


        }

        return 0;
}
