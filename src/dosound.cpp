// /*
//  * -------------
//  *  Dark Oberon
//  * -------------
//  *
//  * An advanced strategy game.
//  *
//  * Copyright (C) 2002 - 2005 Valeria Sventova, Jiri Krejsa, Peter Knut,
//  *                           Martin Kosalko, Marian Cerny, Michal Kral
//  *
//  * This program is free software; you can redistribute it and/or modify it
//  * under the terms of the GNU General Public License (see docs/gpl.txt) as
//  * published by the Free Software Foundation; either version 2 of the License,
//  * or (at your option) any later version.
//  */

// TODO: rewrite this to use SDL2_mixer instead of fmod

/**
 *  @file dosound.cpp
 *
 *  Sounds functions.
 *
 *  @author Peter Knut
 *
 *  @date 2004
 */

// #include "cfg.h"
// #include "doalloc.h"
#include "dosound.h"

//=========================================================================
// InitSound
//=========================================================================

bool InitSound(MIX_InitFlags mix)
{
  if (Mix_Init(mix) != mix)
  {
    std::cerr << "Mix_Init error: " << Mix_GetError() << std::endl;
    return false;
  }

  // maybe have this specified for TSTREAM/TSAMPLE?
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    std::cerr << "Mix_OpenAudio error: " << Mix_GetError() << std::endl;
    return false;
  }

  return true;
}

//=========================================================================
// TCHANNEL
//=========================================================================

void TCHANNEL::_SetVolume()
{
  if (channel >= 0 && vol_type != VT_NONE)
  {
    if (vol_type == VT_NORMAL)
    {
      // FSOUND_SetVolume(channel, volume);

      // Set relative volume change for a sound channel
      int current_vol = Mix_Volume(channel, -1); // Get the current volume
      int new_vol = current_vol + volume;

      // Ensure new volume stays in the 0-128 range
      new_vol = std::min(std::max(new_vol, 0), 128);
      Mix_Volume(channel, new_vol);
    }
    else
    {
      // FSOUND_SetVolumeAbsolute(channel, volume);

      // Set absolute volume directly
      Mix_Volume(channel, std::min(std::max(volume, 0), 128));
    }
  }
}

void TCHANNEL::SetVolume(T_BYTE vol)
{
  volume = vol;
  vol_type = VT_NORMAL;

  _SetVolume();
}

void TCHANNEL::SetVolumeAbsolute(T_BYTE vol)
{
  volume = vol;
  vol_type = VT_ABSOLUTE;

  _SetVolume();
}

bool TCHANNEL::IsPlaying()
{
  return channel >= 0 && Mix_Playing(channel);
  // FSOUND_IsPlaying(channel);
}

//=========================================================================
// TSAMPLE
//=========================================================================

TSAMPLE::TSAMPLE() : TCHANNEL()
{
  sample = NULL;
  // Set the callback function
  // Mix_ChannelFinished(ChannelFinished);
}

TSAMPLE::~TSAMPLE()
{
  if (sample)
  {
    Mix_FreeChunk(sample);
  }
}

bool TSAMPLE::Load(char *data, int size)
{
  if (sample)
  {
    Mix_FreeChunk(sample);
    channel = -1;
  }

  SDL_RWops *rw = SDL_RWFromConstMem(data, size);
  sample = Mix_LoadWAV_RW(rw, 1);

  // sample = FSOUND_Sample_Load(FSOUND_FREE, data, FSOUND_NORMAL | FSOUND_LOADMEMORY, 0, size);

  return (sample != NULL);
}

void TSAMPLE::SetMaxPlaybacks(int max)
{
  // Before playing, check if we can play another instance
  // if (currentPlaybacks < max)
  // {
  //   Mix_PlayChannel(-1, sample, 0);
  //   currentPlaybacks++;
  // }

  // TODO: later if needed

  if (sample)
  {
    // FSOUND_Sample_SetMaxPlaybacks(sample, max);
  }
}

// void TSAMPLE::ChannelFinished(int channel)
// {
//   currentPlaybacks--;
// }

void TSAMPLE::Play()
{
  if (sample)
  {
    // channel = FSOUND_PlaySound(FSOUND_FREE, sample);
    channel = Mix_PlayChannel(-1, sample, 0);
  }

  // set properties
  _SetVolume();
}

void TSAMPLE::Stop()
{
  if (channel >= 0)
  {
    // FSOUND_StopSound(channel);
    Mix_HaltChannel(channel);
  }
  channel = -1;
}

void TSAMPLE::SetLoop(bool lp)
{
  if (loop == lp)
  {
    return;
  }

  loop = lp;

  if (sample)
  {
    if (loop)
    {
      // FSOUND_Sample_SetMode(sample, FSOUND_LOOP_NORMAL);
      Mix_PlayChannel(channel, sample, -1);
    }
    else
    {
      // FSOUND_Sample_SetMode(sample, FSOUND_LOOP_OFF);
      Mix_PlayChannel(channel, sample, 0);
    }
  }
}

//=========================================================================
// TSTREAM
//=========================================================================

TSTREAM::~TSTREAM()
{
  Stop();
  if (stream)
  {
    // FSOUND_Stream_Close(stream);
    Mix_HaltMusic();
    Mix_FreeMusic(stream);
  }
}

// bool TSTREAM::Load(const char *file_name, int seek, int size)
bool TSTREAM::Load(const char *file_name)
{
  if (stream)
  {
    // FSOUND_Stream_Close(stream);
    Mix_HaltMusic();
    Mix_FreeMusic(stream);
    channel = -1;
  }

  // stream = FSOUND_Stream_Open(file_name, FSOUND_SIGNED | FSOUND_2D, seek, size);

  // should work?
  // stream = Mix_LoadMUS("../test_assets/A Step! Through the Fire and Flames_clean.mp3");
  stream = Mix_LoadMUS(file_name);
  return (stream != NULL);
}

void TSTREAM::Play()
{
  // should work, because there should only be one music track played anyway because for sounds there is TSAMPLE
  if (stream)
  {
    // channel = FSOUND_Stream_Play(FSOUND_FREE, stream);
    Mix_PlayMusic(stream, 0);
  }

  // set properties
  _SetVolume();
}

void TSTREAM::Stop()
{
  // if (stream && channel >= 0) FSOUND_Stream_Stop(stream);
  Mix_HaltMusic();
  channel = -1;
}

void TSTREAM::SetLoop(bool lp)
{
  if (loop == lp)
  {
    return;
  }

  loop = lp;

  if (stream)
  {
    if (loop)
    {
      // res = FSOUND_Stream_SetMode(stream, FSOUND_LOOP_NORMAL);
      Mix_HaltMusic();
      Mix_PlayMusic(stream, -1);
    }
    else
    {
      // FSOUND_Stream_SetMode(stream, FSOUND_LOOP_OFF);
      Mix_HaltMusic();
      Mix_PlayMusic(stream, 0);
    }
  }
}

bool TSTREAM::IsPlaying()
{
  return Mix_PlayingMusic();
}

void TSTREAM::SetVolume(T_BYTE vol)
{
  if (vol_type == VT_NORMAL)
  {
    // Set relative volume change for a sound channel
    int current_vol = Mix_VolumeMusic(-1); // Get the current volume
    int new_vol = current_vol + volume;

    // Ensure new volume stays in the 0-128 range
    new_vol = std::min(std::max(new_vol, 0), 128);
    Mix_VolumeMusic(new_vol);
  }
  else
  {
    // FSOUND_SetVolumeAbsolute(channel, volume);

    // Set absolute volume directly
    Mix_VolumeMusic(std::min(std::max(volume, 0), 128));
  }
}

//=========================================================================
// TMODULE
//=========================================================================

TMODULE::~TMODULE()
{
  if (mod)
  {
    Mix_HaltMusic();
    Mix_FreeMusic(mod);
    // FMUSIC_FreeSong(mod);
  }
}

bool TMODULE::Load(char *data, int size)
{
  if (mod)
  {
    Mix_HaltMusic();
    Mix_FreeMusic(mod);
    // FMUSIC_FreeSong(mod);
  }

  // mod = FMUSIC_LoadSongEx(data, 0, size, FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, NULL, 0);

  // should work, if data is a file name
  // TODO: maybe rewrite to work with SDL_RWops*
  mod = Mix_LoadMUS(data);

  // useless because looping is controlled by Mix_PlayMusic
  // if (mod)
  // {
  //   FMUSIC_SetLooping(mod, false);
  // }
  return (mod != NULL);
}

void TMODULE::Play()
{
  if (mod)
  {
    // FMUSIC_PlaySong(mod);
    Mix_PlayMusic(mod, 0); // 0 since load disables looping
  }
}

void TMODULE::Stop()
{
  if (mod)
  {
    // FMUSIC_StopSong(mod);
    Mix_HaltMusic();
  }
}

void TMODULE::SetVolume(T_BYTE vol)
{
  if (mod)
  {
    // FMUSIC_SetMasterVolume(mod, vol);
    Mix_VolumeMusic(vol);
  }
}

void TMODULE::SetVolumeAbsolute(T_BYTE vol)
{
  SetVolume(vol);
}

void TMODULE::SetLoop(bool lp)
{
  if (loop == lp)
    return;

  loop = lp;

  if (mod)
  {
    if (loop)
    {
      Mix_HaltMusic();
      Mix_PlayMusic(mod, -1);
    }
    else
    {
      Mix_HaltMusic();
      Mix_PlayMusic(mod, 0);
    }
    // FMUSIC_SetLooping(mod, lp);
  }
}

bool TMODULE::IsPlaying()
{
  // return mod && FMUSIC_IsPlaying(mod);
  return Mix_PlayingMusic();
}

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et: