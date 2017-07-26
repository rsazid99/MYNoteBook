int n;
vector<int> adj[maxn], cost[maxn], indexx[maxn];
char s[30];
int chainno, inChain[maxn], chainHead[maxn], pa[maxn][22], baseArray[maxn];
int posinBase[maxn], ptr, tree[6 * maxn], dep[maxn], subsize[maxn], otherEnd[maxn];

void dfs(int u, int p, int depth)
{
        dep[u] = depth;
        pa[u][0] = p;
        subsize[u] = 1;

        FORR(i, 0, adj[u].size()){
                int v = adj[u][i];
                if(v == p) continue;
                otherEnd[indexx[u][i]] = v;
                dfs(v, u, depth + 1);
                subsize[u] += subsize[v];
        }

}

void HLD(int u, int co, int p)
{
        if(chainHead[chainno] == -1){
                chainHead[chainno] = u;
        }

        inChain[u] = chainno;
        baseArray[++ptr] = co;
        posinBase[u] = ptr;
        int ca =  -1, ncost = 0;

        FORR(i, 0, adj[u].size()){
                int v = adj[u][i];
                if(v == p) continue;
                if(ca == -1 || subsize[v] > subsize[ca]){
                        ncost = cost[u][i];
                        ca = v;
                }
        }
        if(ca != -1){
                HLD(ca, ncost, u);
        }

        FORR(i, 0, adj[u].size()){
                int v = adj[u][i];
                if(v == p) continue;
                if(v != ca){
                        chainno ++;
                        HLD(adj[u][i], cost[u][i], u);
                }
        }
}


void build(int id, int l, int r)
{
        if( l == r){
                tree[id] = baseArray[l];
                return;
        }
        int mid = (l + r) / 2;
        build(2 * id, l, mid);
        build(2 * id + 1, mid + 1, r);
        tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}


void update(int id, int l, int r, int pos, int val)
{
        if(l == r && l == pos){
                tree[id] = val;
                return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) update(id * 2, l, mid, pos, val);
        else update(id * 2 + 1, mid + 1, r, pos, val);
        tree[id] = max(tree[id * 2], tree[id * 2 + 1]);

}




int query(int id, int l, int r, int x, int y)
{

        if( r < x || l > y) return 0;
        if(l >= x && r <= y) {
                return tree[id];
        }

        int mid = ( l + r) / 2;
        return max(query(id * 2, l, mid, x, y), query(id * 2 + 1, mid + 1, r, x, y));
}


int LCA(int p, int q)
{
        if(dep[q] > dep[p]) swap(p, q);

        int lg = 0;

        while(1){
                int next = lg + 1;
                if((1 << next) > n) break;
                lg ++;
        }

        for(int i = lg; i >= 0; i--){
                if(dep[p] - (1 << i) >= dep[q]) p = pa[p][i];
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



int query_up(int u, int v)
{
        if(u == v) return 0;
        int uchain, vchain = inChain[v], ans = - 1;

        while(1){

                uchain = inChain[u];

                if(uchain == vchain){
                        if(u == v) break;
                        int res = query(1, 1, ptr, posinBase[v] + 1, posinBase[u]);
                        if(res > ans) ans = res;
                        break;
                }

                int res = query(1, 1, ptr, posinBase[chainHead[uchain]], posinBase[u]);
                if(res > ans) ans = res;
                u = chainHead[uchain];
                u = pa[u][0];
        }

        return ans;
}

int ret(int u, int v)
{
        int l = LCA(u, v);
        int ans = max(query_up(u, l), query_up(v, l));
        return ans;
}

void change(int i, int val)
{
        int u = otherEnd[i];
        update(1, 1, ptr, posinBase[u], val);
}

int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int t, x, y, z;
        scanf("%d", &t);

        while(t --){
                scanf("%d", &n);
                MSET(pa, -1);
                MSET(chainHead, -1);
                //MSET(tree, 0);
                //MSET(inChain, 0);
                //MSET(baseArray, 0);
                //MSET(posinBase, 0);
                //MSET(otherEnd, 0);
                //MSET(subsize, 0);
                //MSET(dep, 0);

                FORR(i, 1, n){
                        scanf("%d %d %d", &x, &y, &z);
                        adj[x].pb(y);
                        cost[x].pb(z);
                        indexx[x].pb(i);
                        adj[y].pb(x);
                        cost[y].pb(z);
                        indexx[y].pb(i);
                }
                chainno = 0;
                ptr = 0;
                dfs(1, -1, 0);
                HLD(1, -1, -1);
                build(1, 1, ptr);

                for(int j = 1; (1 << j) <= n; j ++){
                        for(int i = 1; i <= n; i ++){
                                if(pa[i][j - 1] != -1){
                                        pa[i][j] = pa[pa[i][j - 1]][j - 1];
                                }
                        }
                }

                while(1){
                        scanf("%s", s);
                        if(s[0] == 'D') break;
                        else if(s[0] == 'Q'){
                                scanf("%d %d", &x, &y);
                                printf("%d\n", ret(x, y));
                        }
                        else if(s[0] == 'C'){
                                scanf("%d %d", &x, &y);
                                change(x, y);
                        }
                }
                FOR(i, 0, n){
                        adj[i].clear();
                        indexx[i].clear();
                        cost[i].clear();
                }

        }


	return 0;
}
