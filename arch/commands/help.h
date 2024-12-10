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
        void Help(std::vector<std::string> arguments, std::vector<misc::Command> commands)
        {
            std::string commandPrompt = "";

            misc::Output(misc::ColorizeFont("NatureShell help list", 0, 255, 255));
            misc::Output("\n");
            misc::Output("\n");

            for (misc::Command command : commands) {
                commandPrompt += misc::ColorizeFont(command.command, 0, 100, 255) + " - " + command.description + "\n";
            }

            misc::Output(commandPrompt);
        }
    }
}

#endif