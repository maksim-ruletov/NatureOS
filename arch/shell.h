#if !defined(L0_SHELL_H)

/*
 * Оболочка будет прогружаться до инициализации ядра и позволит выполнять команды вне ядра. 
 */
#define L0_SHELL_H

#include "../misc/Screen.h"
#include "../misc/Colorizer.h"
#include "../misc/TTY.h"

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::TTY tty;

            misc::Clear();

            misc::Output(misc::E_ColorizeFont("Welcome to NatureOS shell!\n", 255, 0, 0));

            tty.CreateCommand("test", [](std::vector<std::string> arguments)
            {
                misc::Output("test\n");
            });

            tty.StartInteractive();
        }
    };
} // #arch

#endif