#if !defined(L0_COMMAND_DATE_H)

#define L0_COMMAND_SYS_H

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"
#include "../../misc/Timer.h"

namespace arch 
{
    namespace command
    {
        void Date(std::vector<std::string> arguments)
        {
            misc::Output(misc::ColorizeFont("Current Date " + misc::E_GetDateAndTime(), 0, 255, 255));
            misc::Output("\n");
        }
    }
}

#endif