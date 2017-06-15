struct Point{
        ll x, y;
};
Point A, B, C, D;

ll sqrDist(Point a, Point b)  {
        ll dx = a.x - b.x, dy = a.y - b.y;
        return dx * dx + dy * dy;
}
bool onsegment(Point p, Point q, Point r)
{
        if(r.x >= min(p.x, q.x) && r.x <= max(p.x, q.x) && r.y >= min(p.y, q.y) && r.y <= max(p.y, q.y)) return true;
        return false;
}

int orientation(Point a, Point b, Point c)
{
        ll val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if(val == 0) return 0;
        return (val > 0) ? 1 : 2;
}

int is_perpendicular(Point a, Point b, Point c)
{
        int p = b.y - a.y;
        int q = b.x - a.x;
        int r = c.y - b.y;
        int s = c.x - b.x;
        if(p * r == - 1 * q * s) return 1;
        else return 0;
}

int is_parallel(Point a, Point b, Point c)
{
        int p = b.y - a.y;
        int q = b.x - a.x;
        int r = c.y - b.y;
        int s = c.x - b.x;
        if(p * s == q * r) return 1;
        else return 0;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if(o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0) return true;


        if(o1 == 0 && onsegment(p1, q1, p2)) return true;
        if(o2 == 0 && onsegment(p1, q1, q2)) return true;
        if(o3 == 0 && onsegment(p2, q2, p1)) return true;
        if(o4 == 0 && onsegment(p2, q2, q1)) return true;

        return false;
}
