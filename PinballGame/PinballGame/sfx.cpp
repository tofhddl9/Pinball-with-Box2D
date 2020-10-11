#include "sfx.h"

FMOD_SYSTEM* SFX::g_sound_system;

SFX::SFX(const char* path, bool loop) {
    if (loop) {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &sound_);
    }
    else {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &sound_);
    }

    channel_ = nullptr;
}

SFX::~SFX()
{
    FMOD_Sound_Release(sound_);
    delete channel_;
}


int SFX::Init() {
    FMOD_System_Create(&g_sound_system);
    FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, NULL);

    return 0;
}

int SFX::Release() {
    FMOD_System_Close(g_sound_system);
    FMOD_System_Release(g_sound_system);

    return 0;
}

int SFX::Play() {
    FMOD_System_PlaySound(g_sound_system, sound_, NULL, false, &channel_);

    return 0;
}

int SFX::Pause() {
    FMOD_Channel_SetPaused(channel_, true);

    return 0;
}

int SFX::Resume() {
    FMOD_Channel_SetPaused(channel_, false);

    return 0;
}

int SFX::Stop() {
    FMOD_Channel_Stop(channel_);

    return 0;
}

int SFX::Update() {
    FMOD_Channel_IsPlaying(channel_, &isPlaying_);

    if (isPlaying_) {
        FMOD_System_Update(g_sound_system);
    }

    return 0;
}