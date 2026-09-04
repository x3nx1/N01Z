#ifndef N01Z_GFX_H
#define N01Z_GFX_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include <thread>
#include <atomic>
#include <cstdint>

namespace necoresystems
{
    class GFX
    {
    public:
        GFX() = delete;

        GFX(int32_t initialWindowWidth, int32_t initialWindowHeight, const char *initialWindowTitle, int32_t *status);

        ~GFX();


        void display(std::atomic<int32_t> &statusAsync);
        void display();

        [[nodiscard]] int32_t getWindowWidth() const;

        [[nodiscard]] int32_t getWindowHeight() const;

    private:
        std::atomic<GLFWwindow *> wnd{nullptr};
        std::atomic<bool> active{false};
        static void draw();

    };
}

#endif //N01Z_GFX_H
