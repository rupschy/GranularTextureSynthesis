/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   knob_b_small_png;
    const int            knob_b_small_pngSize = 5457;

    extern const char*   knob_w_large_png;
    const int            knob_w_large_pngSize = 18715;

    extern const char*   bg_png;
    const int            bg_pngSize = 443232;

    extern const char*   bg_1_png;
    const int            bg_1_pngSize = 380080;

    extern const char*   airstrike3d_ttf;
    const int            airstrike3d_ttfSize = 62100;

    extern const char*   bg_jpg;
    const int            bg_jpgSize = 89197;

    extern const char*   test_bg_jpg;
    const int            test_bg_jpgSize = 356106;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

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
