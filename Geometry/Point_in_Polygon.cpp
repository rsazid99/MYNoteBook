int n, m;

struct Point{
        ll x, y;
};
bool flag;
Point polygon[110];

bool onsegment(Point p, Point q, Point r)
{
        if(r.x >= min(p.x, q.x) && r.x <= max(p.x, q.x) && r.y >= min(p.y, q.y) && r.y <= max(p.y, q.y)) return true;
        return false;
}

// 0 --> a, b and c are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int orientation(Point a, Point b, Point c)
{
        ll val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if(val == 0) return 0;
        return (val > 0) ? 1 : 2;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if(o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0) return true;


        if(o1 == 0 && onsegment(p1, q1, p2)){
                flag = true;
                return true;
        }

        return false;
}

bool is_inside(Point p)
{
        // gcd(extreme.x - p.x, extreme.y - p.y) == 1
        Point extreme = {p.x + 1000000000 , p.y + 1000000000 + 1};

        int cnt = 0, i = 0;

        do{
                int nxt = (i + 1) % n;

                if(doIntersect(polygon[i], polygon[nxt], p, extreme)){
                        cnt ++;
                }
                i = nxt;
        } while(i != 0);

        if(flag) return true;

        if(cnt % 2 == 1) return true;

        return false;
}

int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int tt = 1;
        while(scanf("%d", &n)){
                if(n == 0) break;
                scanf("%d", &m);

                FORR(i, 0, n){
                        scanf("%lld %lld", &polygon[i].x, &polygon[i].y);
                }

                if(tt > 1) printf("\n");
                printf("Problem %d:\n", tt ++);
                while(m --){
                        Point p;
                        flag = false;
                        scanf("%lld %lld", &p.x, &p.y);
                        if(is_inside(p)) printf("Within\n");
                        else printf("Outside\n");
                }

        }

        return 0;

}
