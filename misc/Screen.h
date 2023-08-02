#if !defined(L0_SCREEN_H)

#define L0_SCREEN_H

#include <iostream>
#include <string>

namespace misc {
    void Clear()
    {
        system("cls");
    }

    void Output (std::string content)
    {
        std::cout << content;
    }

    void Input (std::string& inputString)
    {
        std::getline(std::cin, inputString);
    }
}

#endif