#if !defined(L1_COLORIZER_H)

#define L1_COLORIZER_H

#include <string>
#include "./Utilities.h"

namespace misc {
    std::string ColorizeFont (const std::string S_Content, const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
        return "\033[38;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m" + S_Content + "\033[0m";
    }

    std::string ColorizeBackground (const std::string S_Content, const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
        return "\033[48;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m" + S_Content + "\033[0m";
    }
}

#endif