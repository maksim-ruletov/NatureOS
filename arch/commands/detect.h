#if !defined(L0_COMMAND_DETECT_H)

#define L0_COMMAND_DETECT_H

#include <vector>
#include <string>

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"

namespace arch
{
    namespace command 
    {
        void Detect(std::vector<std::string> arguments)
        {
            if (fs::translated::DirectoryExist("./natureos"))
            {
                misc::Output("NatureOS founded. To check the system performance, write the testw command\n");
            }
            else
            {
                misc::Output("NatureOS not founded. To install it write install command\n");
            }
        }
    }
}

#endif