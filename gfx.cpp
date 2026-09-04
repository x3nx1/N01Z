#include "gfx.h"

#include "system.h"


necoresystems::GFX::GFX(int32_t initialWindowWidth, int32_t initialWindowHeight,
                        const char *const initialWindowTitle, int32_t *const status)
{
    *status = -1;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Potential MacOS requirement

    this->wnd = glfwCreateWindow(initialWindowWidth, initialWindowHeight, initialWindowTitle, nullptr, nullptr);
    glfwMakeContextCurrent(nullptr);

    if(wnd == nullptr)
    {
        debug::err("GLFW - Unable to create window.");
        glfwTerminate();
        return;
    }

    *status = 0;
}

necoresystems::GFX::~GFX()
{
    glfwTerminate();
}

void necoresystems::GFX::display(std::atomic<int32_t> &statusAsync)
{
    // start graphics thread
    std::thread gfxThread{
        [this, &statusAsync]()
        {
            statusAsync.store(0);
            this->active.store(true);


            glfwMakeContextCurrent(this->wnd.load());

            if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
            {
                statusAsync.store(100);
                return;
            }


            glViewport(0, 0, this->getWindowWidth(), this->getWindowHeight());

            glfwSetFramebufferSizeCallback(this->wnd.load(),
                                           [](GLFWwindow *wnd, int32_t windowWidth, int32_t windowHeight)
                                           {
                                               glViewport(0, 0, windowWidth, windowHeight);
                                           });

            double prevTime{glfwGetTime()};

            glClearColor(0.0375f, 0.15f, 0.1875f, 1.0f);

            while(this->active.load(std::memory_order_relaxed))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                this->draw();
                glfwSwapBuffers(this->wnd.load());

                double time = glfwGetTime();
                double frameTime = time - prevTime;
                prevTime = time;
            }
        }

    };


    while(!glfwWindowShouldClose(this->wnd.load(std::memory_order_relaxed)))
    {
        glfwPollEvents();
    }

    this->active.store(false);

    gfxThread.join();

    glfwDestroyWindow(this->wnd.load());

    debug::log("Graphics thread exit.");
}

void necoresystems::GFX::display()
{
    std::atomic<int32_t> status{0};
    this->display(status);
}


int32_t necoresystems::GFX::getWindowWidth() const
{
    int32_t windowWidth = -1;
    glfwGetWindowSize(this->wnd, &windowWidth, nullptr);
    return windowWidth;
}

int32_t necoresystems::GFX::getWindowHeight() const
{
    int32_t windowHeight = -1;
    glfwGetWindowSize(this->wnd, nullptr, &windowHeight);
    return windowHeight;
}

void necoresystems::GFX::draw()
{
    using engine = necoresystems::System;




}
