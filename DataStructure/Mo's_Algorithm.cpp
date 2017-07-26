struct node{
        int L, R, idx;
        node(int _L, int _R, int _idx){
                L = _L;
                R = _R;
                idx = _idx;
        }
};
int n, q, x, y;
int arr[maxn], cnt[2000000];
vector<node> qe;
vector<pii> ans;
int block;

bool comp(node a, node b){
        if(a.L / block != b.L / block){
                return a.L / block < b.L / block;
        }
        return a.R < b.R;
}

int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();

        scanf("%d", &n);

        block = sqrt((double)n);

        FORR(i, 0, n){
                scanf("%d", &arr[i]);
        }

        scanf("%d", &q);

        FOR(i, 1, q){
                scanf("%d %d", &x, &y);
                qe.pb(node(x - 1, y - 1, i));
        }

        sort(qe.begin(), qe.end(), comp);
        int sum = 1;
        cnt[arr[0]] ++;
        int currL = 0, currR = 0;
        FORR(i, 0, q){
                //cout << qe[i].L << " " << qe[i].R << endl;
                while(currL > qe[i].L){
                        currL --;
                        cnt[arr[currL]] ++;
                        if(cnt[arr[currL]] == 1){
                                sum ++;
                        }
                }
                while(currL < qe[i].L){
                        cnt[arr[currL]] --;
                        if(cnt[arr[currL]] == 0){
                                sum --;
                        }
                        currL ++;
                }

                while(currR > qe[i].R){
                        cnt[arr[currR]] --;
                        if(cnt[arr[currR]] == 0){
                                sum --;
                        }
                        currR --;
                }

                while(currR < qe[i].R){
                        currR ++;
                        cnt[arr[currR]] ++;
                        if(cnt[arr[currR]] == 1){
                                sum ++;
                        }
                }
                ans.pb(pii(qe[i].idx, sum));
        }

        sort(ALL(ans));
        FORR(i, 0, ans.size()) printf("%d\n", ans[i].ss);

        return 0;
}
