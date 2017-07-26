struct fenwick{
        int tree[maxn];
        void update(int idx, int val, int n){
                while(idx <= n){
                        tree[idx] += val;
                        idx += idx & (-idx);
                }
        }
        int query(int idx)
        {
                int sum = 0;
                while(idx > 0){
                        sum += tree[idx];
                        idx -= idx & (-idx);
                }
                return sum;
        }
};
