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

#include "./sys.h"

#include "./commands/help.h"
#include "./commands/sys.h"
#include "./commands/install.h"
#include "./commands/detect.h"
#include "./commands/testw.h"
#include "./commands/date.h"

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::TTY tty;

            misc::Clear();

            tty.SetScreenPrefix(misc::ColorizeFont("$", 104, 55, 79) + "> ");

            misc::Output(misc::ColorizeFont("Welcome to NatureOS shell!\n", 255, 0, 0));

            tty.CreateCommand("help", "full NatureOS list of commands", [&tty](std::vector<std::string> arguments)
            {
                arch::command::Help(arguments, tty.DropCommands());
            });

            tty.CreateCommand("sys", "information about system", &arch::command::Sys);

            tty.CreateCommand("install", "install the NatureOS", &arch::command::Install);

            tty.CreateCommand("detect", "detect already installed NatureOS", &arch::command::Detect);

            tty.CreateCommand("testw", "test system perfomance", &arch::command::Testw);

            tty.CreateCommand("exit", "log out from NatureOS", [&tty](std::vector<std::string> arguments)
            {
                tty.Exit();
            });

            tty.CreateCommand("date", "print current date", &arch::command::Date);

            tty.StartInteractive();
        }
    };
} // #arch

#endif