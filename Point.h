//
// Created by lorenzo on 19/12/19.
//

#ifndef MIDTERM_PARALLEL_COMPUTING_POINT_H
#define MIDTERM_PARALLEL_COMPUTING_POINT_H

#include <vector>

class Point {

public:

    int getNumDimensions(){
        return values.size();
    }

    const std::vector<float> &getValues() const {
        return values;
    }

    void setValues(const std::vector<float> &newValues) {
        Point::values = newValues;
    }

private:

    std::vector<float> values;
};


#endif //MIDTERM_PARALLEL_COMPUTING_POINT_H
