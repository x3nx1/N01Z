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
        if(mapItemDataElements && (mapItemDataElements->size() > 0))
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

                const double itemLocationPair[2] = {itemLocationX->value_or(0.0), itemLocation->value_or(0.0)};
                targetMap.mapItems.emplace_back(itemName->value_or("*Unnamed*"), itemLocationPair);
            }
        } else
        {
            debug::log("Map template parser: No item data found. Moving on...");
        }

        array *mapDataElements = mapData->get_as<array>("mdata");

        if(mapDataElements && (mapDataElements->size() > 0))
        {
            for(int32_t i = 0; i < mapDataElements->size(); i++)
            {
                //table *mapDataElementTable = mapDataElements->get_as<table>(i);

                //
                // TODO: implement map data loading here
                //
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
