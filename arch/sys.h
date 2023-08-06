#if !defined(L0_SYS_H)

#define L0_SYS_H

#include <string>
#include "../misc/Colorizer.h"

namespace arch
{
    const std::string SysVersion = "0.3.0";
    const std::string SysName = "Nature OS (POS)";
    const std::string SysAuthor = "ruletkasuperstar";

    std::string StringifyInfo()
    {
        std::string output = "| " + misc::ColorizeFont(SysVersion, 100, 0, 10) + " | " + misc::ColorizeFont(SysName, 100, 0, 10) + " |\n";
        output += "Made by " + misc::ColorizeFont(SysAuthor, 255, 0, 0) + "\n\n";
        output += misc::ColorizeBackground("   ", 255, 0, 0) + misc::ColorizeBackground("   ", 0, 255, 0) + misc::ColorizeBackground("   ", 0, 0, 255)
                  + misc::ColorizeBackground("   ", 255, 255, 0) + misc::ColorizeBackground("   ", 0, 255, 255) + misc::ColorizeBackground("   ", 255, 255, 255) + "\n\n";

        return output;
    }
}

#endif