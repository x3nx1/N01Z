#ifndef N01Z_GFX_H
#define N01Z_GFX_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include <thread>
#include <atomic>
#include <cstdint>
#include <vector>

namespace necoresystems
{
    class GFX
    {
    public:
        GFX() = delete;

        ~GFX() = delete;

        static int32_t initialize(int32_t initialWindowWidth, int32_t initialWindowHeight,
                                  const char *initialWindowTitle);

        static void activate();

        [[nodiscard]] static int32_t getWindowWidth();

        [[nodiscard]] static int32_t getWindowHeight();

        static void exit();

    private:
        inline static std::atomic<GLFWwindow *> window_s{nullptr};

        static void draw(double frameTime);
    };
}

#endif //N01Z_GFX_H
