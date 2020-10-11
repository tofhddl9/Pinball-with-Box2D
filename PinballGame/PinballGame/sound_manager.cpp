#include "sound_manager.h"

SoundManager::SoundManager()
{
    SFX::Init();

    backgroundMusic_ = new SFX(SOUND_FILE_BACKGROUND, true);

    effectSounds_[PISTON] = new SFX(SOUND_FILE_SHOOTING, false);

    effectSounds_[FLIPPER] = new SFX(SOUND_FILE_WALL, false);
    effectSounds_[WINDMILL] = new SFX(SOUND_FILE_WALL, false);
    effectSounds_[WANDERER] = new SFX(SOUND_FILE_WALL, false);

    effectSounds_[REBOUNDER] = new SFX(SOUND_FILE_BUMPER, false);
    effectSounds_[BUMPER_SMALL] = new SFX(SOUND_FILE_BUMPER, false);
    effectSounds_[BUMPER_LARGE] = new SFX(SOUND_FILE_BUMPER, false);

    effectSounds_[STAR_SMALL] = new SFX(SOUND_FILE_COIN, false);
    effectSounds_[STAR_LARGE] = new SFX(SOUND_FILE_COIN, false);

    effectSounds_[WATER] = new SFX(SOUND_FILE_POURING, false);

    effectSounds_[WORMHOLE] = new SFX(SOUND_FILE_WORMHOLE, false);
}

SoundManager::~SoundManager()
{
    delete backgroundMusic_;
   
    for (auto it = effectSounds_.begin(); it != effectSounds_.end(); ++it) {
        delete(it->second);
    }
    SFX::Release();
}

void SoundManager::PlaySFX(const int objectType)
{
    if (effectSounds_[objectType] != nullptr)
        effectSounds_[objectType]->Play();
}

void SoundManager::PlayBackgroundMusic()
{
    backgroundMusic_->Play();
}

