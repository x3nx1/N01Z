#include <iostream>
#include <cstdint>
#include <GLFW/glfw3.h>
#include "windows.h"


int main()
{
    std::cout << "Starting..." << std::endl;
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd)
{
    return main();
}