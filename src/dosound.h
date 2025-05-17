/*
 * -------------
 *  Dark Oberon
 * -------------
 *
 * An advanced strategy game.
 *
 * Copyright (C) 2002 - 2005 Valeria Sventova, Jiri Krejsa, Peter Knut,
 *                           Martin Kosalko, Marian Cerny, Michal Kral
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (see docs/gpl.txt) as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 */

/**
 *  @file dosound.h
 *
 *  Sound declarations and methods.
 *
 *  @author Peter Knut (original), Fabian Rubin
 *
 *  @date 2004, 2025
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <algorithm>

#include "cfg.h"
// #include "doalloc.h"
#include "dosimpletypes.h"
#include "dologs.h"


// TODO: Maybe use SDL Mixer X (https://github.com/WohlSoft/SDL-Mixer-X),
// an extended version of SDL_mixer that supports multiple parallel music streams and additional features,
// to be able to play several tracks at once if needed.

//=========================================================================
// Definitions
//=========================================================================

#define SND_MAX_PLAYBACKS 2
#define SND_MAX_CHANNELS 64
#define SND_MIXRATE 32000

enum TSOUND_FORMAT
{
  SF_WAV,
  SF_MP2,
  SF_MP3,
  SF_OGG,
  SF_RAW,
  SF_MOD,
  SF_S3M,
  SF_XM,
  SF_IT,
  SF_MID,
  SF_RMI,
  SF_SGT
};

enum TVOLUME_TYPE
{
  VT_NONE,
  VT_NORMAL,
  VT_ABSOLUTE
};

//=========================================================================
// Sounds
//=========================================================================

class TSOUND
{
public:
  char *id;
  TSOUND_FORMAT format;
  // T_BYTE volume;
  int volume; // use int for now because i want this to work, not save memory
  TVOLUME_TYPE vol_type;
  bool loop;

  virtual void Play() = 0;
  virtual void Stop() = 0;

  virtual void SetVolume(T_BYTE vol) = 0;
  virtual void SetVolumeAbsolute(T_BYTE vol) = 0;
  virtual void SetLoop(bool lp) = 0;

  virtual bool IsPlaying() = 0;

  TSOUND()
  {
    id = NULL;
    format = SF_WAV;
    volume = 0;
    vol_type = VT_NONE;
    loop = false;
  }
  virtual ~TSOUND()
  {
    if (id)
      delete[] id;
  }
};

class TCHANNEL : public TSOUND
{
public:
  int channel;

  virtual void SetVolume(T_BYTE vol);
  virtual void SetVolumeAbsolute(T_BYTE vol);

  virtual bool IsPlaying();

  TCHANNEL() : TSOUND() { channel = -1; }
  virtual ~TCHANNEL() {};

protected:
  void _SetVolume();
};

class TSAMPLE : public TCHANNEL
{
public:
  // FSOUND_SAMPLE *sample;
  Mix_Chunk *sample;
  // static int currentPlaybacks;

  bool Load(char *data, int size);
  void SetMaxPlaybacks(int max);

  // static void ChannelFinished(int channel);

  virtual void Play();
  virtual void Stop();
  virtual void SetLoop(bool lp);

  TSAMPLE();
  virtual ~TSAMPLE();
};

class TSTREAM : public TCHANNEL
{
public:
  // FSOUND_STREAM *stream;
  Mix_Music *stream;

  // bool Load(const char *file_name, int seek, int size);
  bool Load(const char *file_name);

  virtual void Play();
  virtual void Stop();
  virtual void SetLoop(bool lp);

  bool IsPlaying() override;
  void SetVolume(T_BYTE vol) override;

  TSTREAM() : TCHANNEL() { stream = NULL; }
  virtual ~TSTREAM();
};

class TMODULE : public TSOUND
{
public:
  //   FMUSIC_MODULE *mod;

  // In FMOD, FMUSIC_MODULE is designed for playing tracker module formats like MOD, XM, S3M, and IT.
  // These formats are typically loaded entirely into memory
  // and offer precise control over playback features such as patterns,
  // instruments, and effects

  // In SDL2_mixer, both module formats and streaming audio are handled using the Mix_Music* type.

  Mix_Music *mod;

  bool Load(char *data, int size);

  virtual void Play();
  virtual void Stop();

  virtual void SetVolume(T_BYTE vol);
  virtual void SetVolumeAbsolute(T_BYTE vol);
  virtual void SetLoop(bool lp);

  virtual bool IsPlaying();

  TMODULE() : TSOUND() { mod = NULL; }
  virtual ~TMODULE();
};

//========================================================================
// Functions
//========================================================================

bool InitSound(MIX_InitFlags mix);

//========================================================================
// End
//========================================================================
// vim:ts=2:sw=2:et:
