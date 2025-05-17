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
 *  @file doipc.h
 *
 *  IPC - inter process communication (mutexes etc.).
 *
 *  @author Marian Cerny
 *
 *  @date 2005
 */

#ifndef __doipc_h__
#define __doipc_h__

//=========================================================================
// Included files
//=========================================================================

#include "cfg.h"

#include <string>
#include <list>

#include <glfw3.h>
// #include <tinycthread.h> // TODO: replace with C++ thread
#include <thread>
#include <condition_variable>
#include <mutex>

//=========================================================================
// TLOCK
//=========================================================================

struct TLOCK
{
public:
  class MutexException
  {
  };

  TLOCK();
  ~TLOCK();

#if DEBUG
  void Lock();
  void Unlock();
#else
  void Lock()
  {
#ifdef NEW_GLFW3
    mtx_lock(&mutex);
#else
    glfwLockMutex(mutex);
#endif
  }

  void Unlock()
  {
#ifdef NEW_GLFW3
    mtx_unlock(&mutex);
#else
    glfwUnlockMutex(mutex);
#endif
  }
#endif

private:
#if DEBUG

  std::thread::id locked_by;
  std::condition_variable unlocked;

#endif

  std::mutex mutex; //!< Mutex for atomicity of operations.
};

//=========================================================================
// TRECURSIVE_LOCK
//=========================================================================

struct TRECURSIVE_LOCK
{
public:
  class MutexException
  {
  };

  TRECURSIVE_LOCK();
  ~TRECURSIVE_LOCK();

  void Lock();
  void Unlock();

private:
  int locked_count;
  std::thread::id locked_by;
  // std::mutex mutex; //!< Mutex for atomicity of operations.
  std::recursive_mutex mutex;
};

//=========================================================================
// template TSAVE_LIST
//=========================================================================

template <class T>
class TSAVE_LIST
{
public:
  class MutexException
  {
  };

  TSAVE_LIST() {} // no need to check if mutex created

  ~TSAVE_LIST() {} // no need to destroy mutex explicitly

  void PushBack(T node)
  {

    if (!mutex.try_lock())
    {
      throw MutexException();
    }
    else
    {
      list.push_back(node);
    }
    mutex.unlock();
  }

  bool PopFront(T &node)
  {
    bool ret;
    if (!mutex.try_lock())
    {
      throw MutexException();
    }
    else
    {
      ret = !list.empty();
      if (ret)
      {
        node = *list.begin();
        list.pop_front();
      }
    }
    mutex.unlock();

    return ret;
  }

private:
  std::mutex mutex; //!< Mutex for atomicity of operations.

  std::list<T> list;
};

//=========================================================================
// Global variables
//=========================================================================

extern TRECURSIVE_LOCK *giant;
extern TRECURSIVE_LOCK *process_mutex;

//=========================================================================
// Global functions
//=========================================================================

void init_giant();

#endif // __doplayers_h__

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et:
