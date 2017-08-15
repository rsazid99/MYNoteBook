#include <bits/stdc++.h>
using namespace std;

#define maxn 100010
#define ff first
#define ss second
#define MSET(a, x) memset(a, x, sizeof a)
#define FOR(i, a, b) for(int i = a; i <= b; i ++)
#define FORR(i, a, b) for(int i = a; i < b; i ++)
#define inf 1061109567
#define pb push_back

typedef pair <int, int> ii;

int n, m, x, y, z;
int dist[maxn];
vector<ii> adj[maxn];

void dijkstra(int src)
{
        MSET(dist, 63);
        dist[src] = 0;
        priority_queue<ii, vector<ii>, greater<ii> > pq;
        pq.push(ii(0, src));

        while(!pq.empty()){
                ii u = pq.top();
                pq.pop();

                if(u.ff != dist[u.ss]) continue;

                FORR(i, 0, adj[u.ss].size()){
                        int v = adj[u.ss][i].ff;
                        int we = adj[u.ss][i].ss;
                        if(dist[v] > dist[u.ss] + we){
                                dist[v] = dist[u.ss] + we;
                                pq.push(ii(dist[v], v));
                        }
                }
        }

}


int main()
{
        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int t;
        scanf("%d", &t);
		
        while(t --){
                scanf("%d %d", &n, &m);

                FOR(i, 1, m){
                        scanf("%d %d %d", &x, &y, &z);
                        adj[x].pb(ii(y, z));
                }

                dijkstra(1);

                int ans = dist[n];

                if(ans == inf) ans = -1;

                printf("%d\n", ans);

                FOR(i, 1, n){
                        adj[i].clear();
                }

        }

        return 0;
}
