nt n, q, r, key, ty, x, y, z, no, pa[3 * maxn], mxdep = -1, encr[3 * maxn];
vector<int> adj[3 * maxn], dep[3 * maxn];

struct node{
        node *next[2];
        node(){
                next[0] = NULL;
                next[1] = NULL;
        }
}*root[300010];

map<int, int> id;



void dfs(int u, int p, int depth)
{
        dep[depth].pb(u);
        mxdep = max(mxdep, depth);
        pa[u] = p;

        FORR(i, 0, adj[u].size()){
                int v = adj[u][i];
                if(v == p) continue;
                dfs(v, u, depth + 1);
        }
}


void insert1(node* cur, node* past, int mask)
{
        for(int i = 31; i >= 0; i --){
                int id = (mask >> i) & 1;
                if(cur -> next[id] == NULL){
                        cur -> next[id] = new node();
                }
                int opo = 1 - id;
                if(past != NULL && past -> next[opo] != NULL) cur -> next[opo] = past -> next[opo];
                cur = cur -> next[id];
                if(past != NULL) past = past -> next[id];
        }
}
int get_min(node* cur, int mask)
{

    int ans = 0;
    for(int i = 31;i >= 0;i --){
        int id = (( mask >> i) & 1);
        if(cur -> next[id]){
            cur = cur -> next[id];
        }else{
            cur = cur -> next[id ^ 1];
            ans = ans | (1 << i);
        }
    }
    return ans;
}


int get_max(node* cur, int mask)
{

    int ans = 0;
    for(int i = 31;i >= 0;i --){
        int id = ((mask >> i) & 1) ^ 1;
        if(cur ->  next[id]){
            ans = ans | (1 << i);
            cur = cur -> next[id];
        }else{
            cur = cur -> next[id ^ 1];
        }
    }
    return ans;
}



int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        scanf("%d %d", &n, &q);

        scanf("%d %d", &r, &key);

        if(!id[r]) id[r] = ++ no;
        root[id[r]] = new node();
        root[0] = new node();
        insert1(root[id[r]], root[0], key);

        FORR(i, 1, n){
                scanf("%d %d %d", &x, &y, &z);
                if(!id[x]) id[x] = ++ no;
                if(!id[y]) id[y] = ++ no;
                adj[id[x]].pb(id[y]);
                adj[id[y]].pb(id[x]);
                encr[id[x]] = z;

        }
        dfs(id[r], -1, 0);

        FOR(i, 1, mxdep){
                FORR(j, 0, dep[i].size()){
                        int u = dep[i][j];
                        root[u] = new node();
                        insert1(root[u], root[pa[u]], encr[u]);
                }
        }


        int last_ans = 0;
        while(q --){
                scanf("%d", &ty);

                ty ^= last_ans;

                if(ty == 0){
                        scanf("%d %d %d", &x, &y, &z);

                        x ^= last_ans;
                        y ^= last_ans;
                        z ^= last_ans;

                        if(!id[y]) id[y] = ++ no;
                        root[id[y]] = new node();
                        insert1(root[id[y]], root[id[x]], z);
                }
                else{
                        scanf("%d %d", &x, &y);
                        x ^= last_ans;
                        y ^= last_ans;

                        int mi = get_min(root[id[x]], y);
                        int mx = get_max(root[id[x]], y);
                        cout << mi <<" " << mx << endl;

                        last_ans = mi ^ mx;
                }

        }

        return 0;

}
