/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   background_texture_dark_png;
    const int            background_texture_dark_pngSize = 199506;

    extern const char*   flute_png;
    const int            flute_pngSize = 2747;

    extern const char*   placeholder_png;
    const int            placeholder_pngSize = 725;

    extern const char*   saxophone_png;
    const int            saxophone_pngSize = 3018;

    extern const char*   trumpet_png;
    const int            trumpet_pngSize = 3236;

    extern const char*   violin_png;
    const int            violin_pngSize = 3333;

    extern const char*   background_texture_png;
    const int            background_texture_pngSize = 296713;

    extern const char*   background_texture_dark_headline_png;
    const int            background_texture_dark_headline_pngSize = 280033;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
