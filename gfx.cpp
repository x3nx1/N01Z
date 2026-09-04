#include "gfx.h"


necoresystems::GFX::GFX(int32_t initialWindowWidth, int32_t initialWindowHeight,
                        const char *const initialWindowTitle, int32_t *const status)
{
    *status = -1;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Potential MacOS requirement

    this->wnd = glfwCreateWindow(initialWindowWidth, initialWindowHeight, initialWindowTitle, NULL, NULL);
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

void necoresystems::GFX::display(int32_t *const statusAsync)
{
    // start graphics thread
    std::thread gfxThread{
        [this, statusAsync]()
        {
            *statusAsync = 0;
            this->active = true;


            glfwMakeContextCurrent(this->wnd);

            if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
            {
                *statusAsync = 100;
                return;
            }


            glViewport(0, 0, this->getWindowWidth(), this->getWindowHeight());

            glfwSetFramebufferSizeCallback(this->wnd, [](GLFWwindow *wnd, int32_t windowWidth, int32_t windowHeight)
            {
                glViewport(0, 0, windowWidth, windowHeight);
            });

            while(this->active)
            {
                glClearColor(0.2f,0.2f,0.8f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(this->wnd);
                // todo: graphics loop
            }
        }

    };


    while(!glfwWindowShouldClose(this->wnd))
    {
        glfwPollEvents();
    }

    this->active = false;

    gfxThread.join();
    debug::log("Graphics thread exit.");
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
