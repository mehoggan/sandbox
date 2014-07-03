#include <iostream>
#include <fstream>
#include <cmath>

class Point {
    public:
    float   distance(Point const& rhs) const {
        float dx    = x - rhs.x;
        float dy    = y - rhs.y;
        return sqrt( dx * dx + dy * dy);
    }
    private:
        float   x;
        float   y;
        friend std::istream& operator>>(std::istream& stream, Point& point) {
            return stream >> point.x >> point.y;
        }
        friend std::ostream& operator<<(std::ostream& stream, Point const& point) {
            return stream << point.x << " " << point.y << " ";
        }
};

int main() {
    std::ifstream data( "init" );
    Point   first;
    data >> first;
    // The next point is the closest until we find a better one
    Point   closest;
    data >> closest;
    float   bestDistance = first.distance(closest);
    Point   next;
    while(data >> next) {
        float nextDistance  = first.distance(next);
        if (nextDistance < bestDistance) {
            bestDistance    = nextDistance;
            closest         = next;
        }
    }
    std::cout << "First(" << first << ") Closest(" << closest << ")\n";
}
    
