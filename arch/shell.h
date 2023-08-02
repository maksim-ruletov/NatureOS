#if !defined(L0_SHELL_H)

/*
 * Оболочка будет прогружаться до инициализации ядра и позволит выполнять команды вне ядра. 
 */
#define L0_SHELL_H

#include "../misc/Screen.h"
#include "../misc/Colorizer.h"

namespace arch {
    class Shell
    {
    public:
        void Start()
        {
            misc::E_Output(misc::E_ColorizeFont("Welcome to NatureOS shell!", 255, 0, 0));
        }
    };
} // #arch

#endif