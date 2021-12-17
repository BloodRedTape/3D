#include <graphics/api/swapchain.hpp>
#include <core/os/window.hpp>
#include <core/os/clock.hpp>
#include <core/assert.hpp>

struct AutoWindow: Window{
    AutoWindow(int width, int height, const char *title){
        Open(width, height, title);
    }

    ~AutoWindow(){
        if(IsOpen())
            Close();
    }
};

class Application{
private:
    static Application *s_Instance;
private:
    AutoWindow m_MainWindow{1280, 720, "const char *title"};
    FramebufferChain m_Chain{&m_MainWindow};
    bool m_IsRunning = true;

    friend int StraitXMain(Span<const char *>);
public:

    Application(){
        Function<void(const Event &e)> handler;
        handler.Bind<Application, &Application::OnEvent>(this);
        m_MainWindow.SetEventsHanlder(handler);
    }

    void Run(){
        Clock cl;

        Semaphore acq;
        while(m_MainWindow.IsOpen() && m_IsRunning){
            m_MainWindow.DispatchEvents();
            float dt = cl.GetElapsedTime().AsSeconds();
            cl.Restart();

            m_Chain.AcquireNext(&acq);


            m_Chain.PresentCurrent(&acq);
        }
    }

    void OnEvent(const Event &e){
        if(e.Type == EventType::WindowClose)
            m_MainWindow.Close();
    }

    static Application &Get(){
        SX_ASSERT(s_Instance);
        return *s_Instance;
    }
};

Application *Application::s_Instance = nullptr;
