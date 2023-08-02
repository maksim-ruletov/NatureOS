#if !defined(L0_SCREEN_H)

#define L0_SCREEN_H

#include <iostream>
#include <string>

namespace misc {
    void E_Output (std::string D_Content) {
        std::cout << D_Content;
    }

    void E_Input (std::string& D_InputString) {
        std::getline(std::cin, D_InputString);
    }
}

#endif