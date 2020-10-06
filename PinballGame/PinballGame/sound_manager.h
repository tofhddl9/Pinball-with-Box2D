#include "setting.h"
#include "sfx.h"
#pragma once

#define SOUND_FILE_BUMPER "../sound/collision_with_bumper.wav"
#define SOUND_FILE_WALL "../sound/collision_with_wall.wav"
#define SOUND_FILE_COIN "../sound/coin.wav"
#define SOUND_FILE_SHOOTING "../sound/shooting.wav"
#define SOUND_FILE_POURING "../sound/water_pour.wav"
#define SOUND_FILE_BACKGROUND "../sound/background.mp3"

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void PlaySFX(int objectType);
    void PlayBackgroundMusic();
    void Update();

private:
    SFX* backgroundMusic_;
    SFX* pistonSound_;
    SFX* wallSound_;
    SFX* bumperSound_;
    SFX* coinSound_;
    SFX* waterSound_;
};