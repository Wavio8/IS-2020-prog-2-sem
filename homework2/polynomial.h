//
// Created by Vio on 20.03.2021.
//

#ifndef PROGA2LAB_POLYNOMIAL_H
#define PROGA2LAB_POLYNOMIAL_H
#include <sstream>
using namespace std;

class Polynomial{
private:
    int *array;
    int min_exponent;
    int max_exponent;
public:
    Polynomial();
    Polynomial(int min,int max,const int* arr);
    Polynomial(const Polynomial &other);
    Polynomial &operator=(const Polynomial &other);
    friend bool operator==(const Polynomial& lhs,const Polynomial& rhs);
    friend bool operator!=(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator+=( Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator-=( Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator+(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs,int value);
    friend Polynomial operator*(int value,const Polynomial& rhs);
    Polynomial& operator*=(const int value);
    friend Polynomial operator*(const Polynomial& lhs,const Polynomial& rhs);
    Polynomial& operator*=(const Polynomial& rhs);
    friend Polynomial operator/(const Polynomial& lhs,int value);
    Polynomial& operator/=(const int value);
    int operator[](int value) const;
    int& operator[](int value);
    double get(int value);


    friend std::istream& operator>>(std::istream& stream, Polynomial &polynom);
    friend ostream& operator<<(ostream &stream, const Polynomial &polynom);



    ~Polynomial();

};

istream& operator>>(istream& stream, Polynomial &polynom);
ostream& operator<<(ostream &stream, const Polynomial &polynom);
#endif //PROGA2LAB_POLYNOMIAL_H
