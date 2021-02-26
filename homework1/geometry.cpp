//
// Created by Vio on 26.02.2021.
//
#include "geometry.h"
//spaces
Point::Point(){
    x=0;
    y=0;
}
Point::Point(int x_,int y_)
        :x(x_)
        ,y(y_)
{}
int Point::getX() const{
    return x;
}
int Point::getY() const{
    return y;
}
Point::Point(const Point& other)
        :x(other.x)
        ,y(other.y)
{}
 Point& Point::operator=(const Point& other){
    if(&other== this){
        return *this;
    }
    x=other.x;
    y=other.y;
}
PolygonalChain::PolygonalChain(int n_points,Point* arr_points)
        :n_point(n_points)
{
    for (int i=0;i<n_point;i++){
        arr_point.push_back(arr_points[i]);
    }
}
PolygonalChain::PolygonalChain(const PolygonalChain& other)
        :n_point(other.n_point)
        ,arr_point(other.arr_point)
{}
PolygonalChain& PolygonalChain::operator=(const PolygonalChain& other){
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
int PolygonalChain::getN() const{
    return n_point;
}
 double PolygonalChain::perimeter() const{
    int x0=0;
    int y0=0;
    int x1,y1;
    double P=0;
    if(n_point>1){
        x0=arr_point[0].getX();
        y0=arr_point[0].getY();
    }
    for(int i=1;i<n_point;i++){
        x1=arr_point[i].getX();
        y1=arr_point[i].getY();
        P=P+sqrt(pow((x1-x0),2) + pow((y1- y0),2));
        x0=x1;
        y0=y1;
    }
    return P;
}
ClosedPolygonalChain::ClosedPolygonalChain(int n_points,Point* arr_points)
        :PolygonalChain(n_points,arr_points)
{}
ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other)
        :PolygonalChain(other)
{}
ClosedPolygonalChain& ClosedPolygonalChain::operator=(const ClosedPolygonalChain& other){
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
double ClosedPolygonalChain::perimeter() const {
    double P=PolygonalChain::perimeter();
//       std::cout<<P;
    if(n_point>2){
        int x0=arr_point[0].getX();
        int y0=arr_point[0].getY();
        int x1=arr_point[n_point-1].getX();
        int y1=arr_point[n_point-1].getY();
        P=P+sqrt(pow((x1-x0),2) + pow((y1- y0),2));
    }
//      std::cout<<P;
    return P;
}
Polygon::Polygon(int n_points,Point* arr_points)
        :ClosedPolygonalChain(n_points,arr_points)
{}
Polygon::Polygon(const Polygon& other)
        :ClosedPolygonalChain(other)
{}
Polygon& Polygon::operator=(const Polygon& other){
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
double Polygon::area() const{
    double S=0;
    if(n_point>2){
        int x0=arr_point[0].getX();
        int y0=arr_point[0].getY();
        int x1,y1;

        for (int i=1;i<n_point;i++){
            x1=arr_point[i].getX();
            y1=arr_point[i].getY();
            S=S+x0*y1-x1*y0;
            x0=x1;
            y0=y1;
        }
        x0=arr_point[0].getX();
        y0=arr_point[0].getY();
        x1=arr_point[n_point-1].getX();
        y1=arr_point[n_point-1].getY();
        S=S+x0*y1-x1*y0;
        S=std::abs(S)/2;

    }

    return S;
}


Triangle::Triangle(int n_points,Point* arr_points)
        :Polygon(n_points,arr_points)
{}
Triangle::Triangle(const Triangle& other)
        :Polygon(other)
{}
Triangle& Triangle::operator=(const Triangle& other){
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
bool Triangle::hasRightAngle() const{
    double length[3];
    //sqrt and pow 2
    length[0]=sqrt(pow(arr_point[1].getX()-arr_point[0].getX(),2)+(pow(arr_point[1].getY()-arr_point[0].getY(),2)));
//        std::cout<<length[0];
    length[1]=sqrt(pow(arr_point[2].getX()-arr_point[1].getX(),2)+(pow(arr_point[2].getY()-arr_point[1].getY(),2)));
//        std::cout<<length[1];
    length[2]=sqrt(pow(arr_point[0].getX()-arr_point[2].getX(),2)+(pow(arr_point[0].getY()-arr_point[2].getY(),2)));
//        std::cout<<length[2];
//        std::cout<<pow(length[2],2);
//        std::cout<<pow(length[1],2);
//        std::cout<<pow(length[0],2);
//        if (length[2]*length[2]+length[1]*length[1]==length[0]*length[0]){
//            std::cout<<"lf";
//        }
    double squarelength0=length[0]*length[0];
    double squarelength1=length[1]*length[1];
    double squarelength2=length[2]*length[2];
    if((squarelength0+squarelength1==squarelength2)||(squarelength0+squarelength2==squarelength1)||(squarelength1+squarelength2==squarelength0)){
        return true;
    } else
        return false;
}
Trapezoid::Trapezoid(int n_points,Point* arr_points)
        :Polygon(n_points,arr_points)
{}
Trapezoid::Trapezoid(const Trapezoid& other)
        :Polygon(other)
{}

Trapezoid& Trapezoid::operator=(const Trapezoid& other){
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
double Trapezoid::height() const{
    double h=2*area();
    double len2base=sqrt(pow(arr_point[2].getX()-arr_point[1].getX(),2)+(pow(arr_point[2].getY()-arr_point[1].getY(),2)));
    double len4base=sqrt(pow(arr_point[0].getX()-arr_point[3].getX(),2)+(pow(arr_point[0].getY()-arr_point[3].getY(),2)));
    h=h/(len2base+len4base);
    return h;
}
RegularPolygon::RegularPolygon(int n_points,Point* arr_points)
        :Polygon(n_points,arr_points)
{}
RegularPolygon::RegularPolygon(const RegularPolygon& other)
        :Polygon(other)
{}
RegularPolygon& RegularPolygon::operator=(const RegularPolygon& other){
    //use from base class
    if(&other== this){
        return *this;
    }
    n_point=other.n_point;
    arr_point=other.arr_point;
}
