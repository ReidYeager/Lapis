class Window
{
private:
  uint32_t           m_width        = 0;
  uint32_t           m_height       = 0;
  char*              m_title        = nullptr;
  bool               m_minimized    = false;
  bool               m_shouldClose  = true;
  WindowPlatformInfo m_platformInfo = {};

  //Input              m_input;
  std::function<void(Event&)> m_eventCallbackFunction;

public:
  SandboxResult Init(WindowInitInfo initInfo);
  SandboxResult PollEvents();
  void         Shutdown();

  inline uint32_t           Width()          const { return m_width; }
  inline uint32_t           Height()         const { return m_height; }
  inline const char*        Title()          const { return m_title; }
  inline WindowPlatformInfo PlatformInfo()   const { return m_platformInfo; }
  inline bool               Minimized()      const { return m_minimized; }
  inline bool               ShouldClose()    const { return m_shouldClose; }
  inline void               MarkForClosure()       { m_shouldClose = true; }
};