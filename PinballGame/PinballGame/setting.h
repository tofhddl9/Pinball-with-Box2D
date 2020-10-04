#pragma once

enum OBJECT_TYPE {
    BALL = 0x01,
    WALL = 0x02,
    PISTON = 0x04,
    FLIPPER = 0x08,
    WINDMILL = 0x10,
    NAIL = 0x20,
    BUMPER = 0x40,
};

const float BUMPER_ELASTICITY = 7.5f;