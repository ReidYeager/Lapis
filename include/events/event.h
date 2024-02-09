#ifndef LAPIS_EVENT_H
#define LAPIS_EVENT_H

#include "include/lapis_defines.h"

#include <string>

namespace Lapis
{

enum EventCategoryFlagBits
{
  Event_Category_Unknown            = 0,
  Event_Category_Window             = (1 << 0),
  Event_Category_Input              = (1 << 1),
  Event_Category_Input_Keyboard     = (1 << 2),
  Event_Category_Input_Mouse        = (1 << 3),
  Event_Category_Input_Mouse_Button = (1 << 4),
};
typedef uint32_t EventCategoryFlags;

enum EventType
{
  Event_Window_Close,
  Event_Window_Resize,
  Event_Window_Minimize,
  Event_Window_Move,
  Event_Window_Focus,

  Event_Key_Press,
  Event_Key_Release,

  Event_Mouse_Move,
  Event_Mouse_Scroll,
  Event_Mouse_Button_Press,
  Event_Mouse_Button_Release,
};

#define EVENT_DEFINE_COMMON(type, categoryFlags)                                           \
inline static EventType GetTypeStatic() { return type; }                           \
inline EventType GetType() const override { return type; }                         \
inline const char* GetTypeName_Debug() const override { return #type; }                    \
inline EventCategoryFlags GetCategories() const override { return categoryFlags; }

class Event
{
public:
  virtual ~Event() {}
  virtual EventType GetType() const = 0;
  virtual EventCategoryFlags GetCategories() const = 0;
  inline bool HasCategory(EventCategoryFlagBits mask) const { return GetCategories() & mask; };

  virtual const char* GetTypeName_Debug() const = 0;
  virtual std::string ToString_Debug() const { return GetTypeName_Debug(); }
}; // class Event

} // namespace Lapis

#include "include/events/event_input.h"
#include "include/events/event_window.h"

#endif // !LAPIS_EVENT_H
