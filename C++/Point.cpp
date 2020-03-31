#include "Point.h"


Point &Point::operator+=(const Point &otherPoint){
    for (int i = 0; i < this->getNumDimensions(); ++i) {
        this->values[i] += otherPoint.getValues()[i];

    }
    return *this;
}

Point Point::operator*(const float d) const {
    Point point(this->values);
    return point *= d;
}


Point &Point::operator*=(const float d) {
    for (long i = 0; i < getNumDimensions(); ++i)
        this->values[i] *= d;
    return *this;
}


Point Point::operator/(const float d) const {
    Point point(this->values);
    return point /= d;
}


Point &Point::operator/=(const float d) {
    for (long i = 0; i < getNumDimensions(); ++i)
        this->values[i] /= d;
    return *this;
}