#include <fmod.h>
#include "setting.h"
#pragma once

class SFX {
public:
    SFX();
    SFX(const char* path, bool loop);
    ~SFX();

    static int Init();
    static int Release();

    int Play();
    int Pause();
    int Resume();
    int Stop();
    int Update();

private:
    static FMOD_SYSTEM* g_sound_system;

    FMOD_SOUND* sound_;
    FMOD_CHANNEL* channel_;

    FMOD_BOOL isPlaying_;
};
