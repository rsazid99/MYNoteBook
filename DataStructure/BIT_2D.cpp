ll tree[2510][2510];

void update(int x , int y , int val){
    int y1;
    while (x <= 2505){
        y1 = y;
        while (y1 <= 2505){
            tree[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

ll query(int x, int y)
{
        ll sum = 0;
        while(x > 0){
                int y1 = y;
                while(y1 > 0){
                        sum += tree[x][y1];
                        y1 -= (y1 & -y1);
                }
                x -= (x & -x);
        }
        return sum;
}
