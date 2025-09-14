#if !defined(L0_COMMAND_INSTALL_H)

#define L0_COMMAND_INSTALL_H

#include <vector>
#include <string>

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"

#include "../../installer/main.h"

#include "../../fs/translated.h"

namespace arch
{
    namespace command
    {
        void Install(std::vector<std::string> arguments)
        {
            if (arguments.size() == 0)
            {
                misc::Output(misc::ColorizeFont("Installation information", 0, 255, 255));
                misc::Output("\n");
                misc::Output("\n");
                misc::Output(misc::ColorizeFont("install -f", 0, 100, 255) + " - install full NatureOS version\n");
                misc::Output(misc::ColorizeFont("install -c", 0, 100, 255) + " - install compact NatureOS version\n");
            }
            else
            {
                if (arguments.at(0).compare("-f") == 0)
                {
                    if (fs::translated::DirectoryExist("./natureos"))
                    {
                        misc::Output(misc::ColorizeFont("Installation failed", 255, 50, 50));
                        misc::Output("\n");
                        misc::Output("\n");
                        misc::Output("Looks like NatureOS already installed. To uninstall it write uninstall command\n");
                    }
                    else
                    {
                        misc::Output(misc::ColorizeFont("Starting full install...", 0, 255, 0));
                        misc::Output("\n");
                        misc::Output("\n");

                        int status = installer::CreateFileSystem("f");

                        misc::Output("\n");
                        misc::Output("\n");
                        misc::Output(status == 0 ? "Installation successfuly finished\n" : "Installation failed!\n");
                    }
                }
            }
        }
    }
}

#endif