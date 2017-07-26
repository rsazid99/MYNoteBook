// O(root(v) * E)


int a[110], b[110],level[110], mate[220], n, m;
vector<int>adj[210];
bool bfs()
{
        queue<int> q;
        FORR(i, 0, n){
                level[i] = -1;
                if(mate[i] < 0){
                        level[i] = 0;
                        q.push(i);
                }
        }
        while(!q.empty()){
                int u = q.front();
                q.pop();

                FORR(i, 0, adj[u].size()){
                        int w = adj[u][i];
                        int v = mate[w];
                        if(v < 0) return true;
                        if(level[v] < 0){
                                level[v] = level[u] + 1;
                                q.push(v);
                        }
                }
        }
        return false;
}
bool dfs(int u)
{
        FORR(i, 0, adj[u].size()){
                int w = adj[u][i];
                int v = mate[w];
                if(v < 0 || (level[v] > level[u] && dfs(v))){
                        mate[u] = w;
                        mate[w] = u;
                        return true;
                }
        }
        return false;
}


int main()
{
        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int t , tt = 1;
        scanf("%d", &t);

        while(t --){
                MSET(level, 0);
                MSET(mate, -1);
                scanf("%d", &n);
                FORR(i, 0, n) scanf("%d", &a[i]);
                scanf("%d", &m);
                FORR(i, 0, m) scanf("%d", &b[i]);
                FORR(i, 0, n){
                        FORR(j, 0, m){
                                if(b[j] % a[i] == 0){
                                        adj[i].pb(j + n);
                                        adj[n + j].pb(i);
                                }
                        }
                }

                int match = 0;

                while(bfs()){
                        FORR(i, 0, n){
                                if(mate[i] < 0 && dfs(i)) match++;
                        }
                }

                printf("Case %d: %d\n", tt++, match);
                FOR(i, 0, n + m) adj[i].clear();

        }
        return 0;
}
