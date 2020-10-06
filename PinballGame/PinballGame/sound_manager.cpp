#include "sound_manager.h"

SoundManager::SoundManager()
{
    SFX::Init();

    backgroundMusic_ = new SFX(SOUND_FILE_BACKGROUND, true);
    pistonSound_ = new SFX(SOUND_FILE_SHOOTING, false);
    wallSound_ = new SFX(SOUND_FILE_WALL, false);
    bumperSound_ = new SFX(SOUND_FILE_BUMPER, false);
    coinSound_ = new SFX(SOUND_FILE_COIN, false);
    waterSound_ = new SFX(SOUND_FILE_POURING, false);
}

SoundManager::~SoundManager()
{
    delete backgroundMusic_;
    delete wallSound_;
    delete bumperSound_;
    delete coinSound_;

    SFX::Release();
}

void SoundManager::PlaySFX(int objectType)
{
    switch (objectType) {
    case PISTON: {
        pistonSound_->Play();
        break;
    }
    case FLIPPER: {}
    case WINDMILL: {}
    case WANDERER: {
        wallSound_->Play();
        break;
    }
    case REBOUNDER: {}
    case BUMPER_SMALL: {}
    case BUMPER_LARGE: {
        bumperSound_->Play();
        break;
    }
    case STAR_SMALL: {}
    case STAR_LARGE: {
        coinSound_->Play();
        break;
    }
    case WATER: {
        waterSound_->Play();
        break;
    }
    }
}

void SoundManager::PlayBackgroundMusic()
{
    backgroundMusic_->Play();
}

void SoundManager::Update()
{
    backgroundMusic_->Update();
}
