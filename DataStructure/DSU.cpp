
int pa[maxn], rnk[maxn];

int find(int x)
{
        if(pa[x] == x) return x;
        else return pa[x] = find(pa[x]);
}


void Union(int u, int v)
{
        int pu = find(u);
        int pv = find(v);

        if(pu == pv) return;

        if(rnk[pu] > rnk[pv]) pa[pv] = pu;
        else pa[pu] = pv;
        if(rnk[pa] == rnk[pu]) rnk[pv] = rnk[pv] + 1;
}
