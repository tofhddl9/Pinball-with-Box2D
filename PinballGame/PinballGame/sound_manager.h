#pragma once
#include "setting.h"
#include "sfx.h"
#include <map>

#define SOUND_FILE_BUMPER "../sound/collision_with_bumper.wav"
#define SOUND_FILE_WALL "../sound/collision_with_wall.wav"
#define SOUND_FILE_COIN "../sound/coin.wav"
#define SOUND_FILE_SHOOTING "../sound/shooting.wav"
#define SOUND_FILE_POURING "../sound/water_pour.wav"
#define SOUND_FILE_WORMHOLE "../sound/wormhole.wav"
#define SOUND_FILE_BACKGROUND "../sound/background.mp3"

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void PlaySFX(const int objectType);
    void PlayBackgroundMusic();

private:
    std::map<int, SFX*> effectSounds_;
    SFX* backgroundMusic_;
};