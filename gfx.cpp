#include "gfx.h"
#include "system.h"

int32_t necoresystems::GFX::initialize(int32_t initialWindowWidth, int32_t initialWindowHeight,
                                       const char *const initialWindowTitle)
{
    // Initialization check
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Potential MacOS requirement


    GFX::window_s.store(glfwCreateWindow(initialWindowWidth, initialWindowHeight, initialWindowTitle, nullptr,
                                         nullptr));
    glfwMakeContextCurrent(nullptr); // will be taken by spawned thread

    if(GFX::window_s.load() == nullptr)
    {
        debug::err("GLFW - Unable to create window.");
        return -1;
    }

    return 0;
}


void necoresystems::GFX::activate()
{
    // start graphics thread
    std::thread gfxThread{
        []()
        {
            glfwMakeContextCurrent(GFX::window_s.load());

            if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
            {
                debug::err("GFX - failed to load GL.");
                return;
            }

            //

            glViewport(0, 0, GFX::getWindowWidth(), GFX::getWindowHeight());

            glfwSetFramebufferSizeCallback(GFX::window_s.load(),
                                           [](GLFWwindow *wnd, int32_t windowWidth, int32_t windowHeight)
                                           {
                                               glViewport(0, 0, windowWidth, windowHeight);
                                           });

            //

            glClearColor(0.0375f, 0.15f, 0.1875f, 1.0f);

            double prevTime{glfwGetTime()};
            double frameTime{0};
            while(!glfwWindowShouldClose(GFX::window_s.load(std::memory_order_relaxed)))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                GFX::draw(frameTime);
                glfwSwapBuffers(GFX::window_s.load());

                //

                const double time = glfwGetTime();
                frameTime = time - prevTime;
                prevTime = time;
            }
        }

    };

    while(!glfwWindowShouldClose(GFX::window_s.load(std::memory_order_relaxed)))
    {
        glfwPollEvents();
    }

    gfxThread.join();
    glfwDestroyWindow(GFX::window_s.load());
    glfwTerminate();

    debug::log("Graphics thread exit.");
}

int32_t necoresystems::GFX::getWindowWidth()
{
    int32_t windowWidth = -1;
    glfwGetWindowSize(GFX::window_s.load(), &windowWidth, nullptr);
    return windowWidth;
}

int32_t necoresystems::GFX::getWindowHeight()
{
    int32_t windowHeight = -1;
    glfwGetWindowSize(GFX::window_s.load(), nullptr, &windowHeight);
    return windowHeight;
}

void necoresystems::GFX::exit()
{
    glfwSetWindowShouldClose(GFX::window_s.load(), true);
}


void necoresystems::GFX::draw(double frameTime)
{
    using engine = necoresystems::System;
}
