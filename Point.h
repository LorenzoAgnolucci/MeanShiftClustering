//
// Created by lorenzo on 19/12/19.
//

#ifndef MEANSHIFTCLUSTERING_POINT_H
#define MEANSHIFTCLUSTERING_POINT_H

#include <utility>
#include <vector>

class Point {

public:
    explicit Point(std::vector<float> values) : values(std::move(values)) {}


    explicit Point(const int numDimensions){
        this->values = std::vector<float>(numDimensions, 0);
    }

    int getNumDimensions() const {
        return values.size();
    }

    const std::vector<float> &getValues() const {
        return values;
    }

    void setValues(const std::vector<float> &newValues) {
        Point::values = newValues;
    }

    Point &operator+=(const Point &otherPoint);

    Point operator*(float d) const;

    Point &operator*=(float d);

    Point operator/(float d) const;

    Point &operator/=(float d);

private:

    std::vector<float> values;
};


#endif //MEANSHIFTCLUSTERING_POINT_H
