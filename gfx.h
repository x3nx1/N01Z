#ifndef N01Z_GFX_H
#define N01Z_GFX_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include <thread>
#include <cstdint>

namespace necoresystems
{
    class GFX
    {
    public:
        GFX() = delete;

        GFX(int32_t initialWindowWidth, int32_t initialWindowHeight, const char *initialWindowTitle, int32_t *status);

        ~GFX();


        void display(int32_t *statusAsync);

        [[nodiscard]] int32_t getWindowWidth() const;

        [[nodiscard]] int32_t getWindowHeight() const;

    private:
        GLFWwindow *wnd{nullptr};
        bool active{false};
    };
}

#endif //N01Z_GFX_H
