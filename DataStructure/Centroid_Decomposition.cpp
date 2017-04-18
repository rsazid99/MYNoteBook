
//################################### coloring in graph #################################
set<int> g[2 * maxn];
int n, m, x, y;
int pa[2 * maxn][60], depth[2 * maxn], sub[2 * maxn], par[2 * maxn], ans[2 * maxn];
// Lca part starts ..................................


void dfs(int u, int from, int dep)
{
        pa[u][0] = from;
        depth[u] = dep;
        for(auto it = g[u].begin(); it != g[u].end(); it ++){
                if(*it == from) continue;
                dfs(*it, u, dep + 1);
        }
}

void preprocess()
{
        dfs(1, 1, 0);
        for(int j = 1; 1 << j <= n; j ++){
                for(int i = 1; i <=n; i ++){
                        if(pa[i][j - 1] != -1)
                                pa[i][j] = pa[pa[i][j - 1]][j - 1];
                }
        }
}

int LCA(int p, int q)
{
        if(depth[q] > depth[p]) swap(p, q);

        int lg = 0;

        while(1){
                int next = lg + 1;
                if((1 << next) > n) break;
                lg ++;
        }

        for(int i = lg; i >= 0; i--){
                if(depth[p] - (1 << i) >= depth[q]) p = pa[p][i];
        }

        if(p == q) return p;

        for(int i = lg; i >= 0; i--){
                if(pa[p][i] != pa[q][i]){
                        p = pa[p][i];
                        q = pa[q][i];
                }
        }
        return pa[p][0];

}

int dist(int u, int v)
{
        return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

// decomposition part starts ..................................

int nn;

void dfs1(int u, int from)
{
        sub[u] = 1;
        nn ++;
        for(auto it = g[u].begin(); it != g[u].end(); it ++){
                if(*it == from) continue;
                dfs1(*it, u);
                sub[u] += sub[*it];
        }
}

int dfs2(int u, int from)
{
        for(auto it = g[u].begin(); it != g[u].end(); it ++){
                if(*it == from) continue;
                if(sub[*it] > nn / 2)
                       return dfs2(*it, u);
        }
        return u;
}


void decompose(int root, int from)
{
        nn = 0;
        dfs1(root, root);
        int centriod = dfs2(root, root);

        if(from == -1) from = centriod;
        par[centriod] = from;

        for(auto it = g[centriod].begin(); it != g[centriod].end(); it ++){
                g[*it].erase(centriod);
                decompose(*it, centriod);
        }
        g[centriod].clear();

}
// handle query............................

void update(int u)
{
        int no = u;

        while(1){
                ans[no] = min(ans[no], dist(no, u));
                if(par[no] == no) break;
                no = par[no];
        }
}

int query(int u)
{
        int no = u;
        int ret = inf;
        while(1){
                ret = min(ret, ans[no] + dist(no, u));
                if(par[no] == no) break;
                no = par[no];
        }
        return ret;
}


int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        MSET(ans, 63);
        scanf("%d %d", &n, &m);
        FOR(i, 1, n - 1){
                scanf("%d %d", &x, &y);
                g[x].insert(y);
                g[y].insert(x);
        }
        preprocess();
        decompose(1, -1);
        update(1);

        while(m --){
                scanf("%d %d", &x, &y);

                if(x == 1) update(y);
                else{
                        cout << query(y) << endl;
                }
        }

        return 0;
}

//################################### distance in graph #################################


set<int> se[50005];
bitset<50005> bs;
int n, x, y, sub[50005], dist[17][50005], P[50005], nn, len;
ll ans = 0;


void sieve()
{
        bs.set();
        bs[0] = 0, bs[1] = 0;

        P[len ++] = 2;
        for(int i = 4; i <= 50000; i += 2) bs[i] = 0;

        for(int i = 3; i <= 50005; i += 2){
                if(bs[i]){
                        P[len ++] = i;
                        if(i <= sqrt(50000 * 1.00)) for(ll j = i * i; j <= 50005; j += 2 * i) bs[j] = 0;
                }
        }

}


void dfs(int u, int from)
{
        sub[u] = 1;
        nn ++;
        for( set<int> :: iterator it = se[u].begin(); it != se[u].end(); it ++){
                if(*it == from) continue;
                dfs(*it, u);
                sub[u] += sub[*it];
        }
}


int dfs2(int u, int pa)
{
        for(set<int> :: iterator it = se[u].begin(); it != se[u].end(); it ++){
                if(*it == pa) continue;
                if(sub[*it] > nn / 2) return dfs2(*it, u);
        }
        return u;
}

void update(int u, int pa, int depth, int dst)
{
        dist[depth][dst] ++;
        for(set<int> :: iterator it = se[u].begin(); it != se[u].end(); it ++){
                if(*it == pa) continue;
                update(*it, u, depth, dst + 1);
        }

}


ll query(int u, int pa, int depth, int dst)
{
        ll ret = 0;

        FORR(i, 0, len){
                if(P[i] - dst < 0) continue;
                if(!dist[depth][P[i] - dst]) break;
                ret += dist[depth][P[i] - dst];
        }

        for(set<int> :: iterator it = se[u].begin(); it != se[u].end(); it ++){
                if(*it == pa) continue;
                ret += query(*it, u, depth, dst + 1);
        }
        return ret;
}

void decompose(int root, int depth)
{
        nn = 0;
        dfs(root, -1);
        int cent = dfs2(root, -1);
        dist[depth][0] = 1;
        for(set<int> :: iterator it = se[cent].begin(); it != se[cent].end(); it ++){

                ans += query(*it, cent, depth, 1);
                update(*it, cent, depth, 1);
        }

        for(set<int> :: iterator it = se[cent].begin(); it != se[cent].end(); it ++){
                se[*it].erase(cent);
                decompose(*it, depth + 1);
        }
        for(int i = 0; i <= n && dist[depth][i]; i ++) dist[depth][i] = 0;
}


int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        sieve();

        scanf("%d", &n);

        FOR(i, 1, n - 1){
                scanf("%d %d", &x, &y);
                se[x].insert(y);
                se[y].insert(x);
        }

        decompose(1, 0);

        ll dw = ((ll)n * (ll)(n - 1)) / 2.0;

        double res = (double) ans / (double) dw;

        printf("%.8f\n" , res);


	return 0;
}
//################################################################################
