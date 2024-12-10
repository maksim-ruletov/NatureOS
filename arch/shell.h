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

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::TTY tty;

            misc::Clear();

            tty.SetScreenPrefix(misc::ColorizeFont("nshell", 104, 55, 79) + "> ");

            misc::Output(misc::ColorizeFont("Welcome to NatureOS shell!\n", 255, 0, 0));

            tty.CreateCommand("help", &arch::command::Help);

            tty.CreateCommand("sys", &arch::command::Sys);

            tty.CreateCommand("install", &arch::command::Install);

            tty.CreateCommand("detect", &arch::command::Detect);

            tty.CreateCommand("testw", &arch::command::Testw);

            tty.CreateCommand("exit", [&tty](std::vector<std::string> arguments)
            {
                tty.Exit();
            });

            tty.StartInteractive();
        }
    };
} // #arch

#endif