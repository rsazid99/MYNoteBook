int n, x, arr[2 * maxn], q, idx[2 * maxn], org[2 * maxn], en[2 * maxn], cc, on[4 * 2 * maxn], lazy[4 * 2 * maxn];
vector<int> adj[2 * maxn];
char s[10];

void dfs(int u, int from)
{
        idx[u] = ++cc;
        en[idx[u]] = idx[u];
        org[idx[u]] = u;
        for(int i = 0; i < adj[u].size(); i ++){
                int v = adj[u][i];
                if(v == from) continue;
                dfs(v, u);
                en[idx[u]] = max(en[idx[u]], en[idx[v]]);
        }
}

void build(int id, int l, int r)
{
        if(l == r){
                on[id] = arr[org[l]];
                lazy[id] = 0;
                return;
        }

        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        on[id] = on[id * 2] + on[id * 2 + 1];
}

void propagate(int id, int l, int r)
{
        lazy[id] = 0;
        lazy[id * 2] ^= 1;
        lazy[id * 2 + 1] ^= 1;

        int mid = (l + r) / 2;
        on[id * 2] = (mid - l + 1) - on[id * 2];
        on[id * 2 + 1] = (r - (mid + 1) + 1) - on[id * 2 + 1];
}

void update(int id, int l, int r, int x, int y)
{
        if(l > y || r < x) return;
        if(l >= x && r <= y){
                lazy[id] ^= 1;
                on[id] = (r - l + 1) - on[id];
                return;
        }
        if(lazy[id]) propagate(id, l, r);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, x, y);
        update(id * 2 + 1, mid + 1, r, x, y);
        on[id] = on[id * 2] + on[id * 2 + 1];
}

int query(int id, int l, int r, int x, int y)
{

        if(l > y || r < x) return 0;

        if(l >= x && r <= y) return on[id];

        if(lazy[id]) propagate(id, l, r);
        int mid = (l + r) / 2;
        return query(id * 2, l, mid, x, y) + query(id * 2 + 1, mid + 1, r, x, y);
}

int main()
{
        scanf("%d", &n);

        for(int i = 2; i <= n; i ++){
                scanf("%d", &x);
                adj[i].push_back(x);
                adj[x].push_back(i);
        }

        for(int i = 1; i <= n; i ++){
                scanf("%d", &arr[i]);
        }

        dfs(1, -1);

        build(1, 1, n);

        scanf("%d", &q);

        while(q --){
                scanf("%s %d", s, &x);
                if(s[0] == 'p'){
                        update(1, 1, n, idx[x], en[idx[x]]);
                }
                else{
                        printf("%d\n", query(1, 1, n, idx[x], en[idx[x]]));
                }
        }

        return 0;
}
