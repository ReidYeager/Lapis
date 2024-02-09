class Window
{
private:
  uint32_t           m_width        = 0;
  uint32_t           m_height       = 0;
  char*              m_title        = nullptr;
  bool               m_minimized    = false;
  bool               m_shouldClose  = true;
  bool               m_isValid      = false;
  WindowPlatformInfo m_platformInfo = {};

  std::function<void(Event&)> m_eventCallbackFunction = nullptr;
  std::optional<std::function<void()>> m_platformPollInjection = nullptr;

public:
  LapisResult Init(const WindowInitInfo* initInfo);
  LapisResult PollEvents();
  void         Shutdown();

  inline uint32_t           Width()          const { return m_width; }
  inline uint32_t           Height()         const { return m_height; }
  inline const char*        Title()          const { return m_title; }
  inline WindowPlatformInfo PlatformInfo()   const { return m_platformInfo; }
  inline bool               Minimized()      const { return m_minimized; }
  inline bool               ShouldClose()    const { return m_shouldClose; }
  inline bool               IsValid()        const { return m_isValid; }
  inline void               MarkForClosure()       { m_shouldClose = true; }
};