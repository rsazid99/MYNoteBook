int n;
struct Point{
        ll x, y;
        bool operator < (Point b) {
                if (y != b.y)
                        return y < b.y;
                return x < b.x;
        }

};
Point polygon[101], pivot;
// 0 --> a, b and c are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int orientation(Point a, Point b, Point c)
{
        ll val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if(val == 0) return 0;
        return (val > 0) ? 1 : 2;
}

int sqrDist(Point a, Point b)  {
        ll dx = a.x - b.x, dy = a.y - b.y;
        return dx * dx + dy * dy;
}

bool POLAR_ORDER(Point a, Point b)  {
        int order = orientation(pivot, a, b);
        if (order == 0)
                return sqrDist(pivot, a) < sqrDist(pivot, b);
        return (order == 2);
}


stack<Point> grahamScan(){
        stack<Point> hull;
        if(n < 3) return hull;
        int ind = 0;
        for (int i = 1; i < n; i++)
                if (polygon[i] < polygon[ind])
                        ind = i;


        Point temp = polygon[0];
        polygon[0] = polygon[ind];
        polygon[ind] = temp;

        pivot = polygon[0];
        sort(polygon + 1, polygon + n, POLAR_ORDER);

        hull.push(polygon[0]);
        hull.push(polygon[1]);
        hull.push(polygon[2]);

        for (int i = 3; i < n; i++) {
                Point top = hull.top();
                hull.pop();
                while (orientation(hull.top(), top, polygon[i]) != 2){
                        top = hull.top();
                        hull.pop();
                }
                hull.push(top);
                hull.push(polygon[i]);
        }
        return hull;
}




int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        while(scanf("%d", &n)){
                if(n == 0) break;

                FORR(i, 0, n) scanf("%lld %lld", &polygon[i].x, &polygon[i].y);

                stack<Point> hull = grahamScan();

                if(hull.size() == n) printf("No\n");
                else printf("Yes\n");
        }

        return 0;

}
