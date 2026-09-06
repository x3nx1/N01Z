#ifndef N01Z_NEDATA_H
#define N01Z_NEDATA_H

#include <cstdint>

namespace necoresystems
{
    namespace data
    {
        struct Map
        {
            struct constants
            {
                const char *audioTrack;
            };

            struct mdata
            {
                int16_t type;
                int16_t mode;
                const double **verts;
            };

            struct mitem
            {
                const char *itemName;
                const double *location;
            };

            const char *creator;
            const char *title;
            const char *description;
            const char *date;
            bool isAlpha;
            constants mapConstants;
            mdata *mapData;
            mitem *mapItems;
        };
    };
}


#endif //N01Z_NEDATA_H
