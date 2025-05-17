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
 *  Mouse Event declarations and methods.
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */

#pragma once

#include "doevent.hpp"

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : mXOffset(xOffset), mYOffset(yOffset) {}

    inline float GetXOffset() const { return mXOffset; }
    inline float GetYOffset() const { return mYOffset; }

    std::string ToString() const override
    {
        std::string s = "MouseScrolledEvent: " + std::to_string(GetXOffset()) + ", " + std::to_string(GetYOffset()) + "\n";
        return s;
    }

    static EventType GetStaticType() { return EventType::MouseScrolled; }
    virtual EventType GetEventType() const override { return GetStaticType(); }
    virtual const char *GetName() const override { return "MouseScrolled"; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse)
private:
    float mXOffset, mYOffset;
};