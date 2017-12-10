int q, n, m;
ll l, r;
int a[70], b[70];
int dp[70][2][2];
ll road[70][2][2];
// w1 is a boolean variable that indicates that the current number is greater than l && w2 indicates that the current number is less than r .
int dpfun(int pos, int w1, int w2)
{
        if(pos == n + 1) return 0;

        int &ret = dp[pos][w1][w2];

        if(ret != -1) return ret;

        for(ll i = 0; i < 2; i ++){
                if((w1 | a[pos] == 0 | i == 1) && (w2 | b[pos] == 1| i == 0)){
                        if(dpfun(pos + 1, w1 | ( i > a[pos]), w2 | (i < b[pos])) + i > ret){
                                ret = dpfun(pos + 1, w1 | ( i > a[pos]), w2 | (i < b[pos])) + i;
                                road[pos][w1][w2] = road[pos + 1][ w1 | ( i > a[pos])][w2 | (i < b[pos])] | (i << (n - pos));
                        }
                }
        }

        return ret;
}


ll solve()
{
        memset(dp, -1, sizeof dp);
        memset(road, 0, sizeof road);


        n = -1;

        while(l){
                a[ ++ n] = l % 2;
                l /= 2;
        }

        reverse(a, a + n + 1);

        m = -1;

        while(r){
                b[ ++ m] = r % 2;
                r /= 2;
        }

        reverse(b, b + m + 1);

        for(int i = m; i >= m - n; i --){
                a[i] = a[i - (m - n)];
        }

        for(int i = 0; i < m - n; i ++) a[i] = 0;
        n = m;
        dpfun(0, 0, 0);

        return road[0][0][0];

}

int main(){

        scanf("%d", &q);

        for(int i = 1; i <= q; i ++){
                scanf("%lld %lld", &l, &r);

                cout << solve() << endl;
        }

        return 0;
}

