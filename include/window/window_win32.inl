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
  std::optional<std::function<void(HWND, uint32_t, WPARAM, LPARAM)>> m_platformPollInjection = nullptr;

public:
  LapisResult Init(const WindowInitInfo* initInfo);
  LapisResult PollEvents();
  void         Shutdown();

  inline uint32_t           Width()          const { return m_width; }
  inline uint32_t           Height()         const { return m_height; }
  inline const char*        Title()          const { return m_title; }
  inline WindowPlatformInfo PlatformInfo()   const { return m_platformInfo; }
  inline bool               Minimized()      const { return m_minimized; }
  inline bool               ShouldClose()    const { return m_shouldClose || !m_isValid; }
  inline bool               IsValid()        const { return m_isValid; }  
  inline void               MarkForClosure()       { m_shouldClose = true; }

  // Win32 specific
  // ============================================================
  friend LRESULT CALLBACK Win32InputCallback(HWND hwnd, uint32_t message, WPARAM wparam, LPARAM lparam);

private:
  LapisResult Register();
  LapisResult CreatePlatformWindow(const WindowInitInfo* initInfo);
  LapisResult RegisterInput();
};