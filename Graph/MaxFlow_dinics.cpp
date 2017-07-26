//O(V^2 * E)

vector<pii> v;
int level[20100], src, dest, work[20100];
struct Edge{
        int to, rev;
        int f, cap;
};
vector<Edge> g[20100];

void addEdge(int s, int t, int cap)
{
        Edge a = {t, g[t].size(), 0, cap};
        Edge b = {s, g[s].size(), 0, 0};
        g[s].pb(a);
        g[t].pb(b);
}

bool bfs()
{
        MSET(level, -1);
        level[src] = 0;

        queue<int> q;
        q.push(src);

        while(!q.empty()){
                int u = q.front();
                q.pop();

                if(u == dest) break;

                FORR(i, 0, g[u].size()){
                        Edge &e = g[u][i];
                        if(e.cap > e.f && level[e.to] < 0){
                                q.push(e.to);
                                level[e.to] = level[u] + 1;
                        }
                }
        }

        return level[dest] >= 0;

}


int dfs(int u, int flow)
{
        if(u == dest) return flow;

        for(int &i = work[u]; i < g[u].size(); i ++){
                Edge &e = g[u][i];
                if(e.cap <= e.f) continue;
                int v = e.to;
                if(level[v] == level[u] + 1){
                        int ret = dfs(v, min(flow, e.cap - e.f));
                        if(ret > 0){
                                e.f += ret;
                                g[v][e.rev].f -= ret;
                                return ret;
                        }
                }
        }
        return 0;

}

int max_flow(int _src, int _dest)
{
        src = _src;
        dest = _dest;
        int result = 0;
        while(bfs()){
                MSET(work, 0);
                while(int delta = dfs(src, inf)){
                        result += delta;
                }
        }
        return result;
}
int go(int n, int m)
{
        FOR(i, 0, 20000) g[i].clear();
        FOR(i, 1, 10000){
                addEdge(0, i, 1);
        }

        FORR(i, 0, v.size()){
                FORR(j, v[i].ff, v[i].ss){
                        addEdge(j, 10000 + i + 1, 1);
                }
                addEdge(10000 + i + 1, 10000 + n + 1, m);
        }

        if(max_flow(0, 10000 + n + 1) == (n * m)){
                return 1;
        }
        return 0;

}

int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int n, x, y;
        scanf("%d", &n);

        FOR(i, 1, n){
                scanf("%d %d", &x, &y);
                v.pb(pii(x, y));
        }
        int lo = 0, hi = 11000, mid = 0, ans = 0;
        while(lo <= hi){

                mid = (lo + hi) / 2;

                if(go(n, mid)){
                        ans = mid;
                        lo = mid + 1;
                }
                else{
                        hi = mid - 1;
                }
        }

        printf("%d\n", ans * n);





	return 0;
}
