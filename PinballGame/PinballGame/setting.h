#pragma once
#include <Box2D/Box2D.h>

//You just have to care about the release of b2World*
using body_ptr = b2Body*;

enum OBJECT_TYPE {
    BALL = 0x0001,
    WALL = 0x0002,
    PISTON = 0x0004,
    FLIPPER = 0x0008,

    WATER = 0x0010,
    WINDMILL = 0x0020,
    WANDERER = 0x0040,
    BUMPER_SMALL = 0x0080,
    BUMPER_LARGE = 0x0100,
    REBOUNDER = 0x0200,
    WORMHOLE = 0x0400,
    STAR_SMALL = 0x0800,
    STAR_LARGE = 0x1000,
};

enum BALL_PROPERTY {
    TRAVELING = 0x10000, // ball enters wormhole
    DIVING = 0x20000,    // ball first falls into the water
    FLOATING = 0x40000   // floating ball
};

const float BUMPER_ELASTICITY = 1.0f;
const float REBOUNDER_ELASTICITY = 1.5f;
const b2Vec2 REBOUNDER_CORRECTION = b2Vec2(0.0f, 2.0f);
const b2Vec2 WORMHOLE_DESTINATION = b2Vec2(15.8f, -13.0f);
//const b2Vec2 WORMHOLE_DESTINATION = b2Vec2(-9.4f, 25.5f);

const int SCORE_WINDMILL = 300;
const int SCORE_BUMPER_SMALL = 100;
const int SCORE_BUMPER_LARGE = 200;
const int SCORE_REBOUNDER = 500;
const int SCORE_WORMHOLE = 1000;
const int SCORE_STAR_SMALL = 500;
const int SCORE_STAR_LARGE = 10000;