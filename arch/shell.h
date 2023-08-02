#if !defined(L0_SHELL_H)

/*
 * Оболочка будет прогружаться до инициализации ядра и позволит выполнять команды вне ядра. 
 */
#define L0_SHELL_H

#include "../misc/Screen.h"
#include "../misc/Colorizer.h"
#include "../misc/TTY.h"

#include "./sys.h"

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::TTY tty;

            misc::Clear();

            misc::Output(misc::ColorizeFont("Welcome to NatureOS shell!\n", 255, 0, 0));

            tty.CreateCommand("help", [](std::vector<std::string> arguments)
            {
                misc::Output(misc::ColorizeFont("NatureShell help list", 0, 255, 255));
                misc::Output("\n");
                misc::Output("\n");
                misc::Output(misc::ColorizeFont("sys", 0, 100, 255) + " - information about system\n");
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
                }
            });

            tty.StartInteractive();
        }
    };
} // #arch

#endif