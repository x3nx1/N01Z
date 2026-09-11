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

    data::Map map{};
    filesystem::loadMap("../n01z/map_templates/demo.toml", map);

    GFX::initialize(1600, 900, "N01Z");
    GFX::activate(); // blocking



    return 0;
}
