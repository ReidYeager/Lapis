#ifndef LAPIS_EVENT_INPUT_H
#define LAPIS_EVENT_INPUT_H

#include "include/lapis_defines.h"
#include "include/events/event.h"
#include "include/events/buttons.h"

#include <sstream>

namespace Lapis
{

// ============================================================
// Keyboard
// ============================================================

class EventKeyPressed : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Key_Press, Event_Category_Input | Event_Category_Input_Keyboard)
  EventKeyPressed(ButtonCode key) : m_keycode(key) {}

  inline int32_t GetKeycode() const { return m_keycode; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Key pressed (" << m_keycode << ")";
    return stream.str();
  }

private:
  ButtonCode m_keycode;
};

class EventKeyReleased : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Key_Release, Event_Category_Input | Event_Category_Input_Keyboard)
  EventKeyReleased(ButtonCode key) : m_keycode(key) {}

  inline int32_t GetKeycode() const { return m_keycode; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Key released (" << m_keycode << ")";
    return stream.str();
  }

private:
  ButtonCode m_keycode;
};

// ============================================================
// Mouse
// ============================================================

class EventMouseMove : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Mouse_Move, Event_Category_Input | Event_Category_Input_Mouse)
  EventMouseMove(int32_t newX, int32_t newY) : m_xPos(newX), m_yPos(newY) {}

  inline int32_t GetXPos() const { return m_xPos; }
  inline int32_t GetYPos() const { return m_yPos; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Mouse moved to (" << m_xPos << ", " << m_yPos << ")";
    return stream.str();
  }

private:
  int32_t m_xPos, m_yPos;
};

class EventMouseScroll : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Mouse_Scroll, Event_Category_Input | Event_Category_Input_Mouse)
  EventMouseScroll(float xAmount, float yAmount) : m_xAmount(xAmount), m_yAmount(yAmount) {}

  inline float GetXAmount() const { return m_xAmount; }
  inline float GetYAmount() const { return m_yAmount; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Mouse scrolled (" << m_xAmount << ", " << m_yAmount << ")";
    return stream.str();
  }

private:
  float m_xAmount, m_yAmount;
};

class EventMouseButtonPress : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Mouse_Button_Press, Event_Category_Input | Event_Category_Input_Mouse | Event_Category_Input_Mouse_Button)
  EventMouseButtonPress(uint32_t button) : m_button(button) {}

  inline uint32_t GetButon() const { return m_button; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Mouse button pressed (" << m_button << ")";
    return stream.str();
  }

private:
  uint32_t m_button;
};

class EventMouseButtonRelease : public Event
{
public:
  EVENT_DEFINE_COMMON(Event_Mouse_Button_Release, Event_Category_Input | Event_Category_Input_Mouse | Event_Category_Input_Mouse_Button)
  EventMouseButtonRelease(uint32_t button) : m_button(button) {}

  inline uint32_t GetButon() const { return m_button; }

  virtual std::string ToString_Debug() const override
  {
    std::stringstream stream;
    stream << "Mouse button released (" << m_button << ")";
    return stream.str();
  }

private:
  uint32_t m_button;
};

} // namespace Lapis

#endif // !LAPIS_EVENT_INPUT_H
