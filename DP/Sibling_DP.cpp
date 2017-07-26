vector<int> adj[2 * maxn];
ll memo[2 * maxn][2];
ll dp2(int u, int pa, int c, int ally);

 // sibling Dynamic programming ............

ll dp(int u, int pa, int ally)
{
        return dp2(u, pa, 0, ally) % mod;
}

ll dp2(int u, int pa, int c, int ally)
{
        if(c == adj[u].size()) return ally;

        if(adj[u][c] == pa) return dp2(u, pa, c + 1, ally);

        int v = adj[u][c];

        if(memo[v][ally] != -1) return memo[v][ally];

        // make the child allay to parent and so on the next child ....

        ll ret = dp(v, u, 1) * dp2(u, pa, c + 1, 1);
        ret %= mod;

        // without making the child ally to parent & continue allaying next.....

        ll tmp = dp(v, u, 0) * dp2(u, pa, c + 1, ally);
        tmp %= mod;

        ret += tmp;

        return memo[v][ally] = ret % mod;
}


int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int n, x, y;
        cin >> n;
        MSET(memo, -1);
        FOR(i, 1, n - 1){
                cin >> x >> y;
                adj[x].pb(y);
                adj[y].pb(x);
        }

        ll ans = dp(1, 0, 0);

        cout << (2 * ans) % mod << endl;

        return 0;
}
