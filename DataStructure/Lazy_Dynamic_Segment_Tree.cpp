#include<bits/stdc++.h>

#define maxn 100005
#define inf 1061109567

using namespace std;

int n, q, m, x, y, z, N, ty;
int b[maxn], sparse[maxn][20], deg[maxn];

struct node{
        int minn, promise;
        node* left;
        node* right;
        node(): left(NULL), right(NULL), promise(-1) {}
};



int getMin(int l, int r)
{
        int len = r - l + 1;
        int k = deg[len];
        return min(sparse[l][k], sparse[l + len - (1 << k)][k]);
}

int solve(int l, int r)
{
        int len = r - l + 1;

        if(len >= n) return getMin(0, n - 1);

        l %= n, r %= n;

        if(l <= r){
                return getMin(l, r);
        }
        else return min(getMin(l, n - 1), getMin(0, r));

}


void push(node* root, int l, int r)
{
        int mid = (l + r) >> 1;

        if(root -> left == NULL){
                root -> left = new node();
                root -> left -> minn = solve(l, mid);
        }
        if(root -> right == NULL){
                root -> right = new node();
                root -> right -> minn = solve(mid + 1, r);
        }

        if(root -> promise == -1) return;

        root -> left -> minn = root -> promise;
        root -> left -> promise = root -> promise;

        root -> right -> minn = root -> promise;
        root -> right -> promise = root -> promise;

        root -> promise = -1;
}


int query(node* root, int L, int R, int l, int r)
{
        if(R < l || L > r) return inf;

        if(L >= l && R <= r){
                return root -> minn;
        }
        push(root, L, R);

        int mid = (L + R) >> 1;

        return min( query(root -> left, L, mid, l, r), query(root -> right, mid + 1, R, l, r));

}

void update(node* root, int L, int R, int l, int r, int x)
{
        if(R < l || L > r) return;

        if(L >= l && R <= r){
                root -> minn = x;
                root -> promise = x;
                return;
        }

        int mid = (L + R) >> 1;
        push(root, L, R);

        update(root -> left, L, mid, l, r, x);
        update(root -> right, mid + 1, R, l, r, x);

        root -> minn =  min(root -> left -> minn, root -> right -> minn);
}

void build(node* root, int L, int R, int l, int r)
{
        if(l == r){
                root -> minn = getMin(l, l);
                return;
        }

        int mid = (L + R) >> 1;

        if(root -> left == NULL) root -> left = new node();

        if(l <= mid){
                build(root -> left, L, mid, l, min(mid, r));
        }
        else{
                root -> left -> minn = solve(L, mid);
        }

        if(root -> right == NULL) root -> right = new node();

        if(r > mid){
                build(root -> right, mid + 1, R, max(mid + 1, l), r);
        }
        else{
                root -> right -> minn = solve(mid + 1, R);
        }

        root -> minn =  min(root -> left -> minn, root -> right -> minn);

}




int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        deg[0] = -1;
        for(int i = 1; i <= 100000; i ++){
                deg[i] = deg[i - 1];
                if(!(i & (i - 1))){
                        ++deg[i];
                }
        }
        scanf("%d %d", &n, &m);

        for(int i = 0; i < n; i ++){
                scanf("%d", &b[i]);
                sparse[i][0] = b[i];
        }
        scanf("%d", &q);

        for(int r = 0; r + 1 < 20; r ++){
                for(int i = 0; i < n; i ++){
                        int t = min(i + (1 << r), n - 1);
                        sparse[i][r + 1] = min(sparse[i][r], sparse[t][r]);
                }
        }

        node* root = new node();

        root -> minn = getMin(0, n - 1);

        N = n * m;

        build(root, 0, N - 1, 0, n - 1);

        while(q --){
                scanf("%d", &ty);

                if(ty == 1){
                        scanf("%d %d %d", &x, &y, &z);
                        x --, y --;
                        update(root, 0, N - 1, x, y, z);
                }
                else if(ty == 2){
                        scanf("%d %d", &x, &y);
                        x --, y --;
                        printf("%d\n", query(root, 0, N - 1, x, y));
                }
        }


        return 0;

}
