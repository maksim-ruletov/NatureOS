#ifndef NatureOS_StandardLibrary_SL_Colorizer_hpp
    #define NatureOS_StandardLibrary_SL_Colorizer_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    namespace __StandardLibrary {
        std::string E_ColorizeFront (std::string D_Content, int D_Red, int D_Green, int D_Blue) {
            return "\033[38;2;" + std::to_string(D_Red) + ";" + std::to_string(D_Green) + ";" + std::to_string(D_Blue) + "m" + D_Content + "\033[0m";
        }

        std::string E_ColorizeBack (std::string D_Content, int D_Red, int D_Green, int D_Blue) {
            return "\033[48;2;" + std::to_string(D_Red) + ";" + std::to_string(D_Green) + ";" + std::to_string(D_Blue) + "m" + D_Content + "\033[0m";
        }
    }

#endif