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
 *  @file do_key_event.hpp
 *
 *  Key Event declarations and methods.
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */

#pragma once

#include "doevent.hpp"

//========================================================================
// Classes
//========================================================================

class KeyEvent : public Event
{
public:
    // gets the key code
    inline int GetKeyCode() const { return mKeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

protected:
    KeyEvent(int keycode) : mKeyCode(keycode) {}

    int mKeyCode;
};

// only key event for now
class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), mRepeatCount(repeatCount) {}

    static EventType GetStaticType() { return EventType::KeyPressed; } // needed for comparison when dispatching
    EventType GetEventType() const override { return GetStaticType(); }
    const char *GetName() const override { return "KeyPressed"; }
    inline int GetRepeatCount() const { return mRepeatCount; }

    std::string ToString() const override
    {
        std::string s = "KeyPressedEvent:\n   Key Code: " + std::to_string(mKeyCode) + "\n";
        return s;
    }

private:
    int mRepeatCount;
};