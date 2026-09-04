#include <cstdint>
#include <iostream>
#include <windows.h>
#include <gfx.h>


int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd)
{
    return main();
}

int main()
{
    std::cout << "Starting N01Z..." << std::endl;

    using namespace necoresystems;

    GFX::initialize(1280, 720, "N01Z");
    GFX::activate(); // blocking

    return 0;
}
