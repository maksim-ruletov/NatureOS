#if !defined(L0_COMMAND_TESTW_H)

#define L0_COMMAND_TESTW_H

#include <vector>
#include <string>

#include "../../misc/Screen.h"
#include "../../misc/Colorizer.h"

#include "../../fs/translated.h"

namespace arch
{
    namespace command
    {
        void Testw(std::vector<std::string> arguments)
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
        }
    }
}

#endif