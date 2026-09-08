#include "nedata.h"

bool necoresystems::filesystem::loadMap(const char *const file, data::Map &targetMap)
{
    try
    {
        using table = const toml::table;
        using array = const toml::array;
        using stringfield = const toml::value<std::string>;
        using intfield = const toml::value<int64_t>;
        using boolfield = const toml::value<bool>;
        using doublefield = const toml::value<double>;


        table fileTable = toml::parse_file(file);

        // fields
        intfield *templateType = fileTable.get_as<intfield>("template_type");
        if(!templateType || templateType->value_or(-1) != 0)
        {
            debug::err("Failed to parse map template file: Missing or invalid template type.");
            return false;
        }

        table *mapTable = fileTable.get_as<table>("map");
        if(!mapTable)
        {
            debug::err("Failed to parse map template file: Unable to locate the following key: 'map'");
            return false;
        }

        stringfield *mapCreatorName = mapTable->get_as<stringfield>("creator");
        stringfield *mapTitle = mapTable->get_as<stringfield>("title");
        stringfield *mapDescription = mapTable->get_as<stringfield>("description");
        stringfield *mapDateUpdated = mapTable->get_as<stringfield>("date_updated");

        boolfield *mapIsAlphaRelease = mapTable->get_as<boolfield>("is_alpha_release");

        // check validity
        if(!(mapCreatorName && mapTitle && mapDescription && mapDateUpdated && mapIsAlphaRelease))
        {
            debug::err(
                "Failed to parse map template file: Unable to locate one or more of the following keys: 'creator' 'title' 'description' 'date_updated' 'is_alpha_release' ");
            return false;
        }

        table *mapConstants = mapTable->get_as<table>("constants");

        if(!mapConstants)
        {
            debug::err("Failed to parse map template file: Unable to locate the following key: 'map.constants'");
            return false;
        }

        stringfield *mapAudioTrack = mapConstants->get_as<stringfield>("audio_track");

        if(!mapAudioTrack)
        {
            debug::err("Failed to parse map template file: Unable to locate the following key: 'audio_track'");
            return false;
        }

        table *mapItemData = mapTable->get_as<table>("itemdata");

        if(!mapItemData)
        {
            debug::err("Failed to parse map template file: Unable to locate the following key: 'map.itemdata'");
            return false;
        }

        table *mapData = mapTable->get_as<table>("data");

        if(!mapData)
        {
            debug::err("Failed to parse map template file: Unable to locate the following keys: 'map.data'");
            return false;
        }

        // load these if applicable, otherwise ignore.
        array *mapItemDataElements = mapItemData->get_as<array>("mitem");
        if(mapItemDataElements && !mapItemDataElements->empty())
        {
            for(size_t i = 0; i < mapItemDataElements->size(); i++)
            {
                table *mapItemDataElementTable = mapItemDataElements->get_as<table>(i);
                if(!mapItemDataElementTable)
                {
                    debug::log("Map template parser: Invalid item data. Skipping...");
                    continue;
                }

                stringfield *itemName = mapItemDataElementTable->get_as<stringfield>("item_name");
                array *itemLocation = mapItemDataElementTable->get_as<array>("item_location");

                if(!(itemName && itemLocation))
                {
                    debug::log("Map template parser: Invalid item data: 'item_name' or 'item_location' - Skipping...");
                    continue;
                }

                doublefield *itemLocationX = itemLocation->get_as<doublefield>(0);
                doublefield *itemLocationY = itemLocation->get_as<doublefield>(1);

                if(!(itemLocationX && itemLocationY))
                {
                    debug::log("Map template parser: Invalid item data: 'item_location' values. Skipping...");
                    continue;
                }

                // if data is there

                data::Map::mitem &mapItemElementItemData = targetMap.mapItems.emplace_back(
                    itemName->value_or("*Unnamed*"));

                mapItemElementItemData.location[0] = itemLocationX->value_or(0.0);
                mapItemElementItemData.location[1] = itemLocationY->value_or(0.0);
            }
        } else
        {
            debug::log("Map template parser: No item data found. Moving on...");
        }

        array *mapDataElements = mapData->get_as<array>("mdata");

        if(mapDataElements && !mapDataElements->empty())
        {
            for(int32_t i = 0; i < mapDataElements->size(); i++)
            {
                table *mapDataElementTable = mapDataElements->get_as<table>(i);

                array *mapDataElementVerts = mapDataElementTable->get_as<array>("verts");
                if(!mapDataElementVerts)
                {
                    debug::err(
                        "Failed to parse map template file: Unable to locate vertex data: 'verts' Maybe check array size.");
                    return false;
                }

                double verts[4][2];


                bool completeData = false;
                for(size_t j = 0; j < mapDataElementVerts->size() || !(completeData = true); j++)
                {
                    array *mapDataElementVertPair = mapDataElementVerts->get_as<array>(j);
                    if(!(mapDataElementVertPair && mapDataElementVertPair->size() == 2))
                    {
                        break; // invalid data - exit before end of loop, leaving completeData flag false
                    }

                    doublefield *vertPairX = mapDataElementVertPair->get_as<doublefield>(0);
                    doublefield *vertPairY = mapDataElementVertPair->get_as<doublefield>(1);

                    if(!(vertPairX && vertPairY))
                    {
                        break; // same as above
                    }

                    // valid pair:

                    verts[j][0] = vertPairX->value_or(0.0); // default to origin
                    verts[j][1] = vertPairY->value_or(0.0); // --
                }

                if(!completeData)
                {
                    continue;
                }

                intfield *mapDataElementType = mapDataElementTable->get_as<intfield>("type");
                intfield *mapDataElementMode = mapDataElementTable->get_as<intfield>("mode");

                if(!(mapDataElementType && mapDataElementMode))
                {
                    continue;
                }

                data::Map::mdata &mapDataElementData = targetMap.mapData.emplace_back(
                    mapDataElementType->value_or(4), mapDataElementMode->value_or(0));

                mapDataElementData.verts[0] = verts[0][0];
                mapDataElementData.verts[1] = verts[0][1];
                mapDataElementData.verts[2] = verts[1][0];
                mapDataElementData.verts[3] = verts[1][1];
                mapDataElementData.verts[4] = verts[2][0];
                mapDataElementData.verts[5] = verts[2][1];
                mapDataElementData.verts[6] = verts[3][0];
                mapDataElementData.verts[7] = verts[3][1];
            }
        } else
        {
            debug::log("Map template parser: No map data found. This might be problematic. Moving on...");
        }

        // assign all values...

        targetMap.creator = mapCreatorName->value_or("*Unknown*");
        targetMap.title = mapTitle->value_or("*Untitled*");
        targetMap.description = mapDescription->value_or("*Who knows?*");
        targetMap.date = mapDateUpdated->value_or("*32/13/2500*");
        targetMap.isAlpha = mapIsAlphaRelease->value_or(true);
        //
        targetMap.mapConstants.audioTrack = mapAudioTrack->value_or("%default%");
        //

        //
    } catch(const toml::parse_error &error)
    {
        debug::err(std::string("Failed to parse map template. ERROR MESSAGE: ") + std::string(error.description()));
        return false;
    }


    return true;
}
