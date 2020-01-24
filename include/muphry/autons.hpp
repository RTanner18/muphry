#pragma once

#include "okapi/api.hpp"
#include "muphry/robot.hpp"

using namespace okapi;

class Auton{
    public:

    static bool flipout();
    static bool stack();
    static bool stackInTower();

    static bool simple();
    static bool small(bool red = true);
    static bool big(bool red = true);
    static bool skills();

    static bool test(bool turn = true);

    static bool random();

};