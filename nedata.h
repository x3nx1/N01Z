#ifndef N01Z_NEDATA_H
#define N01Z_NEDATA_H

#include <cstdint>
#include <toml++/toml.hpp>
#include <debug.h>

namespace necoresystems
{
    namespace data
    {
        struct Map
        {
            typedef struct Constants
            {
                const char *audioTrack;
            } constants;

            typedef struct MData
            {
                int32_t type;
                int32_t mode;
                double verts[8]{};
            } mdata;

            typedef struct MItem
            {
                const char *itemName;
                double location[2]{};
            } mitem;

            const char *creator{"%unset%"};
            const char *title{"%unset%"};
            const char *description{"%unset%"};
            const char *date{"%unset%"};
            bool isAlpha{true};
            constants mapConstants{"%unset%"};
            std::vector<mdata> mapData{};
            std::vector<mitem> mapItems{};
        };
    };

    namespace filesystem
    {
        bool loadMap(const char *file, data::Map &targetMap);
    }
}


#endif //N01Z_NEDATA_H
