#include <cstdint>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "windows.h"

int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd)
{
    return main();
}

int main()
{
    std::cout << "Starting N01Z..." << std::endl;
    return 0;
}
