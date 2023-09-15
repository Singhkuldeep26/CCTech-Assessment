#include <iostream>
#include <vector>

struct Point {
    double x;
    double y;
};

Point calculateCentroid(const std::vector<Point>& points) {
    double centroidX = 0.0;
    double centroidY = 0.0;
    int numPoints = points.size();

    for (const Point& point : points) {
        centroidX += point.x;
        centroidY += point.y;
    }

    centroidX /= numPoints;
    centroidY /= numPoints;

    Point centroid = {centroidX, centroidY};
    return centroid;
}

int main() {
    std::vector<Point> points = {{1.0, 2.0}, {2.0, 2.0}, {4.0, 5.0}, {3.0, 1.0}, {6.0, 8.0}};

    Point centroid = calculateCentroid(points);

    std::cout << "Centroid coordinates: (" << centroid.x << ", " << centroid.y << ")" << std::endl;

    return 0;
}
