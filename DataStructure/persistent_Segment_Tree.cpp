int n, m, x, y, w;
int arr[maxn], tree[20 * maxn], L[20 * maxn], R[20 * maxn], root[maxn], NEW = 1;
vector<int> v;

void build(int id, int l, int r)
{
        if(l == r){
                tree[id] = 0;
                return;
        }
        int mid = (l + r) / 2;
        L[id] = NEW ++;
        R[id] = NEW ++;
        build(L[id], l, mid);
        build(R[id], mid + 1, r);
        tree[id] = tree[L[id]] + tree[R[id]];
}

int update(int id, int l, int r, int pos)
{
        int ID = NEW ++;
        if(l == r && l == pos){
                tree[ID] = 1;
                return ID;
        }
        int mid = (l + r) / 2;
        L[ID] = L[id]; R[ID] = R[id];
        if(pos <= mid) L[ID] = update(L[id], l, mid, pos);
        else R[ID] = update(R[id], mid + 1, r, pos);
        tree[ID] = tree[L[ID]] + tree[R[ID]];
        return ID;
}

int query(int ID, int id, int l, int r, int pos)
{
        if(l == r) return l;
        int mid = (l + r) / 2;
        int res = tree[L[ID]] - tree[L[id]];
        if(pos <= res) return query(L[ID], L[id], l, mid, pos);
        else return query(R[ID], R[id], mid + 1, r, pos - res);
}

int main()
{
        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        scanf("%d %d", &n, &m);
        FOR(i, 1, n){
                scanf("%d", &arr[i]);
                v.pb(arr[i]);
        }
        sort(ALL(v));
        FOR(i, 1, n){
                arr[i] = lower_bound(ALL(v), arr[i]) - v.begin() + 1;

        }
        build(0, 1, n);
        FOR(i, 1, n){
                root[i] = update(root[i - 1], 1, n, arr[i]);
        }
        while(m --){
                scanf("%d %d %d", &x, &y, &w);
                int ans = query(root[y], root[x - 1], 1, n, w);
                printf("%d\n", v[ans - 1]);
        }
        return 0;
}
