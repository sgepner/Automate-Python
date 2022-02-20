
typedef struct{
    double x;
    double y;
} Point;

Point make_Point(double x, double y)
{
    Point rp;
    rp.x = x;
    rp.y = y;
    return rp;
}

Point copy_Point(Point *p)
{
    Point rp;
    rp.x = p->x;
    rp.y = p->y;
    return rp;
}

void move_Point(Point *p, double x, double y)
{
    p->x += x;
    p->y += y;
}