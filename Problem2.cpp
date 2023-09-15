#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    int x;
    int y;
};

class ConvexHull {
public:
    ConvexHull(const std::vector<Point>& points) : points(points) {}

    static bool compare(Point p1, Point p2) {
        if (p1.x == p2.x)
            return p1.y < p2.y;
        return p1.x < p2.x;
    }

    int orientation(Point p, Point q, Point r) {
        int val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    }

    std::vector<Point> grahamScan() {
        int n = points.size();
        if (n < 3) return points;

        std::vector<Point> hull;

        int l = 0;
        for (int i = 1; i < n; i++)
            if (points[i].x < points[l].x)
                l = i;

        int p = l, q;
        do {
            hull.push_back(points[p]);

            q = (p + 1) % n;
            for (int i = 0; i < n; i++) {
                if (orientation(points[p], points[i], points[q]) == 2)
                    q = i;
            }

            p = q;

        } while (p != l);

        return hull;
    }

    double calculateArea(const std::vector<Point>& hull) {
        double area = 0;
        int n = hull.size();

        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (hull[i].x * hull[j].y - hull[j].x * hull[i].y);
        }

        return std::abs(area) / 2.0;
    }

    double largestArea() {
        std::sort(points.begin(), points.end(), compare);
        std::vector<Point> hull = grahamScan();
        return calculateArea(hull);
    }

private:
    std::vector<Point> points;
};

int main() {
    std::vector<Point> points = {{1, 2}, {2, 2}, {4, 5}, {3, 1}, {6, 8}};

    ConvexHull convexHull(points);
    double largestArea = convexHull.largestArea();
    std::cout << "Largest Area: " << largestArea << std::endl;

    return 0;
}
