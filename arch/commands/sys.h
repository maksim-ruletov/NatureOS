#if !defined(L0_COMMAND_SYS_H)

#define L0_COMMAND_SYS_H

#include <vector>
#include <string>

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"

namespace arch
{
    namespace command
    {
        void Sys(std::vector<std::string> arguments)
        {
            if (arguments.size() == 0)
            {
                misc::Output(misc::ColorizeFont("System information", 0, 255, 255));
                misc::Output("\n");
                misc::Output("\n");
                misc::Output("@sys command require arguments. If you want to learn about it write sys -h\n");
            }
            else {
                if (arguments.at(0).compare("-i") == 0)
                {
                    misc::Output(StringifyInfo());
                }

                if (arguments.at(0).compare("-h") == 0)
                {
                    misc::Output(misc::ColorizeFont("System information", 0, 255, 255));
                    misc::Output("\n");
                    misc::Output("\n");
                    misc::Output(misc::ColorizeFont("sys -i", 0, 100, 255) + " - full information about system\n");
                }
            }
        }
    }
}

#endif