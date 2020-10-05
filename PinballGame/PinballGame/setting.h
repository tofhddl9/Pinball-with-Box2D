#pragma once

enum OBJECT_TYPE {
    REMOVABLE_BALL = 0x00,
    BALL = 0x01,
    WALL = 0x02,
    PISTON = 0x04,
    FLIPPER = 0x08,
    WINDMILL = 0x10,
    NAIL = 0x20,
    BUMPER = 0x40,
    REBOUNDER = 0x80,
    WORMHOLE = 0x100
};

const float BUMPER_ELASTICITY = 1.0f;
const float REBOUNDER_ELASTICITY = 1.5f;
const b2Vec2 REBOUNDER_CORRECTION = b2Vec2(0.0f, 2.0f);
const b2Vec2 WORMHOLE_DESTINATION = b2Vec2(-5.0f, 15.0f);