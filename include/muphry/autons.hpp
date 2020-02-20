#pragma once

#include "okapi/api.hpp"
#include "muphry/robot.hpp"

using namespace okapi;

class Auton{
    public:

    static bool alignCubes();
    static bool stackForward(const Vector& vector);
    static bool stackBackward(const Vector& vector);

    static bool small(bool red = true);
    static bool big(bool red = true);
    static bool skills();

    static bool test(bool turn = true);

    static bool moveToPoint(Vector vector);

    static bool random();

};
