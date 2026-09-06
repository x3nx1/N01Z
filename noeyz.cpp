#include <cstdint>
#include <iostream>
#include <windows.h>
#include <gfx.h>

#include "nedata.h"


int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd)
{
    return main();
}

int main()
{
    debug::log("Starting N01Z...");


    using namespace necoresystems;

    GFX::initialize(1280, 720, "N01Z");
    GFX::activate(); // blocking

    necoresystems::data::Map::constants con;

    return 0;
}
