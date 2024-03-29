//
// Created by Vio on 26.02.2021.
//
#include "geometry.h"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x_, int y_)
        : x(x_), y(y_) {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

Point::Point(const Point &other)
        : x(other.x), y(other.y) {}

Point &Point::operator=(const Point &other) {
    if (&other == this) {
        return *this;
    }
    x = other.x;
    y = other.y;
    return *this;
}

PolygonalChain::PolygonalChain(int n_points, Point *arr_points) {
    for (int i = 0; i < n_points; i++) {
        arr_point.push_back(arr_points[i]);
    }
}


PolygonalChain::PolygonalChain(const PolygonalChain &other) = default;

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) = default;

int PolygonalChain::getN() const {
    return arr_point.size();
}

double PolygonalChain::perimeter() const {
    int x0 = 0;
    int y0 = 0;
    int x1, y1;
    double perimeter = 0;
    if (arr_point.size() > 1) {
        x0 = arr_point[0].getX();
        y0 = arr_point[0].getY();
    }
    for (unsigned int i = 1; i < arr_point.size(); i++) {
        x1 = arr_point[i].getX();
        y1 = arr_point[i].getY();
        perimeter = perimeter + sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
        x0 = x1;
        y0 = y1;
    }
    return perimeter;
}

ClosedPolygonalChain::ClosedPolygonalChain(int n_points, Point *arr_points)
        : PolygonalChain(n_points, arr_points) {}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other) = default;

ClosedPolygonalChain &ClosedPolygonalChain::operator=(const ClosedPolygonalChain &other) = default;

double ClosedPolygonalChain::perimeter() const {
    double perimeter = PolygonalChain::perimeter();

    if (arr_point.size() > 2) {
        int x0 = arr_point[0].getX();
        int y0 = arr_point[0].getY();
        int x1 = arr_point[arr_point.size() - 1].getX();
        int y1 = arr_point[arr_point.size() - 1].getY();
        perimeter = perimeter + sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
    }

    return perimeter;
}

Polygon::Polygon(int n_points, Point *arr_points)
        : ClosedPolygonalChain(n_points, arr_points) {}

Polygon::Polygon(const Polygon &other) = default;

Polygon &Polygon::operator=(const Polygon &other) = default;

double Polygon::area() const {
    //fixed you dont need double
    int square = 0;
    if (arr_point.size() > 2) {
        int x0 = arr_point[0].getX();
        int y0 = arr_point[0].getY();
        int x1, y1;

        for (unsigned int i = 1; i < arr_point.size(); i++) {
            x1 = arr_point[i].getX();
            y1 = arr_point[i].getY();
            square = square + x0 * y1 - x1 * y0;
            x0 = x1;
            y0 = y1;
        }
        x0 = arr_point[0].getX();
        y0 = arr_point[0].getY();
        x1 = arr_point[arr_point.size() - 1].getX();
        y1 = arr_point[arr_point.size() - 1].getY();
        square = square + x0 * y1 - x1 * y0;


    }

    return abs(square) / 2.0;
}


Triangle::Triangle(int n_points, Point *arr_points)
        : Polygon(n_points, arr_points) {}

Triangle::Triangle(const Triangle &other)
        : Polygon(other) {}

Triangle &Triangle::operator=(const Triangle &other) = default;

bool Triangle::hasRightAngle() const {

    int length[3];
    length[0] = pow(arr_point[1].getX() - arr_point[0].getX(), 2) + (pow(arr_point[1].getY() - arr_point[0].getY(), 2));
    length[1] = pow(arr_point[2].getX() - arr_point[1].getX(), 2) + (pow(arr_point[2].getY() - arr_point[1].getY(), 2));
    length[2] = pow(arr_point[0].getX() - arr_point[2].getX(), 2) + (pow(arr_point[0].getY() - arr_point[2].getY(), 2));

    return (((length[0] + length[1] == length[2]) || (length[0] + length[2] == length[1]) ||
             (length[1] + length[2] == length[0])));

}

Trapezoid::Trapezoid(int n_points, Point *arr_points)
        : Polygon(n_points, arr_points) {}

Trapezoid::Trapezoid(const Trapezoid &other) = default;

Trapezoid &Trapezoid::operator=(const Trapezoid &other) = default;

double Trapezoid::height() const {
    double h = 2 * area();
    double len2base = sqrt(
            pow(arr_point[2].getX() - arr_point[1].getX(), 2) + (pow(arr_point[2].getY() - arr_point[1].getY(), 2)));
    double len4base = sqrt(
            pow(arr_point[0].getX() - arr_point[3].getX(), 2) + (pow(arr_point[0].getY() - arr_point[3].getY(), 2)));
    h = h / (len2base + len4base);
    return h;
}

RegularPolygon::RegularPolygon(int n_points, Point *arr_points)
        : Polygon(n_points, arr_points) {}

RegularPolygon::RegularPolygon(const RegularPolygon &other)
        : Polygon(other) {}

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &other) = default;

double RegularPolygon::perimeter() const {
    //fixed P shouldnt start with capital letter

    int x1, y1;
    double perimeter = 0;
    int x0 = arr_point[0].getX();
    int y0 = arr_point[0].getY();
    x1 = arr_point[1].getX();
    y1 = arr_point[1].getY();
    perimeter = perimeter + sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
    perimeter = perimeter * arr_point.size();


    return perimeter;
}

double RegularPolygon::pi = 3.1415926535;

double RegularPolygon::area() const {
    double square = 0;
    double perimeter = RegularPolygon::perimeter();
    if (arr_point.size() > 2) {
        square = perimeter * perimeter / (arr_point.size() * 4 * tan(pi / arr_point.size()));
    }

    return square;
}
