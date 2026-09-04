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
    int32_t status;

    GFX gfx{1280, 720, "N01Z", &status};


    gfx.display(&status);



    return status;
}
