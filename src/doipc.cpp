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
 *  @file doipc.cpp
 *
 *  IPC - inter process communication (mutexes etc.).
 *
 *  @author Marian Cerny
 *
 *  @date 2005
 */


//=========================================================================
// Included files
//=========================================================================

#include "cfg.h"

#include "doipc.h"
#include "dologs.h"

//=========================================================================
// TLOCK
//=========================================================================

TLOCK::TLOCK () {} // no need to manually check if mutex/cond created


TLOCK::~TLOCK () {} // no need to manually check if mutex/cond destroyed


#if DEBUG
/**
 *  Locks the object to get exclusive access to it.
 */
void TLOCK::Lock ()
{
  // TODO:

  auto myself = std::this_thread::get_id();

  mutex.lock();

  if (locked_by == myself) {
    /* Mutex is already locked by myself, you should consider using
     * TRECURSIVE_LOCK instead. */
    throw MutexException ();
  }

  /* wait until I can enter. */ // should work?
  std::unique_lock<std::mutex> lock(mutex);
  unlocked.wait(lock, [this] { return locked_by == std::thread::id{}; });

  // while (locked_by != -1) {
  //   glfwWaitCond (unlocked, mutex, GLFW_INFINITY);
  // }

  locked_by = myself;

  mutex.unlock();
}
#endif

#if DEBUG
/**
 *  Locks the object to get exclusive access to it.
 */
void TLOCK::Unlock ()
{
  mutex.lock();

  auto myself = std::this_thread::get_id();

  if (locked_by == std::thread::id{}) {
    /* Mutex is not locked! Fix your bug. */
    throw MutexException ();
  }

  if (locked_by != myself) {
    /* Hey, hey! You shouldn't be unlocking this when you din't lock it. */
    throw MutexException ();
  }

  locked_by = std::thread::id{};

  unlocked.notify_all(); // Notify all waiting threads, should work
  mutex.unlock();
}
#endif

//=========================================================================
// TRECURSIVE_LOCK
//=========================================================================

/**
 *  Creates mutex needed for proper manipulation with object.
 *
 *  @throw MutexException { Error creating mutex. }
 */
TRECURSIVE_LOCK::TRECURSIVE_LOCK ()
{
  // mutex = glfwCreateMutex ();

  // std::recursive_mutex mutex;

  /* Throws an exception when mutex was not created. */
  // if (!mutex)
  //   throw MutexException ();

  // locked_by = -1;
  locked_by = std::thread::id{};
  locked_count = 0;
}


TRECURSIVE_LOCK::~TRECURSIVE_LOCK () {} // no need to destroy mutex manually

/**
 *  Locks the object to get exclusive access to it. Lock() can be called more
 *  than once by one thread, it is implemented as a recursive lock. Unlock()
 *  then must be called the same count as Lock().
 */
void TRECURSIVE_LOCK::Lock ()
{
// #if DEBUG
//   if (!mutex)
//     throw MutexException ();
// #endif

  auto myself = std::this_thread::get_id();

  if (locked_by != myself)
  {
    mutex.lock();
    locked_by = myself;
  }

  locked_count++;
}


/**
 *  Unlocks the object.
 *
 *  @see Lock
 */
void TRECURSIVE_LOCK::Unlock ()
{
  auto myself = std::this_thread::get_id();

  if (locked_by != myself) {
    throw MutexException ();
  }

  locked_count--;

  if (!locked_count) {
    locked_by = std::thread::id{};
    mutex.unlock();
  }
}


//=========================================================================
// Global variables
//=========================================================================

TRECURSIVE_LOCK *giant;
TRECURSIVE_LOCK *process_mutex;


//=========================================================================
// Global functions
//=========================================================================

void init_giant () {
  giant = new TRECURSIVE_LOCK ();
}

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et:
