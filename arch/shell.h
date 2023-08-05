#if !defined(L0_SHELL_H)

/*
 * Оболочка будет прогружаться до инициализации ядра и позволит выполнять команды вне ядра. 
 */
#define L0_SHELL_H

#include <vector>
#include <string>
#include <cstdint>

#include "../misc/Screen.h"
#include "../misc/Colorizer.h"
#include "../misc/TTY.h"

#include "../fs/translated.h"

#include "./sys.h"

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::TTY tty;

            misc::Clear();

            tty.SetScreenPrefix(misc::ColorizeFont("[nshell]", 104, 55, 79) + " >> ");

            misc::Output(misc::ColorizeFont("Welcome to NatureOS shell!\n", 255, 0, 0));

            tty.CreateCommand("help", [](std::vector<std::string> arguments)
            {
                misc::Output(misc::ColorizeFont("NatureShell help list", 0, 255, 255));
                misc::Output("\n");
                misc::Output("\n");
                misc::Output(misc::ColorizeFont("sys", 0, 100, 255) + " - information about system\n");
                misc::Output(misc::ColorizeFont("install", 0, 100, 255) + " - install the NatureOS\n");
                misc::Output(misc::ColorizeFont("detect", 0, 100, 255) + " - detect already installed NatureOS\n");
                misc::Output(misc::ColorizeFont("testw", 0, 100, 255) + " - test system perfomance\n");
                misc::Output(misc::ColorizeFont("exit", 0, 100, 255) + " - log out from NatureOS\n");
            });

            tty.CreateCommand("sys", [](std::vector<std::string> arguments)
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
            });

            tty.CreateCommand("install", [](std::vector<std::string> arguments)
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
                    
                }
            });

            tty.CreateCommand("detect", [](std::vector<std::string> arguments)
            {
                if (fs::translated::DirectoryExist("./natureos"))
                {
                    misc::Output("NatureOS founded. To check the system performance, write the testw command\n");
                }
                else
                {
                    misc::Output("NatureOS not founded. To install it write install command\n");
                }
            });

            tty.CreateCommand("testw", [](std::vector<std::string> arguments)
            {
                const std::vector<std::string> Markers {
                    misc::ColorizeBackground("  ", 255, 50, 0),
                    misc::ColorizeBackground("  ", 0, 255, 50),
                    misc::ColorizeBackground("  ", 255, 255, 0),
                };

                std::uint8_t errors = 0;
                std::uint8_t warnings = 0;

                misc::Output("\n");

                for (std::string path : RequiredDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(0) + " >> Path " + path + " not found, but required!\n");
                        errors++;
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> Path " + path + " founded!\n");
                    }
                }

                for (std::string path : RequiredUserDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(0) + " >> User path " + path + " not found, but required!\n");
                        errors++;
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> User path " + path + " founded!\n");
                    }
                }

                for (std::string path : OptionalDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(2) + " >> Path " + path + " not found.\n");
                        warnings++;
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> User path " + path + " founded!\n");
                    }
                }

                misc::Output("\n");

                misc::Output("Testing result:\n");
                misc::Output(Markers.at(0) + " errors: " + std::to_string(errors) + "\n");
                misc::Output(Markers.at(2) + " warnings: " + std::to_string(warnings) + "\n");

                misc::Output("\n");
            });

            tty.CreateCommand("exit", [&tty](std::vector<std::string> arguments)
            {
                tty.Exit();
            });

            tty.StartInteractive();
        }
    };
} // #arch

#endif