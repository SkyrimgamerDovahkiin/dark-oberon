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
 *  @file doevent.hpp
 *
 *  Event and Event Dispatcher declarations and methods.
 *
 *  @author Fabian Rubin
 *
 *  @date 2025
 */


#pragma once

#include <string>
#include <functional>

//========================================================================
// Definitions
//========================================================================

enum class EventType
{
    None = 0, // base
    // WindowResized, WindowClose,
    KeyPressed,
    MouseScrolled,
    // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// TODO: add support for multiple event catergories
// (for example, a key press, which belongs to "EventCategoryKeyboard", is also an input event).
enum EventCategory
{
    None = 0, // base
    // EventCategoryWindow,
    EventCategoryKeyboard,
    EventCategoryMouse,
    // EventCategoryApplication,
};

// This macro defines an override of the GetCategoryFlags() method for an event class.
// When used inside a class, it automatically provides the implementation that returns
// the specified category (usually a bitmask or enum value).
//
// For example, calling EVENT_CLASS_CATEGORY(EventCategoryInput) inside an event class
// will define:
//
//     virtual int GetCategoryFlags() const override { return EventCategoryInput; }
//
#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

//========================================================================
// Classes
//========================================================================

// base event.
// NOTE: currently, events are blocking, meaning that they have to be dealt with immediatly.
// Use an event queue later (if needed).
class Event
{
public:
    // gets the event type
    virtual EventType GetEventType() const = 0;
    // gets the name of the event, e.g. "KeyPressed" for KeyPressedEvent
    virtual const char *GetName() const = 0;
    // gets the category flags
    virtual int GetCategoryFlags() const = 0;

    // for printing other stuff to console, such as the keycode for a key press event for example
    virtual std::string ToString() const { return GetName(); }

    // is the event already handled?
    bool Handled = false;

    // to check if the event is in a certain category, if we for example just want to handly key events
    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }
};

// event dispatching
// this event dispatcher first compares the type of the event we want to dispatch
// with the event type specified with T and then dispatches the event

class EventDispatcher
{
public:
    EventDispatcher(Event &event) : mEvent(event)
    {
    }

    /**
     *  Dispatches an event to the given handler if the event type matches T.
     *  @tparam T The event type to check and cast to.
     *  @param func Function to call if the event matches; returns true if handled.
     *  @return true if the event was dispatched and handled, false otherwise.
     */
    template <typename T>
    bool Dispatch(std::function<bool(T &)> func)
    {
        if (mEvent.GetEventType() == T::GetStaticType())
        {
            mEvent.Handled = func(static_cast<T &>(mEvent));
            return true;
        }
        return false;
    }

private:
    Event &mEvent;
};