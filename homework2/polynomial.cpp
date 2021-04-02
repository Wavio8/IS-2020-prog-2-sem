//
// Created by Vio on 21.03.2021.
//
#include "polynomial.h"
#include <sstream>
#include <iostream>
#include "cmath"

using namespace std;

Polynomial::Polynomial() {
    max_exponent = 0;
    min_exponent = 0;
    array = new int[1];
    array[0] = 0;
}

Polynomial::Polynomial(int min, int max, const int *arr)
        : min_exponent(min), max_exponent(max) {
    array = new int[max - min + 1];
    for (int i = 0; i < max - min + 1; i++) {
        array[i] = arr[i];
    }
}

Polynomial::Polynomial(const Polynomial &other)
        : min_exponent(other.min_exponent), max_exponent(other.max_exponent) {
    array = new int[other.max_exponent - other.min_exponent + 1];
    for (int i = 0; i < other.max_exponent - min_exponent + 1; i++) {
        array[i] = other.array[i];
    }
}

//-------------   =   --------------------
Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (&other == this) {
        return *this;
    }
    min_exponent = other.min_exponent;
    max_exponent = other.max_exponent;
    delete[] array;
    array = new int[other.max_exponent - other.min_exponent + 1];
    for (int i = 0; i < other.max_exponent - min_exponent + 1; i++) {
        array[i] = other.array[i];
    }
    return *this;
}

//-----------   ==   ---------------------
bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
    for (int i = 0; i < lhs.max_exponent - lhs.min_exponent + 1; i++) {
        if (((lhs.max_exponent != rhs.max_exponent) || (lhs.min_exponent != rhs.min_exponent)) && (lhs.array[i] != 0))
            if ((lhs.array[i] != rhs.array[i]))
                return false;
    }

    return true;
}

//-----------   !=    ---------------------
bool operator!=(const Polynomial &lhs, const Polynomial &rhs) {
    return !(lhs == rhs);
}

//-----------   +=    ---------------------
Polynomial operator+=(Polynomial &lhs, const Polynomial &rhs) {

    if ((lhs.min_exponent <= rhs.min_exponent) && (lhs.max_exponent >= rhs.max_exponent)) {

        int now_power = lhs.min_exponent;

        int i_rhs = 0;
        for (int i = 0; i < lhs.max_exponent - lhs.min_exponent + 1; i++, now_power++) {
            if ((rhs.min_exponent <= now_power) && (rhs.max_exponent >= now_power)) {
                lhs.array[i] = lhs.array[i] + rhs.array[i_rhs];
                i_rhs++;
            }

        }

       
    } else {
        int *add_array = new int[max(lhs.max_exponent, rhs.max_exponent) - min(lhs.min_exponent, rhs.min_exponent) + 1];
        int now_power = min(lhs.min_exponent, rhs.min_exponent);
        int i_rhs = 0;
        int i_lhs = 0;
        for (int i = 0; i < max(lhs.max_exponent, rhs.max_exponent) - min(lhs.min_exponent, rhs.min_exponent) +
                            1; i++, now_power++) {
            if ((rhs.min_exponent <= now_power && rhs.max_exponent >= now_power) &&
                (lhs.min_exponent <= now_power && lhs.max_exponent >= now_power)) {
                add_array[i] = lhs.array[i_lhs] + rhs.array[i_rhs];
                i_rhs++;
                i_lhs++;
            } else if (lhs.min_exponent <= now_power && lhs.max_exponent >= now_power) {
                add_array[i] = lhs.array[i_lhs];
                i_lhs++;
            } else if (rhs.min_exponent <= now_power && rhs.max_exponent >= now_power) {
                add_array[i] = rhs.array[i_rhs];
                i_rhs++;
            }

        }

        lhs = Polynomial(min(lhs.min_exponent, rhs.min_exponent), max(lhs.max_exponent, rhs.max_exponent), add_array);
    }

    return lhs;
}

//---------------   -=   ----------------
Polynomial operator-=(Polynomial &lhs, const Polynomial &rhs) {
    if ((lhs.min_exponent <= rhs.min_exponent) && (lhs.max_exponent >= rhs.max_exponent)) {
        int now_power = lhs.min_exponent;
        int i_rhs = 0;
        for (int i = 0; i < lhs.max_exponent - lhs.min_exponent + 1; i++, now_power++) {
            if (rhs.min_exponent >= now_power && rhs.max_exponent <= now_power) {
                lhs.array[i] = lhs.array[i] - rhs.array[i_rhs];
                i_rhs++;
            }
        }

    } else {
        int *add_array = new int[max(lhs.max_exponent, rhs.max_exponent) - min(lhs.min_exponent, rhs.min_exponent) + 1];
        int now_power = min(lhs.min_exponent, rhs.min_exponent);
        int i_rhs = 0;
        int i_lhs = 0;
        for (int i = 0; i < max(lhs.max_exponent, rhs.max_exponent) - min(lhs.min_exponent, rhs.min_exponent) +
                            1; i++, now_power++) {
            if ((rhs.min_exponent >= now_power && rhs.max_exponent <= now_power) &&
                (lhs.min_exponent >= now_power && lhs.max_exponent <= now_power)) {
                add_array[i] = lhs.array[i_lhs] - rhs.array[i_rhs];
                i_rhs++;
                i_lhs++;
            } else if (lhs.min_exponent >= now_power && lhs.max_exponent <= now_power) {
                add_array[i] = lhs.array[i_lhs];
                i_lhs++;
            } else if (rhs.min_exponent >= now_power && rhs.max_exponent <= now_power) {
                add_array[i] = -rhs.array[i_rhs];
                i_rhs++;
            }
        }
        lhs = Polynomial(min(lhs.min_exponent, rhs.min_exponent), max(lhs.max_exponent, rhs.max_exponent), add_array);
    }
    return lhs;
}

//-------------   +    -----------------
Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial addition;
    addition = lhs;
    addition += rhs;

    return addition;
}

//-------------   -    ---------------
Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial subtraction;
    subtraction = lhs;
    subtraction -= rhs;
    return subtraction;
}

//-------------   -u -------------------
Polynomial operator-(const Polynomial &rhs) {
    Polynomial minus_rhs;
    minus_rhs = rhs;
    for (int i = 0; i < rhs.max_exponent - rhs.min_exponent + 1; i++) {
        minus_rhs.array[i] = minus_rhs.array[i] * (-1);
    }
    return minus_rhs;
}

//------  *(value) -----------------
Polynomial operator*(const Polynomial &lhs, int value) {
    Polynomial multi;
    multi = lhs;
    for (int i = 0; i < multi.max_exponent - multi.min_exponent + 1; i++) {
        multi.array[i] = multi.array[i] * value;
    }
    return multi;
}

Polynomial operator*(int value, const Polynomial &rhs) {
    return rhs * value;
}

//---------- *= ----------------
Polynomial &Polynomial::operator*=(const int value) {
    for (int i = 0; i < max_exponent - min_exponent + 1; i++) {
        array[i] = array[i] * value;
    }
    return *this;
}

//----------   *   --------
Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
    int size_array = lhs.max_exponent + rhs.max_exponent - lhs.min_exponent - rhs.min_exponent + 1;
    int coefficient;
    Polynomial multi(lhs.min_exponent + rhs.min_exponent, lhs.max_exponent + rhs.max_exponent, new int[size_array]);
    for (int i = 0; i < size_array; i++) {
        coefficient = 0;
        int j = 0;
        while ((j <= i) && (j < lhs.max_exponent - lhs.min_exponent + 1)) {
            if ((i - j >= 0) && (i - j < rhs.max_exponent - rhs.min_exponent + 1)) {
                coefficient = coefficient + lhs.array[j] * rhs.array[i - j];
            }
            j++;
        }
        multi.array[i] = coefficient;
    }
    return multi;
}

Polynomial &Polynomial::operator*=(const Polynomial &rhs) {
    *this = *this * rhs;
    return *this;
}

Polynomial operator/(const Polynomial &lhs, int value) {
    Polynomial division;
    division = lhs;
    for (int i = 0; i < lhs.max_exponent - lhs.min_exponent + 1; i++) {
        division.array[i] = lhs.array[i] / value;
    }
    int flag_max = 0;
    int now_power = lhs.min_exponent;
    int flag_min = 0;
    for (int i = 0; i < lhs.max_exponent - lhs.min_exponent + 1; i++, now_power++) {
        if (division.array[i] != 0) {
            division.min_exponent = now_power;
            flag_min = 1;
            break;
        }
    }

    now_power = lhs.max_exponent;
    for (int i = lhs.max_exponent - lhs.min_exponent; i >= 0; i--, now_power--) {
        if (division.array[i] != 0) {
            division.max_exponent = now_power;
            flag_max = 1;
            break;
        }
    }
    if (flag_min == 0 || flag_max == 0) {
        division.max_exponent = 0;
        division.min_exponent = 0;
    }
    Polynomial div;
    div.array = new int[division.max_exponent - division.min_exponent + 1];
    div.max_exponent = division.max_exponent;
    div.min_exponent = div.min_exponent;
    for (int i = 0; i < division.max_exponent - division.min_exponent + 1; i++) {
        div.array[i] = division.array[division.min_exponent - lhs.min_exponent + i];
    }

    return div;

}

Polynomial &Polynomial::operator/=(const int value) {
    *this = *this / value;
    return *this;
}

int Polynomial::operator[](int value) const {
    if (value <= max_exponent && value >= min_exponent)
        return array[value - min_exponent];

    return 0;

}

int &Polynomial::operator[](int value) {
    if (value > max_exponent) {
        Polynomial new_polinom;
        new_polinom.array = new int[value - min_exponent + 1];
        for (int i = 0; i < max_exponent - min_exponent + 1; i++) {
            new_polinom.array[i] = array[i];
        }
        for (int i = max_exponent - min_exponent + 1; i < value - min_exponent + 1; i++) {
            new_polinom.array[i] = 0;
        }

        new_polinom.min_exponent = min_exponent;
        new_polinom.max_exponent = value;
        *this = new_polinom;
    }
    if (value < min_exponent) {
        Polynomial new_polinom;
        new_polinom.array = new int[max_exponent - value + 1];
        for (int i = 0; i < min_exponent - value; i++) {
            new_polinom.array[i] = 0;
        }
        int c = 0;
        for (int i = min_exponent - value; i < value + max_exponent + 1; i++, c++) {
            new_polinom.array[i] = array[c];
        }

        new_polinom.min_exponent = value;
        new_polinom.max_exponent = max_exponent;
        *this = new_polinom;
    }
    return array[value - min_exponent];

}

double Polynomial::get(int value) {
    double res = 0;
    for (int i = 0; i < max_exponent - min_exponent + 1; i++) {
        res = res + array[i] * pow(value, min_exponent + i);
    }

    return res;
}


istream &operator>>(istream &stream, Polynomial &polynom) {
    stream >> polynom.min_exponent;
    stream >> polynom.max_exponent;
    for (int i = 0; i < polynom.max_exponent - polynom.min_exponent + 1; i++) {
        stream >> polynom.array[i];
    }
    return stream;
}

ostream &operator<<(ostream &stream, const Polynomial &polynom) {
    int now_power = polynom.max_exponent;
    int count = 0;
    for (int i = polynom.max_exponent - polynom.min_exponent; i >= 0; i--, now_power--) {
        if (polynom.array[i] > 0 && now_power != polynom.max_exponent) {
            stream << "+";
        }
        if (polynom.array[i] != 1 && polynom.array[i] != -1 && now_power != 0 && polynom.array[i] != 0) {
            stream << polynom.array[i] << "x";
        } else if (polynom.array[i] == 1 && now_power != 0) {
            stream << "x";
        } else if (polynom.array[i] == -1 && now_power != 0) {
            stream << "-x";
        }
        if (now_power == 0 && polynom.array[i] != 0) {
            stream << polynom.array[i];
        }
        if (polynom.array[i] != 0 && now_power != 1 && now_power != 0) {
            stream << "^" << now_power;
        }
        if (polynom.array[i] == 0) {
            count = count + 1;
        }
    }
    if (count == polynom.max_exponent - polynom.min_exponent + 1) {
        stream << "0";
    }
    return stream;
}

Polynomial::~Polynomial() {
    delete[] array;
}


