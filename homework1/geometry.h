//
// Created by Vio on 18.02.2021.
//

#ifndef PR1_GEOMETRY_H
#define PR1_GEOMETRY_H
#include <vector>
#include <cmath>
#include <iostream>
using std::vector;

class Point{
private:
    int x;
    int y;
public:
    Point();
    Point(int x_,int y_);
    int getX() const;
    int getY() const;
    Point(const Point& other);
    Point& operator=(const Point& other);

};
class PolygonalChain{
protected:
    int n_point;
    vector<Point> arr_point;

public:
    explicit PolygonalChain(int n_points=0,Point* arr_points={});
    PolygonalChain(const PolygonalChain& other);
    PolygonalChain& operator=(const PolygonalChain& other);

    int getN() const;
    Point getPoint(int num) const{
        return Point(arr_point[num]);
    }
     virtual double perimeter() const;

};

class ClosedPolygonalChain: public PolygonalChain{
public:
    explicit ClosedPolygonalChain(int n_points=0,Point* arr_points={});
    ClosedPolygonalChain(const ClosedPolygonalChain& other);
    ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);
    double perimeter() const override;
};
class Polygon: public ClosedPolygonalChain{
public:
   Polygon(int n_points=0,Point* arr_points={});
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    double area() const;
};

class Triangle: public Polygon{
public:
    Triangle(int n_points=0,Point* arr_points={});
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);
    bool hasRightAngle() const;
};

class Trapezoid: public Polygon{
public:
    Trapezoid(int n_points=0,Point* arr_points={});
    Trapezoid(const Trapezoid& other);
    Trapezoid& operator=(const Trapezoid& other);
    double height() const;

};

//area and perimeter
class RegularPolygon: public Polygon{
public:
    RegularPolygon(int n_points=0,Point* arr_points={});
    RegularPolygon(const RegularPolygon& other);
    RegularPolygon& operator=(const RegularPolygon& other);

};




#endif //PR1_GEOMETRY_H
