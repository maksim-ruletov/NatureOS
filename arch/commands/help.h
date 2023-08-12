#if !defined(L0_COMMAND_HELP_H)

#define L0_COMMAND_HELP_H

#include <vector>
#include <string>

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"

namespace arch
{
    namespace command
    {
        void Help(std::vector<std::string> arguments)
        {
            misc::Output(misc::ColorizeFont("NatureShell help list", 0, 255, 255));
            misc::Output("\n");
            misc::Output("\n");
            misc::Output(misc::ColorizeFont("sys", 0, 100, 255) + " - information about system\n");
            misc::Output(misc::ColorizeFont("install", 0, 100, 255) + " - install the NatureOS\n");
            misc::Output(misc::ColorizeFont("detect", 0, 100, 255) + " - detect already installed NatureOS\n");
            misc::Output(misc::ColorizeFont("testw", 0, 100, 255) + " - test system perfomance\n");
            misc::Output(misc::ColorizeFont("exit", 0, 100, 255) + " - log out from NatureOS\n");
        }
    }
}

#endif